#include"common_code.h"
#include "Threaten.h"
#include "main_object.h"
#include<cstdlib>
#include<time.h>
threaten_object:: threaten_object(){
    srand((int) time(0));
    thr_object[0].y = 465;
    thr_object[0].w = 50;
    thr_object[0].h = 50;
    thr_object[0].x = 1000 + rand()%500;
    for(int i = 1; i <= 1; i++){
        thr_object[i].y = 465;
        thr_object[i].w = 50;
        thr_object[i].h = 50;
        thr_object[i].x = (thr_object[i-1].x + 400)+ rand()%500;
    }
}
void threaten_object:: draw(SDL_Renderer* renderer){
    for(int i = 0; i <= 1; i++){
        SDL_SetRenderDrawColor(renderer,204, 204,0, 0);
        SDL_RenderFillRect(renderer, &thr_object[i]);
    }
}
