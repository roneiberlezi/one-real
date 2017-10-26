//
//  Projectile.cpp
//  game-project
//
//  Created by Breno Antunes on 10/10/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#include "Bullet.h"


Bullet::Bullet(int x, int y, int angle, int playerId, int type, int bulletId){
    destroy = false;
	this->x = x;
	this->y = y;
	this->angle = angle;
	this->playerId = playerId;
	this->type = type;
    this->bulletId = bulletId;
    
    
    collisionRect.x = x;
    collisionRect.y = y;
    collisionRect.w = width - 3;
    collisionRect.h = height - 3;
    
    velocity = 1000;
    
    deltaTime = SDL_GetTicks();
}

void Bullet::setPosition(int x, int y){
    this->x += x;
    this->y += y;
    
    collisionRect.x = this->x + 3;
    collisionRect.y = this->y + 3;
    
    //if the position not valid, set the property to destroy the bullet
	if (this->x < -16 || this->y < -16) {
        destroy = true;
	}
}

void Bullet::nextPosition()
{

}