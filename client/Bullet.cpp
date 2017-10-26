//
//  Projectile.cpp
//  game-project
//
//  Created by Breno Antunes on 10/10/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#include "Bullet.h"


Bullet::Bullet(int x, int y, WeaponType weapon, float colisionFactor) : Agent(x, y, weapon.bulletSurface->w, weapon.bulletSurface->h, weapon.bulletSurface, colisionFactor){
    this->info = weapon;
}

void Bullet::render(SDL_Surface *screenSurface, SDL_Point cameraPosition){
    destRect.x = mMovement.position.x - cameraPosition.x;
    destRect.y = mMovement.position.y - cameraPosition.y;
    SDL_BlitSurface(texture, &sourceRect, screenSurface, &destRect);
}

void Bullet::setPosition(int x, int y){
        //Align collider to center of agent
        if (x < 0 || y < 0) {
            return;
        }
        
        mMovement.position.x = x;
        mMovement.position.y = y;
    
        //mCollider.x = x;
        //mCollider.y = y;
        //destRect.x = mMovement.screenPosition.x;
        //destRect.y = mMovement.screenPosition.y;
}