#ifndef OBJECT_HH
#define OBJECT_HH

#include <MediaManager.hh>
#include <Texture.hh>
#include <Util.hh>
class GameObject {

    public:
        int posX,posY;
        int width,height;
        
        void EventHandler(MediaManager &medMang);
        
        void LoadTEX(string path,SDL_Renderer* Renderer);

        // addOn variable checks if we want to add on to the current one or set the current one to the new one
        void Move(int newX,int newY,int addOn);
        
        GameObject(int objWidth,int objHeight,int x,int y,MediaManager &medMang);
        ~GameObject();
    private:
        string TMPPATH;
        string RUNPATH;
        int compression;
        Texture ObjectTexture;

};


#endif