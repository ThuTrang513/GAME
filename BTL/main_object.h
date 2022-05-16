#ifndef main_objec__h
#define main_objec__h

#include "base_object.h"
struct main_object{
    base_object main_;
    SDL_Rect * frame = new SDL_Rect[4];
    int x_val;
    int y_val;
    int max_y,min_y;
    main_object(const char * path, SDL_Renderer* renderer);
    ~main_object();
    void handelInput(SDL_Event e,Mix_Chunk* jump_sound);
    void handleMove();
    void showoff(SDL_Renderer* renderer,int index_frame);
    void main_reset ();
    void set_image(const char * path,SDL_Renderer* renderer);
};
#endif // main_objec__h
