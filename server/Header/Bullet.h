//
//  Projectile.h
//  Game Project
//
//  Created by Ronei Berlezi on 06/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Bullet_h
#define Game_Project_Bullet_h

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>

#endif

class Bullet{
public:
	//  SDL_Position direction;
	int x, y, angle, playerId, type, velocity, bulletId;
    bool destroy = false;
    SDL_Rect collisionRect;
    
    static const int width = 16;
    static const int height = 16;
    float collisionFactor = 1;
    int deltaTime;

	Bullet(int x, int y, int angle, int id, int type, int bulletId);
	void setPosition(int x, int y);
	void nextPosition();
};

#endif
