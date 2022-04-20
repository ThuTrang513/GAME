#include "common_code.h"
#include "base_object.h"
#include "main_object.h"
main_object::main_object(const char * path, SDL_Renderer* renderer){
    main_.load(path,renderer);
    SDL_QueryTexture(main_.object,NULL,NULL,&main_.rect.w,&main_.rect.h);
    for(int i = 0; i < 4; i++){
        (frame+i)->x = i*24;
        (frame+i)->y = 0;
        (frame+i)->h = main_.rect.h;
        (frame+i)->w = 24;
    }
    main_.rect.x = 100;
    main_.rect.y = 470;
    main_.rect.w = 48;
    main_.rect.h = 48;
    //

    main_.srcrect = frame;
    main_.show(renderer);
    x_val = 0;
    y_val = 0;
}

main_object::~main_object(){
    if(frame != NULL){
        delete frame;
        frame = NULL;
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
    if(main_.rect.y > 470 || main_.rect.y < 275){
        main_.rect.y -= y_val;
    }
}
void main_object::showoff(SDL_Renderer* renderer,int index_frame){
    if(index_frame % 7 == 0){
        main_.srcrect = frame + index_frame / 7;
    }
    main_.show(renderer);
}
