import torch
from torchvision import transforms
from PIL import Image, ImageDraw
from model import EAST_model
from dataset import get_rotate_mat
import os
import numpy as np
import lanms


def resize_img(img):
	'''resize image to be divisible by 32
	'''
	w, h = img.size
	resize_w = w
	resize_h = h

	resize_h = resize_h if resize_h % 32 == 0 else int(resize_h / 32) * 32
	resize_w = resize_w if resize_w % 32 == 0 else int(resize_w / 32) * 32
	img = img.resize((resize_w, resize_h), Image.BILINEAR)
	ratio_h = resize_h / h
	ratio_w = resize_w / w

	return img, ratio_h, ratio_w


def load_pil(img):
	'''convert PIL Image to torch.Tensor
	'''
	t = transforms.Compose([transforms.ToTensor(), transforms.Normalize(mean=(0.5,0.5,0.5),std=(0.5,0.5,0.5))])
	return t(img).unsqueeze(0)


def is_valid_poly(res, score_shape, scale):
	'''check if the poly in image scope
	Input:
		res        : restored poly in original image
		score_shape: score map shape
		scale      : feature map -> image
	Output:
		True if valid
	'''
	cnt = 0
	for i in range(res.shape[1]):
		if res[0,i] < 0 or res[0,i] >= score_shape[1] * scale or \
           res[1,i] < 0 or res[1,i] >= score_shape[0] * scale:
			cnt += 1
	return True if cnt <= 1 else False


def restore_polys(valid_pos, valid_geo, score_shape, scale=4):
	'''restore polys from feature maps in given positions
	Input:
		valid_pos  : potential text positions <numpy.ndarray, (n,2)>
		valid_geo  : geometry in valid_pos <numpy.ndarray, (5,n)>
		score_shape: shape of score map
		scale      : image / feature map
	Output:
		restored polys <numpy.ndarray, (n,8)>, index
	'''
	polys = []
	index = []
	valid_pos *= scale
	d = valid_geo[:4, :] # 4 x N
	angle = valid_geo[4, :] # N,

	for i in range(valid_pos.shape[0]):
		x = valid_pos[i, 0]
		y = valid_pos[i, 1]
		y_min = y - d[0, i]
		y_max = y + d[1, i]
		x_min = x - d[2, i]
		x_max = x + d[3, i]
		rotate_mat = get_rotate_mat(-angle[i])

		temp_x = np.array([[x_min, x_max, x_max, x_min]]) - x
		temp_y = np.array([[y_min, y_min, y_max, y_max]]) - y
		coordidates = np.concatenate((temp_x, temp_y), axis=0)
		res = np.dot(rotate_mat, coordidates)
		res[0,:] += x
		res[1,:] += y

		if is_valid_poly(res, score_shape, scale):
			index.append(i)
			polys.append([res[0,0], res[1,0], res[0,1], res[1,1], res[0,2], res[1,2],res[0,3], res[1,3]])
	return np.array(polys), index

def get_boxes(score, geo, score_thresh=0.9, nms_thresh=0.2):
  score = score[0,:,:]
  xy_text = np.argwhere(score > score_thresh) # n x 2, format is [r, c]
  if xy_text.size == 0:
    return None

  xy_text = xy_text[np.argsort(xy_text[:, 0])]
  valid_pos = xy_text[:, ::-1].copy() # n x 2, [x, y]
  valid_geo = geo[:, xy_text[:, 0], xy_text[:, 1]] # 5 x n
  polys_restored, index = restore_polys(valid_pos, valid_geo, score.shape)
  if polys_restored.size == 0:
    return None

  boxes = np.zeros((polys_restored.shape[0], 9), dtype=np.float32)
  boxes[:, :8] = polys_restored
  boxes[:, 8] = score[xy_text[index, 0], xy_text[index, 1]]
  newboxes = lanms.merge_quadrangle_n9(boxes.astype('float32'), nms_thresh)
  return newboxes


def adjust_ratio(boxes, ratio_w, ratio_h):
	'''refine boxes
	Input:
		boxes  : detected polys <numpy.ndarray, (n,9)>
		ratio_w: ratio of width
		ratio_h: ratio of height
	Output:
		refined boxes
	'''
	if boxes is None or boxes.size == 0:
		return None
	boxes[:,[0,2,4,6]] /= ratio_w
	boxes[:,[1,3,5,7]] /= ratio_h
	return np.around(boxes)

def postprocess(boxes):
  new_boxes = []
  for box in boxes:
    x = [box[0], box[2], box[4], box[6]]
    x.sort()
    y = [box[1], box[3], box[5], box[7]]
    y.sort()
    if abs(x[0] - x[1]) < 2 and abs(x[2] - x[3]) < 2  and abs(y[0] - y[1]) < 2 and abs(y[2] - y[3]) < 2: 
      new_boxes.append([x[0], y[0], x[2], y[0], x[2], y[2], x[0], y[2], box[8]])
  return np.array(new_boxes)

def detect(img, model, device):
  img, ratio_h, ratio_w = resize_img(img)
  with torch.no_grad():
    score, geo = model(load_pil(img).to(device))
  boxes = get_boxes(score.squeeze(0).cpu().numpy(), geo.squeeze(0).cpu().numpy())
  boxes = adjust_ratio(boxes, ratio_w, ratio_h)
  return postprocess(boxes)

def format_submit_data(img, labels):
    new_labels = []
    w = img.size[0]
    h = img.size[1]
    print(h, w)
    for label in labels:
        x_tl = label[0]
        y_tl = label[1]
        w_b = abs(label[0] - label[4])
        h_b = abs(label[1] - label[5])
        x_c = (x_tl + w_b * 0.5) / w
        y_c = (y_tl + h_b * 0.5) / h
        w_b = w_b / w
        h_b = h_b / h
        mx = int(label[8] / 1.0)
        mn = int(label[8] / 0.9)
        avg = int(mx + mn) / 2
        score = label[8] / avg
        new_labels.append(" ".join([str(0), str(x_c), str(y_c), str(w_b), str(h_b), str(score)]) + "\n")
    return new_labels

def detect_dataset(model, device, test_img_path, submit_path):
	list_path = os.listdir(test_img_path)
	list_path.sort()
	for path in list_path:
			img = Image.open(test_img_path + "/" + path)
			boxes = detect(img, model, device)
			labels = format_submit_data(img, boxes)
			with open(submit_path + "/" + path.replace("jpg", "txt"), "w") as f:
				f.writelines(labels)

if __name__ == '__main__':
	test_img_path   = './Data/Valid/Images'
	model_path  = './pths/model_epoch_10.pth'
	submit_path     = './Data/Valid/Submit'
	device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
	model = EAST_model().to(device)
	model.load_state_dict(torch.load(model_path))
	model.eval()
	detect_dataset(model, device, test_img_path, submit_path)

