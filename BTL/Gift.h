#ifndef GIFT_H_INCLUDED
#define GIFT_H_INCLUDED

#include "main_object.h"

struct Gift_object {
    base_object image;
    void set_image(const char * path,SDL_Renderer* renderer);
    void move_gift(int step,int mark_val,base_object plane);
    bool getGift(int main_x, int main_y);
    void show_image(SDL_Renderer* renderer);
    void reset_gift();
    void Suprising(int n, main_object& main,int &step, int &bg_x,SDL_Renderer* renderer);
    void After_Suprising( int& num, bool &get_gift,main_object& main,int &step, int &bg_x,SDL_Renderer* renderer);
};

#endif // GIFT_H_INCLUDED
