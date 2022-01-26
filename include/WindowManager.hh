#ifndef WINDOW_HH
#define WINDOW_HH

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using std::string;
using std::vector;
using std::exception;

class WindowManager {
    public:
        SDL_Window* WINDOW = NULL;
        SDL_Surface* SURFACE = NULL;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;
    WindowManager(std::string,int width,int height,int x,int y,Uint32 flags);
    ~WindowManager();
};


#endif