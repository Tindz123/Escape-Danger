#include "player.h"

void player::render(int x , int y ,LTexture& gPlayerSpriteSheet, SDL_Renderer* gRenderer, SDL_Rect* clip )
{
    gPlayerSpriteSheet.render(x, y, gRenderer ,clip);
}
void player::handleEvent( SDL_Event& e ,int &direction ,int &mVelX , int &mVelY )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                direction = 1;
                 mVelY -= PLAYER_VEL;
                 break;
            case SDLK_DOWN:
                direction = 2;
                mVelY += PLAYER_VEL;
                break;
            case SDLK_LEFT:
                direction = 3;
                mVelX -= PLAYER_VEL;
                break;
            case SDLK_RIGHT:
                direction = 4;
                mVelX += PLAYER_VEL;
                break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                mVelY += PLAYER_VEL;
                break;
            case SDLK_DOWN:
                mVelY -= PLAYER_VEL;
                break;
            case SDLK_LEFT:
                mVelX += PLAYER_VEL;
                break;
            case SDLK_RIGHT:
                mVelX -= PLAYER_VEL;
                break;
        }
    }
}
void player::move(int &mPosX ,int &mPosY, int mVelX , int mVelY,SDL_Rect&mPlayerBox )
{
    mPosX += mVelX;
    mPlayerBox.x = mPosX;

    if( ( mPosX < 0 ) || ( mPosX + SPRITE_WIDTH > SCREEN_WIDTH ) )
    {
        mPosX -= mVelX;
        mPlayerBox.x = mPosX;
    }

    mPosY += mVelY;
    mPlayerBox.y = mPosY;

    if( ( mPosY < 0 ) || ( mPosY + SPRITE_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY;
        mPlayerBox.y = mPosY;
    }
}
void player::updateFrame(int SPRITE_SIZE , int &playerFrame)
{
    int sizeF = SPRITE_SIZE;
    ++playerFrame;
    if(playerFrame / sizeF >= SPRITE_SIZE)
    {
        playerFrame = 0;
    }
}
