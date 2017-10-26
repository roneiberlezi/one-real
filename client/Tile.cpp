//
//  Tile.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Tile.h"

Tile::Tile(int id, SDL_Surface* tile, int tileWidth, int tileHeight){
    //set the offsets
    this->id = id;
    this->tile = tile;
    square.x = 0;
    square.y = 0;
    
    //Set the collision box
    square.w = tileWidth;
    square.h = tileHeight;
}