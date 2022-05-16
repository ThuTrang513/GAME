#ifndef common_code__H
#define common_code__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include"Text.h"

using namespace std;

const int SCREEN_WIDTH = 730;
const int SCREEN_HEIGHT = 450;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture( string path, SDL_Renderer* rendere);

bool Menu_show(SDL_Renderer* &renderer, const char* font_path);
bool check_mouse(int xm, int ym, SDL_Rect menu_text);

bool End_show(SDL_Renderer* &renderer, const char* font_path);
void GAME_OVER(SDL_Renderer* &renderer, const char* path_text);
#endif // common_code__H
