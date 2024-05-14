#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
#include <ctime>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_mixer.h"

#define pb push_back

const int IDLE_ANIMATION = 6;
const int IDLE_U_ANIMATION = 6;
const int IDLE_R_ANIMATION = 6;
const int IDLE_L_ANIMATION = 6;
const int RUN_R_ANIMATION = 6;
const int RUN_L_ANIMATION = 6;
const int RUN_U_ANIMATION = 6;
const int RUN_D_ANIMATION = 6;
const int A_U_ANIMATION = 4;
const int A_D_ANIMATION = 4;
const int A_R_ANIMATION = 4;
const int A_L_ANIMATION = 4;
const int ENEMY_ANIMATION = 7;
const int ENEMY_D_ANIMATION = 5;
const int DEAD_ANIMATION = 3;

#define SCREEN_HEIGHT 808
#define SCREEN_WIDTH 805
const int SPRITE_WIDTH = 48;
const int SPRITE_HEIGHT = 61;
const int SPRITE_E_WIDTH = 32;
const int SPRITE_E_HEIGHT = 36;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int MENU_BUTTON_WIDTH = 200;
const int MENU_BUTTON_HEIGHT = 52;

bool checkCollision(SDL_Rect& a, SDL_Rect& b);
bool checkCollision2(SDL_Rect& a, SDL_Rect& b);

using namespace std;

#endif // UTILS_H
