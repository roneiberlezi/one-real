//
//  TileSet.h
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __GP__TileSet__
#define __GP__TileSet__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include "Tile.h"


class TileSet{
public:
    std::string tileSetName;
    std::string fileFormat;
    
    //Vector to store all tiles from tile set
    std::vector<Tile*> tiles;
    
    int tileWidth;
    int tileHeight;
    int tileSetNumber;
    int tile_amount;
    
    std::vector<std::string> mTileSets;
    int tileSetAmount[1];
    
    TileSet(int tileWidth, int tileHeight, int tileSetNumber);
private:
    void loadTileSet();
    bool loadMedia(std::string fileName, SDL_Surface ** destination);
};

#endif /* defined(__GP__TileSet__) */
