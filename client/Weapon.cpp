//
//  Weapon.cpp
//  game-project
//
//  Created by Breno Antunes on 10/10/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL_mixer.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL_mixer.h>

#endif

#include "Weapon.h"
#include "Global.h"


Weapon::Weapon (int maxAmmo,int fireRate, WeaponType weapon){
    this->maxAmmo = maxAmmo;
    this->fireRate = fireRate;
    this->currentAmmo = maxAmmo;
    this->weaponType = weapon;
	this->bulletType = weapon.type;
}

void Weapon::Shoot(int x, int y, int angle){

	//printf("\n MAX AMMO: %d, CURRENT AMMO: %d",this->maxAmmo, this->currentAmmo );

	if (this->currentAmmo > 0 && mMap != NULL)
	{
		weaponType.angle = angle;

		bullets.push_back(new Bullet(x, y, weaponType, 0.8));
        

		this->currentAmmo--;
		Mix_PlayChannel(-1, weaponType.sShot, 0);
	}	
	else
	{
		Mix_PlayChannel(-1, weaponType.sEmpty, 0);
	}
}

void Weapon::Reload(int ammount)
{
	this->currentAmmo += ammount;
	if (this->currentAmmo > this->maxAmmo)
		this->currentAmmo = this->maxAmmo;

	Mix_PlayChannel(-1, weaponType.sReload, 0);
}

void Weapon::bulletReceived(int x, int y, WeaponType type, int id){
    std::map<int, Bullet*>::iterator tempBullet;
    tempBullet = bulletMap.find(id);
    
    //new bullet received
    if (tempBullet == bulletMap.end())
        bulletMap[id] = new Bullet(x, y, type, 0.8);
    else
        bulletMap[id]->setPosition(x, y);
}

void Weapon::removeBullet(int id){
    std::map<int, Bullet*>::iterator tempBullet;
    tempBullet = bulletMap.find(id);
    
    if (tempBullet != bulletMap.end())
    {
        bulletMap.erase(tempBullet);
    }
}


void Weapon::addBullet(int x, int y){
    bulletsReceived.push_back(new Bullet(x, y, weaponType, 0.8));
}
