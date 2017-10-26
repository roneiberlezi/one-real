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
#include <SDL2/SDL_mixer.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_mixer.h>

#endif

#include <string>
#include <vector>

Uint32 color32(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 alpha);


//COMENTARIO DIOGO
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

struct WeaponType{
    int type;
    int damage;
    int velocity;//pixels por segundo
    int fireRate;
    SDL_Surface* bulletSurface;
    SDL_Surface* weaponSurface;
    Mix_Chunk* sShot;
    Mix_Chunk* sEmpty;
    Mix_Chunk* sReload;
    
    int angle;
    std::string bSprite;
};

bool loadMedia(std::string filename, SDL_Surface ** destination);

void drawUnfilledRect(SDL_Surface* dst, SDL_Rect* rect, int line_thickness, Uint32 color);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);


std::vector<std::string> split(const std::string &s, char delim);

#endif
