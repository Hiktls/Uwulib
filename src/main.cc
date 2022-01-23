#include <WindowManager.hh>
#include <MediaManager.hh>
#include <SDL2/SDL_ttf.h>
#include <GameObject.hh>
#include <Util.hh>
#include <math.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

// Add hash check to check if a load cycle is needed.

const int COMPRESSION_LEVEL = 1;

int main(int argc,char* argv[]){
    if(argc >= 2){
        Util util("","",COMPRESSION_LEVEL);
        if(!strcmp("package",argv[1])){
            string path = argv[2];
            util.Packager(path);
            return 0;
        }
    }
    else;
    WindowManager wManager("Hello World",SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SDL_WINDOW_SHOWN);
    MediaManager mManager(wManager.WINDOW,"assets",COMPRESSION_LEVEL);
    if((!TTF_Init())){
        throw std::runtime_error(TTF_GetError());
    }
    SDL_Event event;
    int alive = 1;
    SDL_SetRenderDrawColor( mManager.RENDERER, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderPresent(mManager.RENDERER);
    GameObject squae(126,126,5,5,mManager);
    squae.LoadTEX("assets\\super pervert.png",mManager.RENDERER);
    Texture background(SCREEN_WIDTH,SCREEN_HEIGHT,mManager,"assets\\background.png");
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
        background.Render(0,0,mManager.RENDERER);
        squae.EventHandler(mManager);
        SDL_RenderPresent(mManager.RENDERER);
        Uint64 endframe = SDL_GetPerformanceCounter();
        float elapsedMS = (endframe - framestart) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    }
    return 0;
}