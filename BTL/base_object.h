#ifndef base_object__h
#define base_object__h
 struct base_object{
     SDL_Texture* object;
     SDL_Rect rect;

     base_object();
     ~base_object();
     void show(SDL_Renderer* renderer);
     void load(const char * path, SDL_Renderer* renderer);

 };
#endif // base_objec__h
