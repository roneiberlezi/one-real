//
//  TileSet.cpp
//  Map Editor
//
//  Created by Ronei Berlezi on 28/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "TileSet.h"

TileSet::TileSet(SDL_Surface* screenSurface, std::string tileSetPath, std::string fileFormat, std::string fileName, int tileWidth, int tileHeight, int screenWidth, int screenHeight, int tile_selector_width, int tile_selector_line_width, int max_menu_horizontal_tiles, int max_menu_vertical_tiles, int tile_amount){
    
    this->screenSurface = screenSurface;
    this->tileSetPath = tileSetPath;
    this->fileFormat = fileFormat;
    this->fileName = fileName;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->tile_selector_width = tile_selector_width;
    this->tile_selector_line_width = tile_selector_line_width;
    this->max_menu_horizontal_tiles = max_menu_horizontal_tiles;
    this->max_menu_vertical_tiles = max_menu_vertical_tiles;
    this->tile_amount = tile_amount;
    
    mTileSelection = new TileSelection(tileWidth, tileHeight, (max_menu_horizontal_tiles * tileWidth) + (screenWidth - tile_selector_width + tile_selector_line_width) - 1, (tileHeight * max_menu_vertical_tiles) - 1);
    
    currentPage = 1;
    
    loadTileSet();
}


void TileSet::loadTileSet(){
    SDL_Rect dstRect;
    dstRect.h = tileHeight;
    dstRect.w = tileWidth;
    dstRect.x = screenWidth - tile_selector_width + tile_selector_line_width;
    dstRect.y = 0;
    
    int page = 1;
    int v = 0;
    int h = 0;
    
    std::string stringBuffer;
    //std::string tilePosition;
    for (int i = 0; i < tile_amount; i++){
        stringBuffer = tileSetPath;
        stringBuffer.append("/");
        stringBuffer.append(fileName);
        stringBuffer.append(std::to_string(i));
        stringBuffer.append(fileFormat);
        
        SDL_Surface* bufferSurface;
        loadMedia(stringBuffer, &bufferSurface);
        
        Tile* tile = new Tile(i, bufferSurface, dstRect.x, dstRect.y, tileWidth, tileHeight, page);
        //Sets the transparent color for the tile
        SDL_SetColorKey(tile->tile, SDL_TRUE, SDL_MapRGB(screenSurface->format, 255, 0, 255));
        h += 1;
        dstRect.x += tileWidth;
        if (h >= max_menu_horizontal_tiles){
            dstRect.x = screenWidth - tile_selector_width + tile_selector_line_width;
            h = 0;
            v += 1;
            dstRect.y += tileHeight;
            if (v >= max_menu_vertical_tiles){
                page += 1;
                v = 0;
                dstRect.y = 0;
            }
        }
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

Tile* TileSet::findTile(int x, int y, int page){
    for (std::vector<Tile*>::const_iterator it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->page == page && ((*it)->square.x == x && (*it)->square.y == y))
            return (*it);
    }
    return NULL;
}


void TileSet::DisplayTileSet(){
    //Draw all tiles from the current page
    for (std::vector<Tile*>::const_iterator it = tiles.begin(); it != tiles.end(); ++it) {
        if ((*it)->page == currentPage)
            SDL_BlitSurface((*it)->tile, NULL, screenSurface, &(*it)->square);
    }
}
