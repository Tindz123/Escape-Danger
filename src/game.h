#ifndef game_h
#define game_h

#include <utils.h>

class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile(string path, SDL_Renderer* gRenderer);
		#if defined(SDL_TTF_MAJOR_VERSION)
		bool loadFromRenderedText( string textureText, SDL_Color textColor ,SDL_Renderer *gRenderer,TTF_Font*gFont);
        #endif // defined
		void free();

        void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE); //render at a specific point

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;


		int mWidth;
		int mHeight;
};





#endif
