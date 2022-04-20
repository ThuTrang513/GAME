#ifndef main_objec__h
#define main_objec__h

#include "base_object.h"
struct main_object{
    base_object main_;
    SDL_Rect * frame = new SDL_Rect[4];
    int x_val;
    int y_val;

    main_object(const char * path, SDL_Renderer* renderer);
    ~main_object();
    void handelInput(SDL_Event e);
    void handleMove();
    void showoff(SDL_Renderer* renderer,int index_frame);
};
#endif // main_objec__h
