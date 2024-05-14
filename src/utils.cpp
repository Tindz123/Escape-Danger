#include "utils.h"
bool checkCollision(SDL_Rect& a, SDL_Rect& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB - 20)
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}
bool checkCollision2(SDL_Rect& a, SDL_Rect& b)
{
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    float temp2 = 20;

    if( bottomA <= topB - temp2 - 10)
    {
        return false;
    }

    if( topA >= bottomB + 12)
    {
        return false;
    }

    if( rightA <= leftB - temp2*2)
    {
        return false;
    }

    if( leftA >= rightB + temp2)
    {
        return false;
    }

    return true;
}
