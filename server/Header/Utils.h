//
//  Utils.h
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Utils_h
#define Game_Project_Utils_h

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>

#endif

#include <string>
#include <vector>

Uint32 color32(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 alpha);

const struct{
    //SERVER COMMANDS
    int NEW_PLAYER = 0;
    int PLAYER_POSITION = 1;
    int PLAYER_DISCONECTED = 2;
    int BULLETS = 3;
    int PLAYER_HP = 4;
    int KILL_OCCURRED = 5;
    int NICKNAME = 9;
    int PLAYER_SCORE = 11;
    int ITEM_SPAWN = 12;
    int PLAYER_RESPAWN = 13;
    int ITEM_PICKED_UP = 14;
    int REMOVE_BULLET = 15;
    int ROUND_END = 16;
    int ROUND_START = 17;
    
    //CLIENT COMMANDS
    int SEND_PLAYER_POSITION = 21;
    int SEND_BULLET = 23;
    int REQUEST_SCORE = 22;
    int REQUEST_PLAYER_NAME = 24;
} MESSAGE_TYPE;

struct Movement{
    int speed = 9;
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;
    int velX = 0;
    int velY = 0;
    SDL_Point position;//position on map for drawing the sprite on the camera
    SDL_Point centerPosition;
    SDL_Point screenPosition;//position for drawing the sprite on screen
    SDL_Point lookPosition;
    SDL_Point cameraPosition;//start position for drawing the map on screen
    int lookAngle;
    
};

struct BulletInfo{
    int damage;
    int velocity;//pixels por segundo
    SDL_Surface* texture;
    int width;
    int height;
    int angle;
    std::string bSprite;
    SDL_Surface* bulletSurface;
};

bool loadMedia(std::string filename, SDL_Surface ** destination);

void drawUnfilledRect(SDL_Surface* dst, SDL_Rect* rect, int line_thickness, Uint32 color);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);


std::vector<std::string> split(const std::string &s, char delim);

#endif
