//
//  Projectile.h
//  Game Project
//
//  Created by Ronei Berlezi on 06/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Bullet_h
#define Game_Project_Bullet_h

#include "Agent.h"

class Bullet : public Agent{
public:
    WeaponType info;
  //  SDL_Position direction;
    Bullet( int x, int y, WeaponType weapon, float colisionFactor);
    void render(SDL_Surface *screenSurface, SDL_Point cameraPosition);
    void setPosition(int x, int y);
    
/*public:
    Bullet();
    void Update();
    void Fire(float startX, float startY, float xSpeed, float ySpeed);
    void Draw();
    
private:
    bool alive;
    float x, y;
    float xv, yv;*/
};

#endif
