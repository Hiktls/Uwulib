#include <WindowManager.hh>
WindowManager::WindowManager(std::string title,int width,int height,int x=SDL_WINDOWPOS_CENTERED,int y=SDL_WINDOWPOS_CENTERED,Uint32 flags=SDL_WINDOW_SHOWN){
    SCREEN_HEIGHT = height;
    SCREEN_WIDTH = width;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::runtime_error(SDL_GetError());
    }
    WINDOW = SDL_CreateWindow(title.c_str(),x,y,SCREEN_WIDTH,SCREEN_HEIGHT,flags);
    
    if(WINDOW == NULL){
        throw std::runtime_error(SDL_GetError());
    }
    SURFACE = SDL_GetWindowSurface(WINDOW);
}

WindowManager::~WindowManager(){
    SDL_FreeSurface(SURFACE);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}
