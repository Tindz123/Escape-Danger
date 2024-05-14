#include "functions.h"

int showMenu(Mix_Chunk* button, LTexture& gTTitle, TTF_Font* gFontTitle, Mix_Music* gMusic, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int selected[(int)menuButtons.size()];
    for(int i = 0; i < (int)menuButtons.size(); i++){
        selected[i] = 0;
    }
    SDL_Color changedColor = {70, 12, 12};
    SDL_Color originalColor = menuButtons[0]->getColor();
    SDL_Event ev;
    SDL_Color titleColor = {51, 25, 0};
    Mix_PlayMusic(gMusic, -1);
    while(true){
        gStateBackground.render(0, 0, gRenderer);
        if(gTTitle.loadFromRenderedText("ESCAPE DANGER", titleColor, gRenderer, gFontTitle)){
            gTTitle.render(SCREEN_WIDTH / 2 - gTTitle.getWidth() / 2, SCREEN_HEIGHT / 4 - gTTitle.getHeight()/ 2, gRenderer);
        }
        for(int i = 0; i < (int)menuButtons.size(); i++){
            menuButtons[i]->render(gRenderer, gQuitTexture[selected[i]], NULL);
        }
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                return -1;
            }
            int x, y; SDL_GetMouseState(&x, &y);
            switch(ev.type){
            case SDL_MOUSEMOTION:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(!menuButtons[i]->isInside(x, y)){
                        if(!selected[i]){
                            selected[i] = 1;
                            menuButtons[i]->changeNameColor(changedColor);
                        }
                    }
                    else{
                        if(selected[i]){
                            selected[i] = 0;
                            menuButtons[i]->changeNameColor(originalColor);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(menuButtons[i]->isInside(x, y)){
                        Mix_PlayChannel(-1, button, 0);
                        return i;
                    }
                }
            }
            break;
            default:
                break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    return -1;
}
int showWin(Mix_Chunk* button, LTexture& gWinTexture, TTF_Font* gFontTitle, Mix_Music* gWin, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int selected[(int)menuButtons.size()];
    for(int i = 0; i < (int)menuButtons.size(); i++){
        selected[i] = 0;
    }
    SDL_Color changedColor = {70, 12, 12};
    SDL_Color originalColor = menuButtons[0]->getColor();
    SDL_Event ev;
    SDL_Color titleColor = {51, 25, 0};
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(gWin, -1);
    while(true){
        gStateBackground.render(0, 0, gRenderer);
        if(gWinTexture.loadFromRenderedText("YOU WIN!!!", titleColor, gRenderer, gFontTitle)){
            gWinTexture.render(SCREEN_WIDTH / 2 - gWinTexture.getWidth() / 2, SCREEN_HEIGHT / 4 - gWinTexture.getHeight()/ 2, gRenderer);
        }
        for(int i = 0; i < (int)menuButtons.size(); i++){
            menuButtons[i]->render(gRenderer, gQuitTexture[selected[i]], NULL);
        }
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                return -1;
            }
            int x, y; SDL_GetMouseState(&x, &y);
            switch(ev.type){
            case SDL_MOUSEMOTION:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(!menuButtons[i]->isInside(x, y)){
                        if(!selected[i]){
                            selected[i] = 1;
                            menuButtons[i]->changeNameColor(changedColor);
                        }
                    }
                    else{
                        if(selected[i]){
                            selected[i] = 0;
                            menuButtons[i]->changeNameColor(originalColor);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(menuButtons[i]->isInside(x, y)){
                        Mix_PlayChannel(-1, button, 0);
                        return i;
                    }
                }
            }
            break;
            default:
                break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    return -1;
}
int showLose(Mix_Chunk* button, LTexture& gLoseTexture, TTF_Font* gFontTitle, Mix_Music* gMusic, LTexture& gStateBackground, LTexture (&gQuitTexture)[2], SDL_Renderer* gRenderer, vector<Buttons*>& menuButtons)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int selected[(int)menuButtons.size()];
    for(int i = 0; i < (int)menuButtons.size(); i++){
        selected[i] = 0;
    }
    SDL_Color changedColor = {70, 12, 12};
    SDL_Color originalColor = menuButtons[0]->getColor();
    SDL_Event ev;
    SDL_Color titleColor = {51, 25, 0};
    Mix_PlayMusic(gMusic, -1);
    while(true){
        gStateBackground.render(0, 0, gRenderer);
        if(gLoseTexture.loadFromRenderedText("YOU LOSE :((", titleColor, gRenderer, gFontTitle)){
            gLoseTexture.render(SCREEN_WIDTH / 2 - gLoseTexture.getWidth() / 2, SCREEN_HEIGHT / 4 - gLoseTexture.getHeight()/ 2, gRenderer);
        }
        for(int i = 0; i < (int)menuButtons.size(); i++){
            menuButtons[i]->render(gRenderer, gQuitTexture[selected[i]], NULL);
        }
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                return -1;
            }
            int x, y; SDL_GetMouseState(&x, &y);
            switch(ev.type){
            case SDL_MOUSEMOTION:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(!menuButtons[i]->isInside(x, y)){
                        if(!selected[i]){
                            selected[i] = 1;
                            menuButtons[i]->changeNameColor(changedColor);
                        }
                    }
                    else{
                        if(selected[i]){
                            selected[i] = 0;
                            menuButtons[i]->changeNameColor(originalColor);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                for(int i = 0; i < (int)menuButtons.size(); i++){
                    if(menuButtons[i]->isInside(x, y)){
                        Mix_PlayChannel(-1, button, 0);
                        return i;
                    }
                }
            }
            break;
            default:
                break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    return -1;
}

