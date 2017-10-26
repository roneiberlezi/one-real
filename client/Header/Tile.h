//
//  Tile.h
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __GP__Tile__
#define __GP__Tile__


#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>

#endif

class Tile
{
public:
    //Initializes the variables
    Tile(int id, SDL_Surface* tile, int tileWidth, int tileHeight);
    
    //The attributes of the tile
    SDL_Rect square;
    SDL_Surface* tile;
    
    //Tile id
    int id;
};

#endif /* defined(__GP__Tile__) */
