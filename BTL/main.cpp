#include"common_code.h"
#include "base_object.h"
#include "main_object.h"
#include "Threaten.h"
#include<time.h>


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    // BACKGROUND
    base_object background_1;
    background_1.load("Background2.png",renderer);
    background_1.show(renderer);

    base_object background_2;
    background_2.load("Background2.png",renderer);
    background_2.rect.x = SCREEN_WIDTH;
    background_2.show(renderer);
    // MAIN OBJECT
    main_object man("creature-sheet (1).png",renderer);
    man.main_.show(renderer);
    SDL_RenderPresent(renderer);
    //THREATEN OBJECT
    threaten_object threaten_("tree_pineLarge_E.png",renderer);
    threaten_.draw(renderer);

    // SOUND
    Mix_Chunk* jump_sound = Mix_LoadWAV("jump_sound.wav");

    // code
    SDL_Event e;
    bool is_quit = false;
    int bg_x = - 3;
    int index_frame = 0;
    while(!is_quit){

        //KEY_EVENT
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            man.handelInput(e,jump_sound);

        }

        //BACKGROUND_MOVE
        background_1.rect.x += bg_x;
        background_2.rect.x += bg_x;
        if(background_1.rect.x < -1000){
            background_1.rect.x = 0;
        }
        if(background_2.rect.x < 0){
            background_2.rect.x = 1000;
        }
        SDL_RenderClear(renderer);
        background_1.show(renderer);
        background_2.show(renderer);

        // threatern_move
        for(int i = 0; i < 2; i++){
            threaten_.thr_object[i].rect.x -= 7;
            if(threaten_.thr_object[i].rect.x <= 120 && threaten_.thr_object[i].rect.x >= 75&& man.main_.rect.y >= 430){
                is_quit = true;
            }
            if(threaten_.thr_object[i].rect.x + 7 < 0){
                if(i == 0){
                   threaten_.thr_object[i].rect.x = 1000 + rand()%500;
                }
                else{
                    threaten_.thr_object[i].rect.x = 1050 +  rand()%750;
                }
            }
        }
        threaten_.draw(renderer);

        // MAN_SHOW
        man.showoff(renderer,index_frame);
        index_frame ++;
        if(index_frame > 21){
            index_frame = 0;
        }
        man.handleMove();
        SDL_RenderPresent(renderer);
    }
//end
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
