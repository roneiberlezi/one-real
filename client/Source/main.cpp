//
//  main.cpp
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#endif

#include <stdio.h>
#include "Global.h"
#include "Utils.h"
#include "Agent.h"
#include <map>
#include "Network.h"
#include "Ranking.h"
#include "Collidable.h"
#include "pauseMenu.h"

//tudo junto e misturado

#include <math.h>
//Frees media and shuts down SDL
void close();


bool load_media()
{
	//Loading success flag
	bool success = true;

	//COLOCAR AQUI PRA CARREGAR MAPAS E SPRITES EM GERAL!

	//Load music
	gMusic = Mix_LoadMUS("resources/sounds/mansion.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
    
    gOpenning = Mix_LoadWAV("resources/sounds/shot_1.wav");
    if(gOpenning ==NULL){
        printf ("Failed to load splash.mp3 sound! SDL_Mixer Error: %s\n",Mix_GetError());
        success=false;
    }
    
    gKill = Mix_LoadWAV("resources/sounds/kill.wav");
    if(gKill ==NULL){
        printf ("Failed to load kill.wav sound! SDL_Mixer Error: %s\n",Mix_GetError());
        success=false;
    }

	gFirstBlood = Mix_LoadWAV("resources/sounds/firstblood.wav");
	if (gFirstBlood == NULL){
		printf("Failed to load firstblood.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gDoubleKill = Mix_LoadWAV("resources/sounds/doublekill.wav");
	if (gDoubleKill == NULL){
		printf("Failed to load doublekill.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gTripleKill = Mix_LoadWAV("resources/sounds/triplekill.wav");
	if (gTripleKill == NULL){
		printf("Failed to load triplekill.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gUltraKill = Mix_LoadWAV("resources/sounds/ultrakill.wav");
	if (gUltraKill == NULL){
		printf("Failed to load ultrakill.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gGodLike = Mix_LoadWAV("resources/sounds/godlike.wav");
	if (gGodLike == NULL){
		printf("Failed to load godlike.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHeal = Mix_LoadWAV("resources/sounds/health.wav");
	if (gHeal == NULL){
		printf("Failed to load heal.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
		success = false;
	}
    
    gGunPickUp = Mix_LoadWAV("resources/sounds/guncock.wav");
    if (gGunPickUp == NULL){
        printf("Failed to load guncock.wav sound! SDL_Mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    
    //Weapon Sounds
    //Load sound effects
    weapon1.sShot = Mix_LoadWAV("resources/sounds/lazer3.wav");
    if (weapon1.sShot == NULL) printf("Failed to load shot_0.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    weapon1.sEmpty = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
    if (weapon1.sEmpty == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    weapon1.sReload = Mix_LoadWAV("resources/sounds/ammo_pickup.wav");
    if (weapon1.sReload == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	weapon2.sShot = Mix_LoadWAV("resources/sounds/possiblelaser.wav");
	if (weapon2.sShot == NULL) printf("Failed to load shot_1.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon2.sEmpty = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
	if (weapon2.sEmpty == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon2.sReload = Mix_LoadWAV("resources/sounds/ammo_pickup.wav");
	if (weapon2.sReload == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	weapon3.sShot = Mix_LoadWAV("resources/sounds/silencedgunshot.wav");
	if (weapon3.sShot == NULL) printf("Failed to load shot_2.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon3.sEmpty = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
	if (weapon3.sEmpty == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon3.sReload = Mix_LoadWAV("ammo_pickup.wav");
	if (weapon3.sReload == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	weapon4.sShot = Mix_LoadWAV("resources/sounds/lasershort.wav");
	if (weapon4.sShot == NULL) printf("Failed to load shot_2.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon4.sEmpty = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
	if (weapon4.sEmpty == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon4.sReload = Mix_LoadWAV("resources/sounds/ammo_pickup.wav");
	if (weapon4.sReload == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	weapon5.sShot = Mix_LoadWAV("resources/sounds/biglaser.wav");
	if (weapon5.sShot == NULL) printf("Failed to load shot_3.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon5.sEmpty = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
	if (weapon5.sEmpty == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	weapon5.sReload = Mix_LoadWAV("resources/sounds/ammo_pickup.wav");
	if (weapon5.sReload == NULL) printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	
	//Load sound effects
	gShot0 = Mix_LoadWAV("resources/sounds/shot_0.wav");
	if (gShot0 == NULL)
	{
	printf("Failed to load shot_0.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	success = false;
	}

	gEmptyWeapon = Mix_LoadWAV("resources/sounds/empty_weapon.wav");
	if (gEmptyWeapon == NULL)
	{
		printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gReloadWeapon = Mix_LoadWAV("resources/sounds/ammo_pickup.wav");
	if (gReloadWeapon == NULL)
	{
		printf("Failed to load empty_weapon.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gWeaponPick = Mix_LoadWAV("resources/sounds/weapon_pickup2.wav");
	if (gWeaponPick == NULL)
	{
		printf("Failed to load weapon_pickup2.wav sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Destroy console
    mConsole->~Console();
    mConsole = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

	//Free the sound effects
	Mix_FreeChunk(gShot0);
	Mix_FreeChunk(gEmptyWeapon);
	Mix_FreeChunk(gReloadWeapon);
	gShot0 = NULL;
	gEmptyWeapon = NULL;
	gReloadWeapon = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Network Destroy
	if (net != NULL)
	{
		if (net->connected)
		{
			net->~network();
			net = NULL;
		}
	}

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	
}

bool init()
{
    //command map for console
    std::map< std::string, Command* > commandMap;
    commandMap["load"] = new CommandLoad();
    commandMap["player"] = new CommandPlayerDemo();
	commandMap["connect"] = new CommandConnect();
	commandMap["disconnect"] = new CommandDisconnect();
    commandMap["demo"] = new CommandDemoServer();
    
	//Maps
    maps[0] = "resources/maps/smallmap";
    maps[1] = "resources/maps/map2";
    maps[2] = "resources/maps/map3";
    maps[3] = "resources/maps/map4";
    
    //WEAPON DEFINITIONS
    //weapon1
    weapon1.type = 0;
    weapon1.damage = 10;
    weapon1.fireRate = 10;
    loadMedia("resources/images/weapons/w1.png", &weapon1.weaponSurface);
    loadMedia("resources/images/weapons/b5.png", &weapon1.bulletSurface);

	//weapon2
	weapon2.type = 1;
	weapon2.damage = 20;
    weapon2.fireRate = 8;
	loadMedia("resources/images/weapons/w2.png", &weapon2.weaponSurface);
	loadMedia("resources/images/weapons/b2.png", &weapon2.bulletSurface);
	
	//weapon3
	weapon3.type = 2;
	weapon3.damage = 30;
    weapon3.fireRate = 6;
	loadMedia("resources/images/weapons/w3.png", &weapon3.weaponSurface);
	loadMedia("resources/images/weapons/b8.png", &weapon3.bulletSurface);

	//weapon4
	weapon4.type = 3;
	weapon4.damage = 40;
    weapon4.fireRate = 6;
	loadMedia("resources/images/weapons/w4.png", &weapon4.weaponSurface);
	loadMedia("resources/images/weapons/b9.png", &weapon4.bulletSurface);

	//weapon5
	weapon5.type = 4;
	weapon5.damage = 50;
    weapon5.fireRate = 3;
	loadMedia("resources/images/weapons/w6.png", &weapon5.weaponSurface);
	loadMedia("resources/images/weapons/b7.png", &weapon5.bulletSurface);

	//Pre-Loading Itens
	loadMedia("resources/images/itens/health.png", &health);
	loadMedia("resources/images/itens/ammo.png", &ammo);
    loadMedia("resources/images/itens/weapon.png", &weaponBox);

	//Death Sprite
	loadMedia("resources/images/player/dead.png", &dead);
    
    //Pre-Load player sprite
    loadMedia("resources/images/player/SpriteSheet.png", &playerSprite);
    
    //Initialization flag
    bool success = true;

    //Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "One Real 1.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
            
        }
    }
    
    // Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {
        printf("TTF_Init() Failed: %s", TTF_GetError());
        success = false;
    }
    else{
        font = TTF_OpenFont(fontFileName.c_str(), 12);
        if (font == NULL){
            printf("TTF_OpenFont() Failed: %s", TTF_GetError());
            success = false;
        }
    }

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
    
    mConsole = new Console(gScreenSurface, 0, 0, SCREEN_WIDTH, font, CONSOLE_TEXT_SIZE, CONSOLE_TEXT_COLOR, CONSOLE_BACKGROUD_COLOR, commandMap, GAME_VERSION);
    
	mainMenu = new Menu(gScreenSurface, font, CONSOLE_TEXT_SIZE, gWindow);

	if (!load_media())
		success = false;

		
    return success;
}


void move(Agent* agent)
{
    bool Collision = false;
    SDL_Point newPos;

    //Move the agent left or right
    newPos.x = agent->mMovement.position.x + round(agent->mMovement.velX * ((SDL_GetTicks() - agent->deltaTime)/1000.0));
    newPos.y = agent->mMovement.position.y + round(agent->mMovement.velY * ((SDL_GetTicks() - agent->deltaTime)/1000.0));
    
    if (agent->mMovement.velX != 0 || agent->mMovement.velY != 0) {
        agent->deltaTime = SDL_GetTicks();
    }
    
    agent->setColisionRectPosition(newPos.x, newPos.y);
    
    //If the agent collided or went too far to the left or right
    if (agent->colisionRect.x < 0 || agent->colisionRect.y < 0){
        Collision = true;
        return;
    }
    
    for (int x = 0; x < mMap->sizeX; x++) {
        for (int y = 0; y < mMap->sizeY; y++) {
            if (mMap->layer[1]->layer[x][y] != 0) {
                Agent object = Agent(x*TILE_WIDTH, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, NULL, 1);
                if (Collidable::checkCollision(agent->colisionRect, object.colisionRect))
                    Collision = true;
            }
        }
    }

    
    if (!Collision){
        agent->setPosition(newPos.x, newPos.y, mMap->sizeX, mMap->sizeY);
    }
    
    
}

void handleKeys(SDL_Event* e){
    mConsole->handleKeys(e);
    
    if (mPlayer != NULL) {
        mPlayer->handleEvent(e);
        
    }
}

void drawEmptyBg(){
    SDL_Rect emptybg;
    emptybg.w = SCREEN_WIDTH;
    emptybg.h = SCREEN_HEIGHT;
    emptybg.x = 0;
    emptybg.y = 0;
    
    SDL_FillRect(gScreenSurface, &emptybg, color32(0, 0, 0, 0));
}

void drawEnemies(){
    for (std::map<int,Player*>::iterator it=enemiesMap.begin(); it!=enemiesMap.end(); ++it){
        it->second->renderOnMap(gScreenSurface, mPlayer->mMovement.cameraPosition,&messages);
    }
}

void drawItems(){
    for (std::map<int,Item*>::iterator it=itensMap.begin(); it!=itensMap.end(); ++it){
        it->second->renderAsItem(gScreenSurface, mPlayer->mMovement.cameraPosition);
    }
}

int main( int argc, char* args[])
{
    int startTime;
	int exit = 0;
    int FPS = 60;
    int startTimeNetwork;
    int PPS = 15;
    int controlMenu= 0;
    Ranking *rank = new Ranking();
    bool rankEnable=false;
    pauseMenu *pauseMenu = new class pauseMenu();
    
    startTimeNetwork = SDL_GetTicks();

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }else{
        controlMenu = mainMenu->showMenu();
        if (controlMenu == 3){
            quit = true;
        }else{
            if (Mix_PlayingMusic() == 0)
            {
                //Play the music
                Mix_PlayMusic(gMusic, -1);
                printf("\n Playing Music");
            }

            while (!quit)
            {
                startTime = SDL_GetTicks();
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                while (SDL_PollEvent(&event))
                {
                    rankEnable = false;
                    if (state[SDL_SCANCODE_TAB]){
                        net->requestScore();
                        rankEnable = true;
                    }
                    if (event.type == SDL_QUIT){
                        quit = true;
                    }
                    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
                        if(event.key.keysym.sym==SDLK_ESCAPE)
                            if(event.type==SDL_KEYDOWN)
                                pauseMenu->enablePause();
                        handleKeys(&event);
                    }
                    if (event.type == SDL_MOUSEMOTION){
                        if(mPlayer!=NULL){
                            mPlayer->handleMouseEvent(&event);
                        }
                        
                    }
                    if(event.type == SDL_MOUSEBUTTONDOWN){
                        if(pauseMenu->enabled){
                            int x = event.motion.x;
                            int y = event.motion.y;
                            if ( (x >= pauseMenu->textOp[0].x) && (x <= (pauseMenu->textOp[0].x + pauseMenu->textSurOP[0]->w))){
                                if ((y >= pauseMenu->textOp[0].y) && (y <= (pauseMenu->textOp[0].y + pauseMenu->textSurOP[0]->h))){
                                    pauseMenu->enablePause();
                                }
                            }
                            if ((x >= pauseMenu->textOp[1].x) && (x <= (pauseMenu->textOp[1].x + pauseMenu->textSurOP[1]->w))){
                                if ((y >= pauseMenu->textOp[1].y) && (y <= (pauseMenu->textOp[1].y + pauseMenu->textSurOP[1]->h))){
                                    
                                    quit=true;
                                }
                            }
                        }else{
                            if(mPlayer!=NULL){
                                mPlayer->handleMouseEvent(&event);
                            }
                        }
                    }
                }
                
                
                if (net != NULL)
                    if (net->connected)
                    {
                        //Online stuff here
                        net->recv(mPlayer, &enemiesMap,&itensMap);

                        

                        if (net->ready && mMap == NULL)
                        {
                            //Start map
                            mMap = new Map(maps[currentMap], TILE_WIDTH, TILE_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
                            
                            if (mMap->fileNotFound) {
                                if (mMap != NULL)
                                    mMap->~Map();
                                mMap = NULL;
                            }
                        }

                        if((SDL_GetTicks()-startTimeNetwork) > 1000/PPS)
                        {
                            net->send(mPlayer);
                            net->sendShot(mPlayer);
                            startTimeNetwork = SDL_GetTicks();
                        }
                    }
                
                drawEmptyBg();
                
                if (mMap != NULL) {
                    
                    mMap->drawMap(gScreenSurface, SCREEN_WIDTH, SCREEN_HEIGHT, mPlayer->mMovement.cameraPosition);
                    
                    drawItems();
                    
                    drawEnemies();
                    
                    mPlayer->render(gScreenSurface);
                    mPlayer->renderBullet(gScreenSurface);
                    
                    if (mPlayer->alive)
                        move(mPlayer);
                    
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    
                    mPlayer->setLookPosition(x, y);
                }
                
                mConsole->update();
                if(rankEnable){
                    
                    rank->rankingDraw(mPlayer, &enemiesMap, gScreenSurface, font);
                }
                if(pauseMenu->enabled){
                    pauseMenu->showPauseMenu(gScreenSurface,font);
                }
                if(endGame){
                    SDL_Rect scorePosition;
                    SDL_Surface* scoreSurface;
                    SDL_Color color{255,255,255,0};
                    TTF_Font* messageEndGameFont;
                    messageEndGameFont= TTF_OpenFont("resources/fonts/halloween.ttf", 50);
                    std::stringstream timerNext;
                    std::string victoryString;
                    std::string bigestKiller = mPlayer->nickName;
                    int biggerKill=mPlayer->kills;
                    
                    
                    for(std::map<int, Player*>::iterator iterator = enemiesMap.begin();iterator != enemiesMap.end(); iterator++ ){
                        if(iterator->second->kills > biggerKill){
                            biggerKill = iterator->second->kills;
                            bigestKiller = iterator->second->nickName;
                        }
                    }
                    victoryString = bigestKiller + " ganhou o round !";
                    scoreSurface = TTF_RenderText_Solid(messageEndGameFont,  victoryString.c_str(),color);
                    scorePosition.x = (gScreenSurface->w/2) - (scoreSurface->w/2);
                    scorePosition.y = (gScreenSurface->h/2) - (scoreSurface->h/2);
                    SDL_BlitSurface(scoreSurface,NULL,gScreenSurface,&scorePosition);
                    
                    int timer;
                    timer = 10 - ((SDL_GetTicks() - timerNextRound)/1000);
                    
                    if (timer < 0)
                        timer = 0;
                    
                    timerNext << timer;
                    victoryString = timerNext.str();
                    scoreSurface = TTF_RenderText_Solid(messageEndGameFont, victoryString.c_str(), color);
                    
                    scorePosition.x = (gScreenSurface->w/2);
                    scorePosition.y = (gScreenSurface->h/2) - (scoreSurface->h/2) + 50;
                    
                    SDL_BlitSurface(scoreSurface,NULL,gScreenSurface,&scorePosition);
                    
                    SDL_FreeSurface(scoreSurface);
                }
                
                if(1000/FPS>(SDL_GetTicks()-startTime))
                    SDL_Delay(1000/FPS-(SDL_GetTicks()-startTime));
                
                SDL_UpdateWindowSurface(gWindow);
                    
                }
        net->~network();
        mPlayer->~Player();
        mMap->~Map();
        }
    }
    return 0;
}
