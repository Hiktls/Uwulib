#ifndef MEDIA_HH
#define MEDIA_HH

#include <Util.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>

using std::string;
namespace fs = std::filesystem;


class MediaManager {
    public:
        SDL_Renderer* RENDERER = NULL;
        string RUNPATH;
        string ASSETSNAME;
        string TMPPATH;
    SDL_Texture* LoadTEX(string relativePath);
    SDL_Surface* LoadBMP(string relativePath,SDL_Surface* MainSurface);
    SDL_Surface* LoadIMG(string relativePath,SDL_Surface* MainSurface);
    void BlitSurface(SDL_Surface* MainSurface,SDL_Surface* TargetSurface,int x,int y,int h,int w);
    int GetCompressionLevel(){return compressionLevel;};
    // Air compress is an integer used to determine if we want to compress assets, and how we want to go about that.
    // With this, we are able to; compress, dont compress, decompress when asset is needed and compress it back. 
    // 0 : dont compress
    // 1 : compress
    // 2 : air compress
    MediaManager(SDL_Window* WINDOW,string assetsFolder,int compression);
    ~MediaManager();
    private:
        int compressionLevel;
};

#endif