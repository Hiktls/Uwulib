#include <Texture.hh>

Texture::Texture(const int width,const int height,MediaManager &medMang,const string path) : util(medMang.TMPPATH,medMang.RUNPATH,medMang.GetCompressionLevel()){
    TMPPATH = medMang.TMPPATH;
    RUNPATH = medMang.RUNPATH;
    if(path == "NON"){
        LibTexture = NULL;
    }
    else {
        LibTexture = util.LoadTEX(path,medMang.RENDERER);
    }
    TexProps.h = height;
    TexProps.w = width;
    TexProps.x = 0;
    TexProps.y = 0;
}

void Texture::Open(const string path,const int width,const int height,SDL_Renderer* &Renderer){
    FreeTex();
    TexProps.w = width;
    TexProps.h = height;
    LibTexture = util.LoadTEX(path,Renderer);
}

void Texture::Render(const int x,const int y,SDL_Renderer* &Renderer){
    if(LibTexture != NULL){
        TexProps.x = x;
        TexProps.y = y;
        SDL_RenderCopy(Renderer,LibTexture,NULL,&TexProps);
        TexProps.x = 0;
        TexProps.y = 0;
    }
    else {
        throw std::runtime_error("Texture not loaded");
    }
}

Texture::~Texture(){
    SDL_DestroyTexture(LibTexture);
}