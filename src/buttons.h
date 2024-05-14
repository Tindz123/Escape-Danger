#ifndef BUTTONS_H
#define BUTTONS_H
#include "utils.h"
#include "game.h"
class Buttons
{
	public:
		Buttons(int w, int h);
		~Buttons();

		void setPosition( int x, int y );
		void setButtonName(string name, SDL_Color textColor, TTF_Font* font);
		void render(SDL_Renderer* gRenderer, LTexture& gTButtonsSpriteSheet, SDL_Rect* clip);
        bool isInside(int& x, int& y);
        void changeNameColor(SDL_Color newNameColor);
        SDL_Color getColor();
        SDL_Rect getButtonBox();
        string getButtonName();

    private:
        SDL_Rect mButtonBox;
        string buttonName;
        LTexture mTButtonName;
        SDL_Color buttonNameColor;
        TTF_Font* buttonNameFont;
};

#endif // BUTTONS_H
