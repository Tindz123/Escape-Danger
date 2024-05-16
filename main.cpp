#include <utils.h>
#include "game.h"
#include "timer.h"
#include "player.h"
#include "slime.h"
#include "buttons.h"
#include "functions.h"
#include <random>

int randomInt(int min, int max);
bool Init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
LTexture gDTexture;
LTexture gAUTexture;
LTexture gADTexture;
LTexture gARTexture;
LTexture gALTexture;
LTexture gIdleTexture;
LTexture gIdleUTexture;
LTexture gIdleRTexture;
LTexture gIdleLTexture;
LTexture gUpTexture;
LTexture gDownTexture;
LTexture gLeftTexture;
LTexture gRightTexture;
LTexture gETexture;
LTexture gEDTexture;
LTexture gBackground;
LTexture gStateBackground;
LTexture gTTitle;
LTexture gWinTexture;
LTexture gLoseTexture;
LTexture gPlayTexture[2];
LTexture gCountDown;

TTF_Font *gFont = NULL;
TTF_Font *gFontTitle = NULL;
TTF_Font *gFontTime = NULL;

player *Player = NULL;
SDL_Rect mPlayerBox;
vector<slime*>enemies;
bool eDead[1000];
bool lose = false;

Mix_Music *gMusic = NULL;
Mix_Music *gWin = NULL;
Mix_Chunk* PDead = NULL;
Mix_Chunk* attack = NULL;
Mix_Chunk* button = NULL;

vector<Buttons*> menuStart;

SDL_Rect gSpriteClips[ IDLE_ANIMATION ];
SDL_Rect gSpriteClipsIU[ IDLE_ANIMATION ];
SDL_Rect gSpriteClipsIR[ IDLE_ANIMATION ];
SDL_Rect gSpriteClipsIL[ IDLE_ANIMATION ];
SDL_Rect gSpriteClipsR[RUN_R_ANIMATION];
SDL_Rect gSpriteClipsL[RUN_L_ANIMATION];
SDL_Rect gSpriteClipsU[ RUN_U_ANIMATION ];
SDL_Rect gSpriteClipsD[ RUN_D_ANIMATION ];
SDL_Rect gSpriteClipsAU[ A_U_ANIMATION ];
SDL_Rect gSpriteClipsAD[ A_D_ANIMATION ];
SDL_Rect gSpriteClipsAR[ A_R_ANIMATION ];
SDL_Rect gSpriteClipsAL[ A_L_ANIMATION ];
SDL_Rect gSpriteClipsE[ ENEMY_ANIMATION ];
SDL_Rect gSpriteClipsED[ ENEMY_D_ANIMATION ];

SDL_Renderer *gRenderer = NULL;


int main(int argc , char* argv[])
{
    if(!Init())
    {
        cout << "Unable to initialize\n";
    }else
    {
        if(!loadMedia())
        {
            cout << "Unable to load media\n";
        }else
        {
            bool isRunning = true;
            SDL_Color btmpColor = {121, 48, 48};

            Buttons* btmp = NULL; btmp = new Buttons(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
            btmp->setPosition(SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, 300);
            btmp->setButtonName("New game", btmpColor, gFont);
            Buttons* btmp2 = NULL; btmp2 = new Buttons(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
            btmp2->setPosition(btmp->getButtonBox().x, btmp->getButtonBox().y + MENU_BUTTON_HEIGHT + 25);
            btmp2->setButtonName("Quit", btmpColor, gFont);
            menuStart.pb(btmp); menuStart.pb(btmp2);
            int gameState = showMenu(button, gTTitle,gFontTitle, gMusic, gStateBackground, gPlayTexture, gRenderer, menuStart);
            if(gameState == 1|| gameState == -1) isRunning = 0;
            else isRunning = 1;

            SDL_Event e;
            int playerFrame = 0;
            int playerAttackFrame = 0;
            int playerDFrame = 0;
            int direct = 1;

            int mPosX = SCREEN_WIDTH / 2;
            int mPosY = SCREEN_HEIGHT / 2;
            int mVelX = 0;
            int mVelY = 0;
            mPlayerBox.w = SPRITE_WIDTH - 48;
            mPlayerBox.h = SPRITE_HEIGHT - 50;

            LTimer fpsTimer;
            LTimer capTimer;
            int countedFrames = 0;
            fpsTimer.start();

            int lastTime = SDL_GetTicks();

            int countdown = 120;
            Uint32 startTime = SDL_GetTicks();
            Uint32 isTouch = SDL_GetTicks();
            Mix_PlayMusic(gMusic,-1);

            while( isRunning )
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear(gRenderer);

                gBackground.render(0,0,gRenderer);

                Uint32 currentTime = SDL_GetTicks();
                Uint32 elapsedTime = currentTime - startTime;
                if (elapsedTime >= 1000) {
                    startTime = currentTime;
                    countdown--;
                }
                    if (countdown <= 0)
                        {
                            SDL_Delay(500);
                            int winState = showWin(button, gWinTexture,gFontTitle, gWin, gStateBackground, gPlayTexture, gRenderer, menuStart);
                            if(winState == 0)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear(gRenderer);
                                for(int j = 0 ; j < enemies.size() ; ++j)
                                {
                                    delete enemies[j];
                                }
                                enemies.clear();
                                playerFrame = 0;
                                playerAttackFrame = 0;
                                playerDFrame = 0;
                                direct = 1;
                                mPosX = SCREEN_WIDTH / 2;
                                mPosY = SCREEN_HEIGHT / 2;
                                mVelX = 0;
                                mVelY = 0;
                                countdown = 120;
                                Mix_PlayMusic(gMusic,-1);
                                startTime = SDL_GetTicks();

                                isRunning = 1;
                            }
                            else if(winState == 1|| winState == -1)
                            {
                                isRunning = 0;
                            }
                    }
                SDL_Color textColor = {0, 0, 0};
                string timeText;
                string temp3 = to_string(countdown);
                timeText = "Time: " + temp3;
                if(gCountDown.loadFromRenderedText(timeText, textColor, gRenderer, gFontTime))
                    {
                        gCountDown.render(10, 10, gRenderer);
                    }
                        if(lose)
                        {
                        Mix_PlayChannel(-1,PDead,0);
                        SDL_Delay(1000);
                        int loseState = showLose(button, gLoseTexture,gFontTitle, gWin, gStateBackground, gPlayTexture, gRenderer, menuStart);
                        if(loseState == 0)
                        {
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear(gRenderer);
                                for(int j = 0 ; j < enemies.size() ; ++j)
                                {
                                    delete enemies[j];
                                }
                                enemies.clear();
                                playerFrame = 0;
                                playerAttackFrame = 0;
                                playerDFrame = 0;
                                direct = 1;
                                mPosX = SCREEN_WIDTH / 2;
                                mPosY = SCREEN_HEIGHT / 2;
                                mVelX = 0;
                                mVelY = 0;
                                countdown = 120;
                                Mix_PlayMusic(gMusic,-1);

                                isRunning = 1;
                                lose = false;
                        }else if(loseState == 1|| loseState == -1)
                            isRunning = 0;
                        }

                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        isRunning = false;break;
                    }
                        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
                        if( avgFPS > 2000000 )
                        {
                            avgFPS = 0;
                        }
                        Player->handleEvent(e,direct,mVelX ,mVelY );
                }

                if (SDL_GetTicks() - lastTime >= 1000)
                {
                    slime *Slime =new slime();
                    Slime->enemyX = randomInt(0, 800);
                    int t = randomInt(0, 10);
                    Slime->enemyY = (t% 2 ==0) ? 800 : 0;
                    Slime->mEnemyBox.w = SPRITE_E_WIDTH - 30;
                    Slime->mEnemyBox.h = SPRITE_E_HEIGHT - 36;
                    enemies.push_back(Slime);
                    lastTime = SDL_GetTicks();
                }
                int eCount = enemies.size();
                eDead[eCount]= false;

                Player->move(mPosX,mPosY,mVelX ,mVelY,mPlayerBox);

                if(!lose)
                {

                     for(int i = 0 ; i < eCount ; ++i)
                                {
                                    if(checkCollision(mPlayerBox,enemies[i]->mEnemyBox)&& !eDead[i])
                                    {
                                        Uint32 currentTime1 = SDL_GetTicks();
                                        Uint32 elapsedTime1 = currentTime1 - isTouch;
                                        if (elapsedTime1 >= 7000) {
                                            lose = true;
                                        }
                                    }
                                }

                    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                    if( currentKeyStates[ SDL_SCANCODE_UP ] )
                    {
                        Player->render(mPosX , mPosY,gUpTexture,gRenderer,&gSpriteClipsU[playerFrame /RUN_U_ANIMATION]);
                        Player->updateFrame(RUN_U_ANIMATION , playerFrame);

                    }
                    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
                    {
                        Player->render(mPosX , mPosY,gDownTexture,gRenderer,&gSpriteClipsD[playerFrame /RUN_U_ANIMATION]);
                        Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                    }
                    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
                    {
                        Player->render(mPosX , mPosY,gLeftTexture,gRenderer,&gSpriteClipsL[playerFrame /RUN_U_ANIMATION]);
                        Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                    }
                    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
                    {
                        Player->render(mPosX , mPosY,gRightTexture,gRenderer,&gSpriteClipsR[playerFrame /RUN_U_ANIMATION]);
                        Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                    }else
                    {
                        bool attacking = false;
                        if(direct == 1)
                        {
                            if( currentKeyStates[ SDL_SCANCODE_Z ] )
                            {
                                attacking = 1;
                                Player->render(mPosX , mPosY,gAUTexture,gRenderer,&gSpriteClipsAU[playerFrame /A_U_ANIMATION]);
                                Player->updateFrame(A_U_ANIMATION , playerFrame);
                                for(int i = 0 ; i < eCount ; ++i)
                                {
                                    if(checkCollision2(mPlayerBox,enemies[i]->mEnemyBox))
                                    {
                                        eDead[i] = true;
                                    }
                                }

                            }else
                            {
                                Player->render(mPosX , mPosY,gIdleUTexture,gRenderer,&gSpriteClipsIU[playerFrame /RUN_U_ANIMATION]);
                                Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                            }
                        }else if(direct == 2)
                        {
                            if( currentKeyStates[ SDL_SCANCODE_Z ] )
                            {
                                attacking = 1;
                                Player->render(mPosX , mPosY,gADTexture,gRenderer,&gSpriteClipsAD[playerFrame /A_U_ANIMATION]);
                                Player->updateFrame(A_U_ANIMATION , playerFrame);
                                for(int i = 0 ; i < eCount ; ++i)
                                {
                                    if(checkCollision2(mPlayerBox,enemies[i]->mEnemyBox))eDead[i] =true;

                                }
                            }else
                            {
                                Player->render(mPosX , mPosY,gIdleTexture,gRenderer,&gSpriteClips[playerFrame /RUN_U_ANIMATION]);
                                Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                            }
                        }else if(direct == 3)
                        {
                            if( currentKeyStates[ SDL_SCANCODE_Z ] )
                            {
                                attacking = 1;
                                Player->render(mPosX , mPosY,gALTexture,gRenderer,&gSpriteClipsAL[playerFrame /A_U_ANIMATION]);
                                Player->updateFrame(A_U_ANIMATION , playerFrame);
                                for(int i = 0 ; i < eCount ; ++i)
                                {
                                    if(checkCollision2(mPlayerBox,enemies[i]->mEnemyBox))eDead[i] =true;
                                }
                            }else
                            {
                                Player->render(mPosX , mPosY,gIdleLTexture,gRenderer,&gSpriteClipsIL[playerFrame /RUN_U_ANIMATION]);
                                Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                            }
                        }else if (direct == 4)
                        {
                            if( currentKeyStates[ SDL_SCANCODE_Z ] )
                            {
                                attacking = 1;
                                Player->render(mPosX , mPosY,gARTexture,gRenderer,&gSpriteClipsAR[playerAttackFrame /A_U_ANIMATION]);
                                Player->updateFrame(A_U_ANIMATION , playerAttackFrame);
                                for(int i = 0 ; i < eCount ; ++i)
                                {
                                    if(checkCollision2(mPlayerBox,enemies[i]->mEnemyBox))eDead[i] =true;
                                }
                            }else
                            {
                                Player->render(mPosX , mPosY,gIdleRTexture,gRenderer,&gSpriteClipsIR[playerFrame /RUN_U_ANIMATION]);
                                Player->updateFrame(RUN_U_ANIMATION , playerFrame);
                            }
                        }
                        if(attacking)
                        {
                            Mix_VolumeChunk(attack,MIX_MAX_VOLUME/5);
                            Mix_PlayChannel(-1,attack,0);
                            attacking = false;
                        }
                    }

                        for(int i = 0 ; i < eCount ; ++i)
                        {
                            if(eDead[i] == true)
                            {
                                int tmp = i;
                                enemies[i]->render(gEDTexture,gRenderer,&gSpriteClipsED[enemies[i]->slimeDFrame/ENEMY_D_ANIMATION]);
                                enemies[i]->updateDFrame(ENEMY_D_ANIMATION,enemies[i]->slimeDFrame,enemies[i]->isDelete);
                                if(enemies[i]->isDelete == true){enemies.erase(enemies.begin() + tmp) , enemies[i]->isDelete = false;}
                            }else
                            {
                                enemies[i]->render(gETexture,gRenderer,&gSpriteClipsE[enemies[i]->slimeFrame/ENEMY_ANIMATION]);
                                enemies[i]->updateFrame(ENEMY_ANIMATION,enemies[i]->slimeFrame);
                                enemies[i]->move(mPosX,mPosY ,enemies[i]->mEnemyBox);
                            }
                        }
                    }


                SDL_RenderPresent( gRenderer );
                int frameTicks = capTimer.getTicks();
                if( frameTicks < SCREEN_TICK_PER_FRAME )
                {
                    SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
                }
            }
        }
    }
    return 0;
}

bool Init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING) == -1 )
    {
        cout << "Unable to initialize\n"; success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        gWindow = SDL_CreateWindow( "Escape Danger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

            if( gRenderer == NULL )
            {
                cout << "Could not create renderer\n"; success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags)){
                    cout << "Could not initialize SDL_Image! SDL_image Error: " << IMG_GetError() << '\n';
                    success = false;
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }
    }

    return success;
}


bool loadMedia()
{
	bool success = true;
    //--------player---------//
    if( !gIdleTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load idle texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < IDLE_ANIMATION; ++i)
        {
        gSpriteClips[i].x = i * SPRITE_WIDTH;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = SPRITE_WIDTH;
        gSpriteClips[i].h = SPRITE_HEIGHT;
        }
	}

    if( !gIdleUTexture.loadFromFile( "assets/player.png" ,gRenderer))
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < IDLE_U_ANIMATION; ++i)
        {
        gSpriteClipsIU[i].x = i * SPRITE_WIDTH;
        gSpriteClipsIU[i].y = 96;
        gSpriteClipsIU[i].w = SPRITE_WIDTH;
        gSpriteClipsIU[i].h = SPRITE_HEIGHT;
        }
	}

     if( !gIdleRTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < IDLE_ANIMATION; ++i)
        {
        gSpriteClipsIR[i].x = i * SPRITE_WIDTH;
        gSpriteClipsIR[i].y = 48;
        gSpriteClipsIR[i].w = SPRITE_WIDTH;
        gSpriteClipsIR[i].h = SPRITE_HEIGHT;
        }
	}

     if( !gIdleLTexture.loadFromFile( "assets/player2.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < IDLE_ANIMATION; ++i)
        {
        gSpriteClipsIL[i].x = i * SPRITE_WIDTH;
        gSpriteClipsIL[i].y = 48;
        gSpriteClipsIL[i].w = SPRITE_WIDTH;
        gSpriteClipsIL[i].h = SPRITE_HEIGHT;
        }
	}
        //
	if( !gUpTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < RUN_U_ANIMATION; ++i)
        {
        gSpriteClipsU[i].x = i * SPRITE_WIDTH;
        gSpriteClipsU[i].y = 240;
        gSpriteClipsU[i].w = SPRITE_WIDTH;
        gSpriteClipsU[i].h = SPRITE_HEIGHT;
        }
	}

	if( !gDownTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load down texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < RUN_D_ANIMATION; ++i)
        {
        gSpriteClipsD[i].x = i * SPRITE_WIDTH;
        gSpriteClipsD[i].y = 144;
        gSpriteClipsD[i].w = SPRITE_WIDTH;
        gSpriteClipsD[i].h = SPRITE_HEIGHT;
        }
	}

	if( !gLeftTexture.loadFromFile( "assets/player2.png" ,gRenderer) )
	{
		printf( "Failed to load left texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < RUN_L_ANIMATION; ++i)
        {
        gSpriteClipsL[i].x = i * SPRITE_WIDTH;
        gSpriteClipsL[i].y = 192;
        gSpriteClipsL[i].w = SPRITE_WIDTH;
        gSpriteClipsL[i].h = SPRITE_HEIGHT;
        }
	}

	if( !gRightTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load right texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < RUN_R_ANIMATION; ++i)
        {
        gSpriteClipsR[i].x = i * SPRITE_WIDTH;
        gSpriteClipsR[i].y = 192;
        gSpriteClipsR[i].w = SPRITE_WIDTH;
        gSpriteClipsR[i].h = SPRITE_HEIGHT;
        }
	}

	if( !gAUTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < A_U_ANIMATION; ++i)
        {
        gSpriteClipsAU[i].x = i * SPRITE_WIDTH;
        gSpriteClipsAU[i].y = 384;
        gSpriteClipsAU[i].w = SPRITE_WIDTH;
        gSpriteClipsAU[i].h = SPRITE_HEIGHT;
        }
	}
	if( !gADTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < A_U_ANIMATION; ++i)
        {
        gSpriteClipsAD[i].x = i * SPRITE_WIDTH;
        gSpriteClipsAD[i].y = 288;
        gSpriteClipsAD[i].w = SPRITE_WIDTH;
        gSpriteClipsAD[i].h = SPRITE_HEIGHT;
        }
	}
	if( !gARTexture.loadFromFile( "assets/player.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < A_U_ANIMATION; ++i)
        {
        gSpriteClipsAR[i].x = i * SPRITE_WIDTH;
        gSpriteClipsAR[i].y = 336;
        gSpriteClipsAR[i].w = SPRITE_WIDTH;
        gSpriteClipsAR[i].h = SPRITE_HEIGHT;
        }
	}
        if( !gALTexture.loadFromFile( "assets/player2.png" ,gRenderer) )
        {
            printf( "Failed to load press texture!\n" );
            success = false;
        }else
        {
            for (int i = 0; i < A_U_ANIMATION; ++i)
            {
            gSpriteClipsAL[i].x = (i + 2) * SPRITE_WIDTH;
            gSpriteClipsAL[i].y = 336;
            gSpriteClipsAL[i].w = SPRITE_WIDTH;
            gSpriteClipsAL[i].h = SPRITE_HEIGHT;
            }
        }
    if( !gDTexture.loadFromFile( "assets/player3.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < DEAD_ANIMATION; ++i)
        {
        gSpriteClipsD[i].x = i * SPRITE_WIDTH;
        gSpriteClipsD[i].y = 0;
        gSpriteClipsD[i].w = SPRITE_WIDTH;
        gSpriteClipsD[i].h = SPRITE_HEIGHT;
        }
	}


	//--------enemy---------//
	if( !gETexture.loadFromFile( "assets/slime.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < ENEMY_ANIMATION; ++i)
        {
        gSpriteClipsE[i].x = i * SPRITE_E_WIDTH;
        gSpriteClipsE[i].y = 188;
        gSpriteClipsE[i].w = SPRITE_E_WIDTH;
        gSpriteClipsE[i].h = SPRITE_E_HEIGHT;
        }
	}
    if( !gEDTexture.loadFromFile( "assets/slime.png" ,gRenderer) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}else
	{
	    for (int i = 0; i < ENEMY_D_ANIMATION; ++i)
        {
        gSpriteClipsED[i].x = i * SPRITE_E_WIDTH;
        gSpriteClipsED[i].y = 380;
        gSpriteClipsED[i].w = SPRITE_E_WIDTH;
        gSpriteClipsED[i].h = SPRITE_E_HEIGHT;
        }
	}

    //-----------background----------//
	if(!gBackground.loadFromFile("assets/map.png",gRenderer))
	{
		printf( "Failed to load stretching image!\n" );
		success = false;
	}
	if(!gStateBackground.loadFromFile("assets/bg.png",gRenderer))
	{
		printf( "Failed to load stretching image!\n" );
		success = false;
	}

	//------------menu------------//
	if(!gPlayTexture[0].loadFromFile("assets/Button/Play-On.png",gRenderer))
    {
		printf( "Failed to load stretching play!\n" );
		success = false;
    }
    if(!gPlayTexture[1].loadFromFile("assets/Button/Play-Off.png",gRenderer))
    {
		printf( "Failed to load stretching play!\n" );
		success = false;
    }
    //---------music------------//
    gMusic = Mix_LoadMUS("sounds/Background.wav");
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gWin = Mix_LoadMUS("sounds/win.wav");
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	PDead = Mix_LoadWAV("sounds/dead.wav");
    button = Mix_LoadWAV("sounds/Buttons.wav");
    attack = Mix_LoadWAV("sounds/atk.wav");
	//--------font-----------//
	gFont = TTF_OpenFont("fonts/Regular.ttf",20);
	gFontTitle = TTF_OpenFont("fonts/Regular.ttf",50);
	gFontTime = TTF_OpenFont("fonts/Regular.ttf",20);
	return success;
}

void close()
{
    gIdleTexture.free();
	gUpTexture.free();
	gDownTexture.free();
	gLeftTexture.free();
	gRightTexture.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
