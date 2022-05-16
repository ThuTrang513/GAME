#ifndef text_object_H_
#define text_object_H_

#include<cstring>
#include "common_code.h"
#include "base_object.h"
#include<SDL_ttf.h>

using namespace std;

struct text_object{
    string str;
    SDL_Color text_color;
    SDL_Texture* t_object;
    TTF_Font* font_text_;
    //int width_, height_;
    SDL_Rect rect;
    text_object();
    void set_font(const char* path_text);
    void createGameText(SDL_Renderer* renderer );
    void set_color(SDL_Color text_color_);
    void set_create(string _str,int x_,int y_, int h_, int w_);
};
#endif // text_object__H
