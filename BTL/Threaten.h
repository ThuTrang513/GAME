#ifndef _threaten__H
#define _threaten__H
#include "main_object.h"
#include "base_object.h"
struct threaten_object{
    base_object *thr_object = new base_object[2];
    threaten_object(const char * path, SDL_Renderer* renderer);
    //~threaten_object();
    void draw(SDL_Renderer* renderer);
};
/*struct threaten_act{
    threaten_object;s
    int x;
    int y;

};*/
#endif // _threaten__H

