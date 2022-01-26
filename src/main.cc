#include <math.h>
#include <SDL2/SDL_ttf.h>
#include "WindowManager.hh"
#include "GameObject.hh"
#include "Util.hh"
#include "MediaManager.hh"
#include "Text.hh"
#include "Button.hh"

// Todo: Create the button class with features including event triggers,borders, loading texture into the button,coloring it and all

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 512;


#define TICKS_PER_FRAME 16.6666

const int COMPRESSION_LEVEL = 0;

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

    SDL_Event event;
    int alive = 1;
    TTF_Font* anka = TTF_OpenFont("assets\\anka-coder.ttf",25);
    Text FpsText(argv[1],anka,mManager);
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;

    while(alive == 1){
        static double previousDelta = delta;
        a = SDL_GetTicks();
        delta = a - b;
        if(delta > 1000/60.0){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT){
                    alive = 0;
                }
                if(event.type == SDL_KEYDOWN){
                }
            }
            b = a;
            SDL_RenderPresent(mManager.RENDERER);
            SDL_SetRenderDrawColor(mManager.RENDERER,189, 26, 162,0xFF);
            SDL_RenderClear(mManager.RENDERER);
            printf("%f,%f\n",1000/delta,previousDelta);
            if(1000/delta != previousDelta)
                FpsText.SetText(std::to_string(1000/delta));
            previousDelta = 1000/delta;        
            FpsText.Render();
        }
    }
    return 0;
}