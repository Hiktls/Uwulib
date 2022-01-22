#include <WindowManager.hh>
#include <MediaManager.hh>
#include <Object.hh>
#include <Util.hh>
#include <math.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

// Add hash check to check if a load cycle is needed.


int main(int argc,char* argv[]){
    Util util;
    if(argc >= 2){
        if(!strcmp("package",argv[1])){
            string path = argv[2];
            util.Packager(path);
            return 0;
        }
    }
    else;
    WindowManager wManager("Hello World",SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SDL_WINDOW_SHOWN);
    MediaManager mManager(wManager.WINDOW,"assets",1);
    SDL_Event event;
    
    int alive = 1;
    SDL_SetRenderDrawColor( mManager.RENDERER, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderPresent(mManager.RENDERER);
    Object squae(127,250,60,100);
    squae.LoadTEX("assets\\super pervert.png",mManager);
    while(alive == 1){
        Uint64 framestart = SDL_GetPerformanceCounter();
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                alive = 0;
            }
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP: squae.Move(0,-5,1); break;
                    case SDLK_DOWN: squae.Move(0,5,1); break;
                    case SDLK_LEFT: squae.Move(-5,0,1); break;
                    case SDLK_RIGHT: squae.Move(5,0,1); break;
                }
            }
        }
        SDL_SetRenderDrawColor(mManager.RENDERER,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(mManager.RENDERER);
        squae.EventHandler(mManager);
        SDL_RenderPresent(mManager.RENDERER);
        Uint64 endframe = SDL_GetPerformanceCounter();
        float elapsedMS = (endframe - framestart) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    }
    return 0;
}