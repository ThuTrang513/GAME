#include "base_object.h"
base_object::base_object(){
    object = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    srcrect = NULL;
}
base_object::~base_object(){
    /*if(object != NULL){
        delete object;
        object = NULL;
    }*/
}
 void base_object::load(const char * path,SDL_Renderer* renderer){
     object = loadTexture(path,renderer);
 }
void base_object::show(SDL_Renderer* renderer){
    if(object != NULL){
        SDL_RenderCopy(renderer,object,srcrect,&rect);
    }
}
void base_object::set_rect(int x_, int y_, int h_, int w_){
    rect.x = x_;
    rect.y = y_;
    rect.w = h_;
    rect.h = w_;
}
