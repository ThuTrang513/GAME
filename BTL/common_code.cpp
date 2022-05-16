#include"common_code.h"

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
    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1){
        logSDLError(std::cout, "CreateRenderer", true);
    }
    if(TTF_Init()== -1){
        logSDLError(std::cout, "CreateRenderer", true);
    }
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
        break;
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
bool check_mouse(int xm, int ym,SDL_Rect menu_text){
    if( xm >= menu_text.x &&  xm <= menu_text.x + menu_text.w &&
        ym >= menu_text.y &&  ym <= menu_text.y + menu_text.h){
        return 1;
    }
    return 0;
}

bool Menu_show(SDL_Renderer* &renderer, const char* path_text){
    base_object menu_bg;
    menu_bg.load("menu.jpg",renderer);
    menu_bg.show(renderer);

    text_object menu_text[2];
    menu_text[1].set_create("PLAY GAME",300,SCREEN_HEIGHT/2,30,200);
    menu_text[1].set_font(path_text);
    menu_text[1].createGameText(renderer);

    menu_text[0].set_create("EXIT",300,SCREEN_HEIGHT/2 + 50 ,30,100);
    menu_text[0].set_font(path_text);
    menu_text[0].createGameText(renderer);

    SDL_Event e_m;
    int ym = 0;
    int xm = 0;

    while(true){

        while(SDL_PollEvent(&e_m)){
            switch (e_m.type){
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                {
                    xm = e_m.motion.x;
                    ym = e_m.motion.y;
                    for(int i = 0; i < 2; i++){
                        if(check_mouse(xm, ym,menu_text[i].rect)){
                            menu_text[i].set_color({0,0,0});
                        }
                        else{
                            menu_text[i].set_color({255,255,255});
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = e_m.motion.x;
                    ym = e_m.motion.y;
                    for(int i = 0; i < 2; i++){
                        if(check_mouse(xm, ym,menu_text[i].rect)){
                            menu_text[i].set_color({0,0,0});
                            return i;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        menu_bg.show(renderer);
        for(int i = 0; i < 2; i++){
            menu_text[i].createGameText(renderer);
        }

        SDL_RenderPresent(renderer);
    }
}

bool End_show(SDL_Renderer* &renderer, const char* path_text){
    base_object menu_bg;
    menu_bg.load("menu.jpg",renderer);
    menu_bg.show(renderer);

    text_object menu_text[2];
    menu_text[1].set_create("Continue",300,SCREEN_HEIGHT/2,30,200);
    menu_text[1].set_font(path_text);
    menu_text[1].createGameText(renderer);

    menu_text[0].set_create("EXIT",300,SCREEN_HEIGHT/2 + 50 ,30,100);
    menu_text[0].set_font(path_text);
    menu_text[0].createGameText(renderer);

    SDL_Event e_m;
    int ym = 0;
    int xm = 0;

    while(true){

        while(SDL_PollEvent(&e_m)){
            switch (e_m.type){
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
                {
                    xm = e_m.motion.x;
                    ym = e_m.motion.y;
                    for(int i = 0; i < 2; i++){
                        if(check_mouse(xm, ym,menu_text[i].rect)){
                            menu_text[i].set_color({0,0,0});
                        }
                        else{
                            menu_text[i].set_color({255,255,255});
                        }
                    }
                    cout << endl;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = e_m.motion.x;
                    ym = e_m.motion.y;
                    for(int i = 0; i < 2; i++){
                        if(check_mouse(xm, ym,menu_text[i].rect)){
                            menu_text[i].set_color({0,0,0});
                            return i;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        menu_bg.show(renderer);
        for(int i = 0; i < 2; i++){
            menu_text[i].createGameText(renderer);
        }

        SDL_RenderPresent(renderer);
    }
}
void GAME_OVER(SDL_Renderer* &renderer, const char* path_text){
    text_object game_over;
    game_over.set_create("GAME OVER",SCREEN_WIDTH /2 - 150,SCREEN_HEIGHT/2,50,300);
    game_over.set_color({0,0,0});
    game_over.set_font(path_text);
    game_over.createGameText(renderer);
}
