#ifndef BUTTON_HH
#define BUTTON_HH

#include <SDL2/SDL.h>
#include "Text.hh"

struct Border{
    int s1,s2,s3,s4;
};

class Button{

    public:

    /**
     * @brief Create the button object which you can create triggers
     * 
     * @param text Text on the button, duh
     * @param color 
     * @param medMang
     */
        Button(Text text,SDL_Color color,Texture texture,Border border);


    private:
        Text ButtonText;
        SDL_Renderer* Renderer = NULL;
        SDL_Color ButtonColor;

};



#endif