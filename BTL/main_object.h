#ifndef main_objec__h
#define main_objec__h

struct main_object{
    base_object main_;
    int x_val;
    int y_val;

    main_object(const char * path, SDL_Renderer* renderer);
    ~main_object();
    void handelInput(SDL_Event e);
    void handleMove();

};
#endif // main_objec__h
