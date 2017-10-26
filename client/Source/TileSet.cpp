//
//  TileSet.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

//
//  TileSet.cpp
//  Map Editor
//
//  Created by Ronei Berlezi on 28/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, int tileSetNumber){
    //mTileSets.push_back("space");
	//this->tileSetAmount[1] = 110;
	
    this->fileFormat = ".bmp";
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->tileSetNumber = tileSetNumber;
    //tileSetName = mTileSets[tileSetNumber];
    tileSetName = "resources/images/maps/space";
    this->tile_amount = 110;
    //    this->tile_amount = tileSetAmount[tileSetNumber];
	
	
    
    loadTileSet();
}


void TileSet::loadTileSet(){
    std::string stringBuffer;
    //std::string tilePosition;
    for (int i = 0; i < tile_amount; i++){
        stringBuffer = tileSetName;
        stringBuffer.append("/");
        stringBuffer.append(tileSetName);
        stringBuffer.append(std::to_string(i));
        stringBuffer.append(fileFormat);
        
        SDL_Surface* bufferSurface;
        loadMedia(stringBuffer, &bufferSurface);
        
        Tile* tile = new Tile(i, bufferSurface, tileWidth, tileHeight);
        //Sets the transparent color for the tile
        SDL_SetColorKey(tile->tile, SDL_TRUE, SDL_MapRGB(tile->tile->format, 255, 0, 255));
        
        tiles.push_back(tile);
    }
}

bool TileSet::loadMedia(std::string filename, SDL_Surface ** destination)
{
    //Loading success flag
    bool success = true;
    
    //Load splash image
    *destination = IMG_Load(filename.c_str());
    if (*destination == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
        success = false;
    }
    
    return success;
}
