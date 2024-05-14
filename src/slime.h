#ifndef SLIME_H
#define SLIME_H
#include <utils.h>
#include <game.h>

class slime
{
    public:
        float EnemyVel = 0.1;
        slime();

        void render(LTexture& gSlimeSpriteSheet, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
        void updateFrame(int SPRITE_SIZE , int &slimeFrame);
        void updateDFrame(int SPRITE_SIZE , int &slimeDFrame);
        void move(int mPosX ,int mPosY ,SDL_Rect &mEnemyBox);

        float enemyX ,enemyY;
        int slimeFrame;
        int slimeDFrame;
        SDL_Rect mEnemyBox;
};

#endif // SLIME_H
