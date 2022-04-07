#ifndef _threaten__H
#define _threaten__H
#include "main_object.h"
struct threaten_object{
    SDL_Rect *thr_object = new SDL_Rect[2];
    threaten_object();
    //~threaten_object();

    void draw(SDL_Renderer* renderer);
    bool die(main_object man,int i);
};
/*struct threaten_act{
    threaten_object;s
    int x;
    int y;

};*/
#endif // _threaten__H

