#include"common_code.h"
#include "base_object.h"
#include "main_object.h"
#include "Threaten.h"
#include<time.h>
#include"Text.h"
#include<fstream>
#include"Gift.h"

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    // MENU
    bool is_quit = !Menu_show(renderer,"calibri-bold.ttf");
    SDL_RenderPresent(renderer);
    // BACKGROUND
    base_object background_1;
    background_1.load("bg_2.jpg",renderer);
    background_1.show(renderer);

    base_object background_2;
    background_2.load("bg_2.jpg",renderer);
    background_2.rect.x = 720;
    background_2.show(renderer);
    // MAIN OBJECT
    main_object man("creature-sheet (4).png",renderer);
    man.main_.show(renderer);

    //THREATEN OBJECT
    threaten_object threaten_("tree_4-removebg-preview.png",renderer);
    threaten_.draw(renderer);

    // SOUND
    Mix_Chunk* jump_sound = Mix_LoadWAV("jump_sound.wav");

    // Text
    const char* path_text = "FreeMonoBold.ttf";

    text_object mark;
    mark.set_create("Mark: ", 20,30,20,100);
    mark.set_font(path_text);
    mark.createGameText(renderer);
    int mark_val = 0;

    text_object time;
    time.set_create("Time", SCREEN_WIDTH /2 - 50,30,20,100);
    int time_val = SDL_GetTicks()/1000;
    int time_pause = 0;
    time.set_font(path_text);
    time.createGameText(renderer);

    ifstream mark_file ("Mark.txt");
    int val_max;
    mark_file >> val_max;
    text_object mark_max;
    mark_max.set_create("Mark Max: ",SCREEN_WIDTH - 200,30,20,200);
    mark_max.str = "Mark Max: " + to_string(val_max);
    mark_max.set_font(path_text);
    mark_max.createGameText(renderer);

    //gift
    Gift_object gift_object;
    gift_object.set_image("gift-removebg.png",renderer);

    // plane
    base_object plane;
    plane.load("creature-0.png",renderer);
    plane.set_rect(-100,230,60,60);

    //SDL_RenderPresent(renderer);
    // code
    SDL_Event e;
    bool get_gift = false;
    int bg_x = 3;
    int feature_step = 5;
    int index_frame = 0;
    int num;
    while(!is_quit){

        //KEY_EVENT
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            man.handelInput(e,jump_sound);
        }
        //BACKGROUND_MOVE
        background_1.rect.x -= bg_x;
        background_2.rect.x -= bg_x;
        if(background_1.rect.x < -720){
            background_1.rect.x = 720;
        }
        if(background_2.rect.x < -720){
            background_2.rect.x = 720;
        }
        SDL_RenderClear(renderer);
        background_1.show(renderer);
        background_2.show(renderer);

        // threatern_move
        for(int i = 0; i < 2; i++){
            threaten_.thr_object[i].rect.x -= feature_step;
            if(threaten_.thr_object[i].rect.x <= 120 && threaten_.thr_object[i].rect.x >= 75 && man.main_.rect.y >= 290 && num != 3){
                is_quit = true;
                GAME_OVER(renderer,path_text);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000);
            }
            if(threaten_.thr_object[i].rect.x <= 75 && threaten_.thr_object[i].rect.x >= 68){
                mark_val ++;
            }
            if(threaten_.thr_object[i].rect.x + feature_step < 0){
                if(i == 0){
                   threaten_.thr_object[i].rect.x = SCREEN_WIDTH + rand()%(SCREEN_WIDTH/2);
                }
                else{
                    threaten_.thr_object[i].rect.x = threaten_.thr_object[0].rect.x + 200 +  rand()%750;
                }
            }
        }
        //plane
        if(plane.rect.x <= 120 && plane.rect.x >= 75 && man.main_.rect.y <= 270 && num != 3){
            is_quit = true;
            SDL_Delay(500);
        }
        if(plane.rect.x >= -100){
            plane.rect.x -= feature_step;
        }
        else if(mark_val % 7 == 0 && mark_val > 0){
            plane.rect.x = SCREEN_WIDTH;
        }
        //gift
        gift_object.move_gift(feature_step,mark_val,plane);
        int time_start;
        if(gift_object.getGift(man.main_.rect.x,man.main_.rect.y)){
            if(get_gift == false){
                num = 1 + rand()% 3;
                cout << num << endl;
                gift_object.Suprising(num,man,feature_step,bg_x,renderer);
                get_gift = true;
                time_start = SDL_GetTicks()/1000 - time_pause;
            }
        }
        if(SDL_GetTicks()/1000 - time_pause - time_start == 10 && get_gift == true){
            gift_object.After_Suprising(num,get_gift, man,feature_step,bg_x ,renderer);
            cout << "end " << endl;
        }
        gift_object.show_image(renderer);
        plane.show(renderer);
        threaten_.draw(renderer);
        // MAN_SHOW
        man.showoff(renderer,index_frame);
        index_frame ++;
        if(index_frame > 21){
            index_frame = 0;
        }
        man.handleMove();

        // TEXT_SHOW
        mark.str = "Mark: " + to_string(mark_val);
        mark.createGameText(renderer);

        time_val = SDL_GetTicks()/1000 - time_pause;
        time.str = "Time: " + to_string(time_val);
        time.createGameText(renderer);

        mark_max.str = "Mark Max: " + to_string(val_max);
        mark_max.createGameText(renderer);
        // IF LOSE
        if(is_quit == true){
            is_quit = !End_show(renderer,"FreeMonoBold.ttf");
            for(int i = 0; i < 2; i++){
                if(i == 0){
                    threaten_.thr_object[i].rect.x = SCREEN_WIDTH + rand()%500;
                }
                else{
                    threaten_.thr_object[i].rect.x = SCREEN_WIDTH + rand()%750;
                }
            }
            plane.rect.x = -100;
            gift_object.reset_gift();
            man.main_reset();
            man.set_image("creature-sheet (4).png",renderer);
            bg_x = 3;
            feature_step = 5;
            if(mark_val > val_max){
                val_max = mark_val;
                ofstream file("Mark.txt");
                file << val_max;
                file.close();
            }
            mark_val = 0;
            time_pause = SDL_GetTicks()/1000;
            SDL_Delay(100);
        }
        SDL_RenderPresent(renderer);
    }
//end
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
