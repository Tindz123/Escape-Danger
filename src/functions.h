#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "utils.h"
#include "game.h"
#include "buttons.h"

int showMenu(Mix_Chunk* button, LTexture& gTTitle, TTF_Font* gFontTitle, Mix_Music* gMusic, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons);
int showWin(Mix_Chunk* button, LTexture& gWinTexture, TTF_Font* gFontTitle, Mix_Music* gMusic, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons);
int showLose(Mix_Chunk* button, LTexture& gLoseTexture, TTF_Font* gFontTitle, Mix_Music* gMusic, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons);

#endif // FUNCTIONS_H
