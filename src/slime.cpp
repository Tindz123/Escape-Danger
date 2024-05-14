#include "slime.h"
slime::slime()
{

    slimeFrame = 0;
    slimeDFrame = 3;
}
void slime::render(LTexture& gSlimeSpriteSheet, SDL_Renderer* gRenderer, SDL_Rect* clip )
{
    gSlimeSpriteSheet.render(enemyX, enemyY, gRenderer ,clip);
}
void slime::updateFrame(int SPRITE_SIZE , int &slimeFrame)
{
    int sizeF = SPRITE_SIZE;
    ++slimeFrame;
    if(slimeFrame / sizeF >= SPRITE_SIZE)
    {
        slimeFrame = 0;
    }
}

void slime::move(int mPosX ,int mPosY ,SDL_Rect &mEnemyBox)
{

    int temp = 10;
    if (enemyX < mPosX + temp)
    {
        enemyX += EnemyVel;
        mEnemyBox.x = enemyX;
    }

    else if (enemyX > mPosX + temp)
    {
        enemyX -= EnemyVel;
        mEnemyBox.x = enemyX;
    }

    if (enemyY < mPosY + temp)
    {
        enemyY += EnemyVel;
        mEnemyBox.y = enemyY;
    }
    else if (enemyY > mPosY+ temp)
    {
        enemyY -= EnemyVel;
        mEnemyBox.y = enemyY;
    }
}
