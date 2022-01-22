#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <MediaManager.hh>

class Texture{

    public:
        int widht,height;
        void Open(string path,MediaManager &medMang);
        void Render();
        Texture();
        ~Texture();
    private:
        SDL_Texture* LibTexture;

};


#endif