//
//  MiniMap.h
//  Map Editor
//
//  Created by Ronei Berlezi on 29/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __Map_Editor__MiniMap__
#define __Map_Editor__MiniMap__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Utils.h"

class MiniMap{
public:
    int mapSizeX;
    int mapSizeY;
    int screenWidth;
    int screenHeight;
    int tileWidth;
    int tileHeight;
    int menuWidth;
    
    SDL_Rect position;
    SDL_Rect miniMap;
    SDL_Point mapOffset;
    int horizontalTiles;
    int verticalTiles;
    
    MiniMap(int tileWidth, int tileHeight, int screenWidth, int screenHeight, int menuWidth);
    
    void draw(SDL_Surface* screen, int x_offset, int y_offset);
    
    void setMapSize(int x, int y);
};

#endif /* defined(__Map_Editor__MiniMap__) */
