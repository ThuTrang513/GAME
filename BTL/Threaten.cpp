#include"common_code.h"
#include "Threaten.h"
#include "main_object.h"
#include<cstdlib>
#include<time.h>
threaten_object:: threaten_object(const char * path, SDL_Renderer* renderer){
    thr_object[0].load(path,renderer);
    thr_object[1].load(path,renderer);
    thr_object[0].rect.y = 305;
    thr_object[0].rect.w = 60;
    thr_object[0].rect.h = 60;
    thr_object[0].rect.x = SCREEN_WIDTH  + rand()%(SCREEN_WIDTH/2);
    thr_object[1].rect.y = 305;
    thr_object[1].rect.w = 60;
    thr_object[1].rect.h = 60;
    thr_object[1].rect.x = (SCREEN_WIDTH + thr_object[0].rect.x + 400)+ rand()%750;
}
void threaten_object::draw(SDL_Renderer* renderer){
    for(int i = 0; i <= 1; i++){
        thr_object[i].show(renderer);
    }
}
