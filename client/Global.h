//
//  Global.h
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __Game_Project__Global__
#define __Game_Project__Global__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_mixer.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#endif

#include <stdio.h>
#include "Console.h"
#include "Utils.h"
#include "Map.h"
#include "Player.h"
#include "Network.h"
#include "Menu.h"
#include "Item.h"

extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

extern bool quit;
extern SDL_Event event;

//Console information
extern Console* mConsole;
extern TTF_Font* font;
extern std::string fontFileName;
extern const SDL_Color CONSOLE_TEXT_COLOR;
extern const Uint32 CONSOLE_BACKGROUD_COLOR;
extern const int CONSOLE_TEXT_SIZE;
extern const std::string GAME_VERSION;


//Map variables
extern Map* mMap;

//Player variables
extern Player* mPlayer;


//Network
extern network* net;

//Menu
extern Menu* mainMenu;
extern char* nickMenu;
extern char* ipMenu;

//Game Ended
extern bool endGame;
extern int timerNextRound;

//Player map
extern std::map<int, Player*> enemiesMap;
extern int currentMap;
extern const char* maps[10];

//Item map
extern std::map<int, Item*> itensMap;

//Background Music
extern Mix_Music *gMusic;
extern Mix_Chunk *gOpenning;

//The sound effects that will be used
extern Mix_Chunk *gShot0;
extern Mix_Chunk *gShot1;
extern Mix_Chunk *gShot2;
extern Mix_Chunk *gShot3;
extern Mix_Chunk *gHit;
extern Mix_Chunk *gWeaponPick;
extern Mix_Chunk *gEmptyWeapon;
extern Mix_Chunk *gReloadWeapon;
extern Mix_Chunk *gKill;
extern Mix_Chunk *gFirstBlood;
extern Mix_Chunk *gDoubleKill;
extern Mix_Chunk *gTripleKill;
extern Mix_Chunk *gUltraKill;
extern Mix_Chunk *gGodLike;
extern Mix_Chunk *gHeal;
extern Mix_Chunk *gGunPickUp;

//pre-defined weapons for the whole game
extern WeaponType weapon1;
extern WeaponType weapon2;
extern WeaponType weapon3;
extern WeaponType weapon4;
extern WeaponType weapon5;

//Items
extern SDL_Surface* health;
extern SDL_Surface* ammo;
extern SDL_Surface* dead;
extern SDL_Surface* weaponBox;

//player
extern SDL_Surface* playerSprite;

//Messages
extern std::vector<std::string> messages;


#endif /* defined(__Game_Project__Global__) */
