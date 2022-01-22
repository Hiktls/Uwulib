#include <WindowManager.hh>
WindowManager::WindowManager(std::string title,int width,int height,int x=SDL_WINDOWPOS_CENTERED,int y=SDL_WINDOWPOS_CENTERED,Uint32 flags=SDL_WINDOW_SHOWN){
    if(width != NULL || height != NULL ){
        SCREEN_HEIGHT = height;
        SCREEN_WIDTH = width;        
    }
    else {
        throw std::invalid_argument("Argument must not be null.");
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        char* buffer = ExceptionFormat("Failed to init SDL. Err: %s",SDL_GetError());
        throw buffer;
    }
    WINDOW = SDL_CreateWindow(title.c_str(),x,y,SCREEN_WIDTH,SCREEN_HEIGHT,flags);
    
    if(WINDOW == NULL){
        char* buffer = ExceptionFormat("Failed to create. Err: %s",SDL_GetError());
        throw buffer;
    }
    SURFACE = SDL_GetWindowSurface(WINDOW);
}

WindowManager::~WindowManager(){
    SDL_FreeSurface(SURFACE);
    SDL_DestroyWindow(WINDOW);

    SDL_Quit();
}
