#include <GameObject.hh>

GameObject::GameObject(int objWidth,int objHeight,int x,int y,MediaManager &medMang) : ObjectTexture(objWidth,objHeight,medMang) {
    width = objWidth;
    height = objHeight;
    posX = x;
    posY = y;
    compression = medMang.GetCompressionLevel();
    printf("%d",compression);
    TMPPATH = medMang.TMPPATH;
    RUNPATH = medMang.RUNPATH;
}

void GameObject::EventHandler(MediaManager &medMang){
    if(ObjectTexture.GetSDLTexture() != NULL){
        SDL_Rect rect;
        rect.h = height;
        rect.w = width;
        rect.x = posX;
        rect.y = posY;
        SDL_RenderCopy(medMang.RENDERER,ObjectTexture.GetSDLTexture(),NULL,&rect);
    }
}

void GameObject::Move(int newX,int newY,int addOn){
    if(addOn == 1){
        posX += newX;
        posY += newY;
    }
    else{
        posX = newX;
        posY = newY;
    }
}

void GameObject::LoadTEX(string path,SDL_Renderer* Renderer){
    Util util(TMPPATH,RUNPATH,compression);
    ObjectTexture.SetSDLTexture(util.LoadTEX(path,Renderer));
}

GameObject::~GameObject(){
    width = 0;
    height = 0;
    posX = 0;
    posY = 0;
}