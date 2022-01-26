#ifndef UTIL_HH
#define UTIL_HH

#include <fstream>
#include <filesystem>
#include <string>
#include <zlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sha256.hh"
using std::string;

namespace fs = std::filesystem;

class Util {

    public:
        string GetFileHash(string path);
        void Packager(string path);
        int Compress(string source, string dest);
        SDL_Texture* LoadTEX(string relativePath,SDL_Renderer* &Renderer);
        int Decompress(string source, string dest);
        Util(string tmp,string run,int compressionLevel);
    private:
        int compression;
        string RUNPATH;
        string TMPPATH;
        

};


#endif 