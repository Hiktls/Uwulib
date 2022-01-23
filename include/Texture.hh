#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "MediaManager.hh"
#include "Util.hh"
class Texture{
    public:
        int width,height;
        /**  Open the a texture file, overrides the current texture.
        *   @param path Relative path to texture
        *   @param width
        *   @param height
        *   @throws std::runtime_error
        * 
        * 
        */
        void Open(const string path,const int width,const int height,SDL_Renderer* &Renderer);
        void FreeTex(){SDL_DestroyTexture(LibTexture);LibTexture=NULL;TexProps.h = 0;TexProps.w=0;}
        /**  Render texture, not a recommended way to render textures, this is for special cases where creating an Object type is unnecessary
        *   @param x X coordinate of the desired render location
        *   @param y Y coordinate of the desired render location
        *   @throws std::runtime_error
        */
        void Render(const int x,const int y,SDL_Renderer* &Renderer);
        Texture(const int width,const int height,MediaManager &medMang,const string path="NON");
        ~Texture();
        void SetSDLTexture(SDL_Texture* Tex){LibTexture = Tex;}
        SDL_Texture* GetSDLTexture(){return LibTexture;}
    private:
        Util util;
        SDL_Texture* LibTexture;
        SDL_Rect TexProps;
        string TMPPATH;
        string RUNPATH;

};


#endif