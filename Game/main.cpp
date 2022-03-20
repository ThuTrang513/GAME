#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture( string path, SDL_Renderer* rendere);

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
    SDL_Texture* background = loadTexture("Background.png",renderer);
    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.w = SCREEN_WIDTH;
    bgRect.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer,background,NULL,&bgRect);

    SDL_Texture* background_2 = loadTexture("Background.png",renderer);
    SDL_Rect bgRect_2;
    bgRect_2.x = -SCREEN_WIDTH;
    bgRect_2.y = 0;
    bgRect_2.w = SCREEN_WIDTH;
    bgRect_2.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer,background,NULL,&bgRect_2);

    SDL_Texture* logo = loadTexture("Idle (1).png",renderer);
    SDL_Rect logoRect;
    SDL_QueryTexture(logo,NULL,NULL,&logoRect.w,&logoRect.h);

    logoRect.x = 100;
    logoRect.y = 375;
    logoRect.w = logoRect.w /5.0;
    logoRect.h = logoRect.h /5.0;

    SDL_RenderCopy(renderer,logo,NULL,&logoRect);

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
            SDL_RenderCopy(renderer,background,NULL,&bgRect_2);
            SDL_RenderCopy(renderer,logo,NULL,&logoRect);
            SDL_RenderPresent(renderer);

    }
//end
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
