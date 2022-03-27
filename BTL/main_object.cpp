#include "common_code.h"
#include "base_object.h"
#include "main_object.h"
main_object::main_object(const char * path, SDL_Renderer* renderer){
    main_.load(path,renderer);
    SDL_QueryTexture(main_.object,NULL,NULL,&main_.rect.w,&main_.rect.h);
    main_.rect.x = 100;
    main_.rect.y = 385;
    main_.rect.w = main_.rect.w /5.0;
    main_.rect.h = main_.rect.h /5.0;
    main_.show(renderer);
    x_val = 0;
    y_val = 0;
}
main_object::~main_object(){
    if(main_.object != NULL){
        delete main_.object;
        main_.object = NULL;
    }
}
void main_object::handelInput(SDL_Event e){
    if(e.type == SDL_KEYDOWN){
        cerr << "_" << e.key.keysym.sym <<"_" << endl;
        switch(e.key.keysym.sym ){
        case SDLK_UP:
            y_val = -5;
            break;
        }
    }
    else if(e.type == SDL_KEYUP){
        switch(e.key.keysym.sym ){
        case SDLK_UP:
            y_val += 10;
            break;
        }
    }
}
void main_object::handleMove(){
    main_.rect.y += y_val;
    if(main_.rect.y > 375 || main_.rect.y < 275){
        main_.rect.y -= y_val;
    }
}
