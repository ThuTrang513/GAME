#ifndef base_object__h
#define base_object__h
#include "common_code.h"
 struct base_object{
     SDL_Texture* object;
     SDL_Rect rect;
     SDL_Rect * srcrect;

     base_object();
     ~base_object();
     void show(SDL_Renderer* renderer);
     void load(const char * path, SDL_Renderer* renderer);
    void set_rect(int x_, int y_, int h_, int w_);
 };
#endif // base_objec__h
