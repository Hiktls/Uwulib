#ifndef WINDOW_HH
#define WINDOW_HH

#include <SDL2/SDL.h>
#include <exception>
#include <iostream>
#include <vector>
#include <stdarg.h>

using std::string;
using std::vector;
using std::exception;

class WindowManager {
    public:
        SDL_Window* WINDOW = NULL;
        SDL_Surface* SURFACE = NULL;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;

    char* ExceptionFormat(string source,...){
        va_list list;
        char* buffer = (char*) malloc(2048 * sizeof(char));
        vsnprintf(buffer,sizeof(buffer),source.c_str(),list);
        return buffer;
    }
    WindowManager(std::string,int width,int height,int x,int y,Uint32 flags);
    ~WindowManager();
};


#endif