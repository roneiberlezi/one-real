//
//  Weapon.h
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Weapon_h
#define Game_Project_Weapon_h

#include "Utils.h"
#include <vector>
#include <map>
#include "Bullet.h"

class Weapon{
public:
    int maxAmmo;
    int currentAmmo;
	int fireRate; //shots by second
	int bulletType;
	WeaponType weaponType;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> bulletsReceived;
    std::map<int, Bullet*> bulletMap;
    
    void Shoot(int x, int y, int angle);
	void Reload(int ammount);
    void addBullet(int x, int y);
    
    void removeBullet(int id);
    void bulletReceived(int x, int y, WeaponType type, int id);
    
    Weapon (int maxAmmo,int fireRate, WeaponType weapon);
};

#endif
