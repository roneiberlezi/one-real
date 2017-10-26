//
//  Map.h
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __GP__Map__
#define __GP__Map__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#endif

#include "Layer.h"
#include <vector>
#include "Tile.h"
#include "TileSet.h"
#include "MiniMap.h"

class Map
{
public:
    SDL_Rect area;
    int layerAmount;
    int sizeX;
    int sizeY;
    std::vector<Layer*> layer;
    SDL_RWops* file;
    int tileSetNumber;
    bool fileNotFound = false;
    int screenWidth;
    int screenHeight;

    
    MiniMap* miniMap;
    
    TileSet* currentTileSet;
    
    //Constructor to load a map
    Map(const char* fileName, int tileWidth
        , int tileHeight, int screenWidth, int screenHeight);
    
    
    void drawMap(SDL_Surface* screen, int width, int height,SDL_Point cameraPosition);
    void drawLayer(SDL_Surface* screen, int layer_, std::vector<Tile*> tileSet, int width, int height, int posx, int posy);
    
    bool save(const char* fileName);
    ~Map();
private:
    int tileWidth;
    int tileHeight;
};



#endif /* defined(__GP__Map__) */
