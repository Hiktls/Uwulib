#include "Text.hh"

Text::Text(string text,TTF_Font* font,MediaManager &medMang,SDL_Color colour) : util(medMang.TMPPATH,medMang.RUNPATH,medMang.GetCompressionLevel()), RealText(0,0,medMang){
    RealStringText = text;
    if(font == NULL){
        throw std::runtime_error("Bruh yo font is nall");
    }
    TextFont = font;
    TextColour = colour;
    Renderer = medMang.RENDERER;
    SDL_Surface* textSurface = TTF_RenderText_Solid(TextFont,RealStringText.c_str(),TextColour);
    if( textSurface == NULL )
    {
        throw std::runtime_error(TTF_GetError());
    }
    RealText.SetSDLTexture(SDL_CreateTextureFromSurface(medMang.RENDERER,textSurface));
    TextProps.h = textSurface->h;
    TextProps.w = textSurface->w;
    RealText.SetDimensions(TextProps.h,TextProps.w);
    SDL_FreeSurface(textSurface);

};

void Text::SetText(string text){
    RealStringText = text;
    SDL_Surface* textSurface = TTF_RenderText_Solid(TextFont,RealStringText.c_str(),TextColour);
    if( textSurface == NULL )
    {
        throw std::runtime_error(TTF_GetError());
    }
    RealText.FreeTex();
    RealText.SetSDLTexture(SDL_CreateTextureFromSurface(Renderer,textSurface));
    TextProps.h = textSurface->h;
    TextProps.w = textSurface->w;
    RealText.SetDimensions(TextProps.h,TextProps.w);
    SDL_FreeSurface(textSurface);
}

void Text::Render(){
    RealText.Render(0,0);
}

Text::~Text(){
}