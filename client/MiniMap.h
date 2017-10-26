//
//  MiniMap.h
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __GP__MiniMap__
#define __GP__MiniMap__


#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>

#endif

#include <stdio.h>
#include "Utils.h"
//
class MiniMap{
public:
    int mapSizeX;
    int mapSizeY;
    int screenWidth;
    int screenHeight;
    int tileWidth;
    int tileHeight;
    
    SDL_Rect position;
    SDL_Rect miniMap;
    SDL_Point mapOffset;
    int horizontalTiles;
    int verticalTiles;
    
    MiniMap(int tileWidth, int tileHeight, int screenWidth, int screenHeight);
    
    void draw(SDL_Surface* screen, int x_offset, int y_offset);
    
    void setMapSize(int x, int y);
};


#endif /* defined(__GP__MiniMap__) */
