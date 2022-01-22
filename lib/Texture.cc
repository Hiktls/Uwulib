#include <Texture.hh>

void Texture::Open(string path,MediaManager &medMang){
    LibTexture = medMang.LoadTEX(path);
}