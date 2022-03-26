#include "common_code.h"
#include "base_object.h"
base_object::base_object(){
    object = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
}
base_object::~base_object(){
    if(object != NULL){
        delete object;
        object = NULL;
    }
}
 void base_object::load(const char * path,SDL_Renderer* renderer){
     object = loadTexture(path,renderer);
 }
void base_object::show(SDL_Renderer* renderer){
    if(object != NULL){
        SDL_RenderCopy(renderer,object,NULL,&rect);
    }
}
