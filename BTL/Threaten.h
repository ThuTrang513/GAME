#ifndef _threaten__H
#define _threaten__H
struct threaten_object{
    SDL_Rect *thr_object = new SDL_Rect[3];
    threaten_object();
    //~threaten_object();

    void draw(SDL_Renderer* renderer);
};
/*struct threaten_act{
    threaten_object;s
    int x;
    int y;

};*/
#endif // _threaten__H

