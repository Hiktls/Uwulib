#ifndef TEXT_HH
#define TEXT_HH

#include <string>
#include <SDL2/SDL_ttf.h>
#include "Texture.hh"
#include "Util.hh"
#include "MediaManager.hh"

using std::string;
// TODO : SDl_ttf initialized, only left to implement it.
class Text {
    public:
        /**
         * @brief Create a new text object
         * 
         * @param text The string that will be displayed.
         * @param font Font the string will be used with.
         * @param colour Colour of the font, default is black.
         */


        void SetDimensions(int width,int height){TextProps.w=width;TextProps.h=height;};

        void SetText(string text);
        
        void SetFont(TTF_Font* font){TextFont=font;};
        /**
         * @brief Render text on to given renderer
         * 
         * @param Renderer Renderer that will be used to and rendered on to
         */
        void Render();
        
        /**
         * @brief Returns string typed text.
         * 
         * @return string
         */
        void CreateAttribute(string name,int id,string value);
        string GetText(){return RealStringText;};
        Text(string text,TTF_Font* font,MediaManager &medMang,SDL_Color colour={0,0,0,0xff});
        ~Text();
    private:
        Util util;
        SDL_Renderer* Renderer = NULL;
        // Everything is a texture if you look careful
        Texture RealText;
        string RealStringText;
        // Dimension properties of the Text.
        SDL_Rect TextProps;
        SDL_Color TextColour;
        // Font used to display the Text.
        TTF_Font* TextFont;
        
        
};


#endif