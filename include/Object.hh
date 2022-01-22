#ifndef OBJECT_HH
#define OBJECT_HH

#include <MediaManager.hh>


class Object {

    public:
        int posX,posY;
        int width,height;
        
        void EventHandler(MediaManager &medMang);
        
        void LoadTEX(string path,MediaManager &medMang);

        // addOn variable checks if we want to add on to the current one or set the current one to the new one
        void Move(int newX,int newY,int addOn);
        
        Object(int objWidth,int objHeight,int x,int y);
        ~Object();
    private:
        SDL_Texture* ObjectTexture;

};


#endif