#ifndef _threaten__H
#define _threaten__H
struct threaten_object{
    SDL_Rect thr_object;
    threaten_object();
    void draw(SDL_Renderer* renderer);
};
#endif // _threaten__H

