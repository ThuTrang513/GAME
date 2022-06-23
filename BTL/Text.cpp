#include"Text.h"

text_object::text_object(){
    text_color = {255,255,255};
}
void text_object:: set_create(string _str,int x_,int y_, int h_, int w_){
    str = _str;
    rect.x = x_;
    rect.y = y_;
    rect.w = w_;
    rect.h = h_;
}
void text_object::set_color(SDL_Color text_color_){
    text_color = text_color_;
}

void text_object::set_font(const char* path_text){
    font_text_ = TTF_OpenFont(path_text,rect.h);
}

void text_object::createGameText(SDL_Renderer* renderer ){
    SDL_Surface* surface_;
    if(font_text_){
      surface_ = TTF_RenderText_Solid(font_text_,str.c_str(),text_color);
    }
    else cout << "error";
    if(surface_ ){
        t_object = SDL_CreateTextureFromSurface(renderer,surface_);
        /*width_= surface_.w;
        height_ = surface_.h;*/

        SDL_FreeSurface(surface_);
    }
    else cout << "error";
    if(t_object != NULL){
        SDL_RenderCopy(renderer,t_object,NULL,&rect);
    }
    else cout << "error";
}
