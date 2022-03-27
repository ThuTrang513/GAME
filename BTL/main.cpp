#include"common_code.h"
#include "base_object.h"
#include "main_object.h"
#include "Threaten.h"

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
    main_object man("Idle (1).png",renderer);
    man.main_.show(renderer);
    SDL_RenderPresent(renderer);
    //THREATEN OBJECT
    threaten_object threaten_;
    threaten_.draw(renderer);
    // code
    SDL_Event e;
    bool is_quit = false;
    int bg_x = -2;
    while(!is_quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            man.handelInput(e);
        }
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
        man.main_.show(renderer);
        man.handleMove();
        threaten_.draw(renderer);
        SDL_RenderPresent(renderer);
    }
//end
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
