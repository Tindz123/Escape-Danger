#ifndef PLAYER_H
#define PLAYER_H
#include <utils.h>
#include <game.h>

class player
{
    public:
        static const int PLAYER_VEL = 3;

		void handleEvent( SDL_Event& e ,int &direction ,int &mVelX ,int &mVelY);
        void render(int x , int y ,LTexture& gPlayerSpriteSheet, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
        void updateFrame(int SPRITE_SIZE , int &playerFrame);

        void move(int &mPosX ,int &mPosY, int mVelX , int mVelY ,SDL_Rect&mPlayerBox );

    private:


};

#endif // PLAYER_H
