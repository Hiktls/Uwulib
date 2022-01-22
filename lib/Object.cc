#include <Object.hh>

Object::Object(int objWidth,int objHeight,int x,int y){
    if(objWidth == NULL || objHeight == NULL){
        throw std::invalid_argument("Height or Width can not be NULL");
    }
    ObjectTexture = NULL;
    width = objWidth;
    height = objHeight;
    posX = x;
    posY = y;
}

void Object::EventHandler(MediaManager &medMang){
    if(ObjectTexture != NULL){
        SDL_Rect rect;
        rect.h = height;
        rect.w = width;
        rect.x = posX;
        rect.y = posY;
        SDL_RenderCopy(medMang.RENDERER,ObjectTexture,NULL,&rect);
    }
    else {
    }
}

void Object::Move(int newX,int newY,int addOn){
    if(addOn == 1){
        posX += newX;
        posY += newY;
    }
    else{
        posX = newX;
        posY = newY;
    }
}



void Object::LoadTEX(string path,MediaManager &medMang){ // SDL_Texture*(*texxer)(string)
    
    ObjectTexture = medMang.LoadTEX(path);
}

Object::~Object(){
    SDL_DestroyTexture(ObjectTexture);
    ObjectTexture = NULL;
    width = NULL;
    height = NULL;
    posX = NULL;
    posY = NULL;
}