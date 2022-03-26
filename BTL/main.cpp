
#include"common_code.h"
#include "base_object.h"
#include "main_object.h"
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it
    /*SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);

    SDL_RenderPresent(renderer);*/
    base_object background;
    background.load("Background.png",renderer);
    background.show(renderer);
    main_object man("Idle (1).png",renderer);
    SDL_RenderPresent(renderer);
    SDL_Event e;

    while(e.type != SDL_QUIT){
        man.handelInput(e);
        man.handleMove();
        SDL_RenderClear(renderer);
        background.show(renderer);
        man.main_.show(renderer);
        SDL_RenderPresent(renderer);

    }
    /*
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) == 0 ) SDL_Delay(50);
        else if(e.type == SDL_QUIT ){
            break;
        }

        else if(e.type == SDL_KEYDOWN){
            cerr << "_" << e.key.keysym.sym <<"_" << endl;
            switch(e.key.keysym.sym ){
            case SDLK_UP:
                logoRect.y -= 50;
                logoRect.x += 50;
                break;
            case SDLK_DOWN:
                logoRect.y += 50;
                logoRect.x += 50;
                break;
            case SDLK_LEFT:
                logoRect.x -= 50;
                break;
            case SDLK_RIGHT:
                logoRect.x += 50;
                break;
            }
        }
            bgRect.x += 10;
            bgRect_2.x += 10;
            //logoRect.x += 50;
            if(bgRect.x == SCREEN_WIDTH){
                bgRect.x = -SCREEN_WIDTH;
            }
            if(bgRect_2.x == SCREEN_WIDTH){
                bgRect_2.x = -SCREEN_WIDTH;
            }
            if(logoRect.x == SCREEN_WIDTH){
                logoRect.x = 0;
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,background,NULL,&bgRect);
            SDL_RenderCopy(renderer,logo,NULL,&logoRect);
            SDL_RenderPresent(renderer);

    }*/
//end
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
