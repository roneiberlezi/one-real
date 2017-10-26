//
//  Player.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Player.h"


Player::Player(int id){
    init(id);
}

Player::Player(int id, TCPsocket socket){
    this->socket = socket;
    init(id);
}

void Player::init(int id){
    this->id = id;
    position.x = 0;
    position.y = 0;
    bulletType = 0;
    this->kills = 0;
    this->deaths = 0;
    this->killStreak = 0;
    
    collisionRect.x = position.x;
    collisionRect.y = position.y;
    collisionRect.w = width * collisionFactor;
    collisionRect.h = height * collisionFactor;
}

//set the new player position, return true if it has changed since the last update. If returns true, the server shall send the new position to all players.
bool Player::setPosition(int x, int y){
    bool changed = false;
    if (position.x != x || position.y != y) {
        changed = true;
    }
    
    position.x = x;
    position.y = y;
    
    //sets the new rect collicion position
    collisionRect.x = x + (width*0.33);
    collisionRect.y = y + height/3;
    
    return changed;
}

void Player::initRoundValues(){
    kills = 0;
    deaths = 0;
    currentHP = 100;
    killStreak = 0;
    alive = true;
}

void Player::death(int ticks){
    deaths++;
    killStreak = 0;
    
    currentHP = 0;
    alive = false;
    deathTime = ticks;
}
