//
//  Global.cpp
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Global.h"

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const std::string RESOURCE_PATH = "resources/";

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool quit = false;
SDL_Event event;

//Console information
Console* mConsole;
TTF_Font* font;
std::string fontFileName = "resources/fonts/arial.ttf";
const SDL_Color CONSOLE_TEXT_COLOR = { 255, 255, 255 };
const Uint32 CONSOLE_BACKGROUD_COLOR = color32(48, 56, 138, 0);
const int CONSOLE_TEXT_SIZE = 12;
const std::string GAME_VERSION = "Unreal 1.0";


//Map variables
Map* mMap = NULL;
int currentMap;
const char* maps[10];


//Player variables
Player* mPlayer;

//Network
network* net = NULL;

//Menu
Menu* mainMenu = NULL;
char* nickMenu = new char[50];
char* ipMenu = new char[20];

//Game Ended
bool endGame = false;
int timerNextRound;

//Player map
std::map<int, Player*> enemiesMap;

//Item map
std::map<int, Item*> itensMap;

//Background Music
Mix_Music *gMusic = NULL;
Mix_Chunk *gOpenning = NULL;

//The sound effects that will be used
Mix_Chunk *gShot0 = NULL;
Mix_Chunk *gShot1 = NULL;
Mix_Chunk *gShot2 = NULL;
Mix_Chunk *gShot3 = NULL;
Mix_Chunk *gHit = NULL;
Mix_Chunk *gWeaponPick = NULL;
Mix_Chunk *gEmptyWeapon = NULL;
Mix_Chunk *gReloadWeapon = NULL;
Mix_Chunk *gKill = NULL;
Mix_Chunk *gFirstBlood = NULL;
Mix_Chunk *gDoubleKill = NULL;
Mix_Chunk *gTripleKill = NULL;
Mix_Chunk *gUltraKill = NULL;
Mix_Chunk *gGodLike = NULL;
Mix_Chunk *gHeal = NULL;
Mix_Chunk *gGunPickUp = NULL;

//pre-defined weapons for the whole game
WeaponType weapon1;
WeaponType weapon2;
WeaponType weapon3;
WeaponType weapon4;
WeaponType weapon5;

//Items
SDL_Surface* health;
SDL_Surface* ammo;
SDL_Surface* dead;
SDL_Surface* weaponBox;

//player
SDL_Surface* playerSprite;

//Messages
std::vector<std::string> messages;
