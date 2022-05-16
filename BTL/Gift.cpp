#include "base_object.h"
#include<cstring>
#include"Gift.h"

void Gift_object::set_image(const char * path,SDL_Renderer* renderer){
    image.load(path,renderer);

    image.set_rect(-60,230,60,60);
}
void Gift_object::move_gift(int step,int mark_val, base_object plane){
    if(image.rect.x >= -100){
        image.rect.x -= step;
    }
    else if(mark_val % 20 == 0 && mark_val > 0 && mark_val % 7 != 0){
        if(plane.rect.x >= 670 && plane.rect.x <= 790){
            image.rect.x = SCREEN_WIDTH + 500;
        }
        else image.rect.x = SCREEN_WIDTH;
    }
}

bool Gift_object::getGift(int main_x, int main_y){
    if(image.rect.x >= main_x - 40 && image.rect.x <= main_x + 40 && main_y <= 290){
        return true;
    }
    return false;
}
void Gift_object::show_image(SDL_Renderer* renderer){
    image.show(renderer);
}

void Gift_object::reset_gift(){
    image.rect.x = -100;
}
void Gift_object::Suprising(int n, main_object &main,int &step ,int &bg_x,SDL_Renderer* renderer){
    if(n == 1){
        main.main_.rect.y = 296;
        main.main_.rect.w = 72;
        main.main_.rect.h = 72;
        main.max_y = 296;

    }
    else if(n == 2){
        step = 3;
        bg_x = 1;
    }
    else if(n == 3){
        main.set_image("creature-sheet (2).png",renderer);
    }
}
void  Gift_object::After_Suprising( int& num, bool &get_gift ,main_object& main,int &step, int &bg_x,SDL_Renderer* renderer ){
    get_gift = false;
    if(num == 1 ){
        main.main_reset();
    }
    else if(num == 2){
        step = 7;
        bg_x = 3;
    }
    else if(num == 3){
        main.set_image("creature-sheet (4).png",renderer);
    }
    num = 0;
}

