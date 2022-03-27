#include"common_code.h"
#include "Threaten.h"

threaten_object:: threaten_object(){
    thr_object.y = 465;
    thr_object.w = 50;
    thr_object.h = 50;
}
void threaten_object:: draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,204, 204,0, 0);
    SDL_RenderFillRect(renderer, &thr_object);
}
