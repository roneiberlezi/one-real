//
//  TileSet.h
//  Map Editor
//
//  Created by Ronei Berlezi on 28/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __Map_Editor__TileSet__
#define __Map_Editor__TileSet__

#include <stdio.h>
#include <string>
#include <vector>
#include "Tile.h"
#include "TileSelection.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TileSet{
public:
    std::string tileSetPath;
    std::string fileFormat;
    std::string fileName;
    
    TileSelection* mTileSelection = NULL;
    
    //Vector to store all tiles from tile set
    std::vector<Tile*> tiles;

    int currentPage;
    int tileWidth;
    int tileHeight;
    int screenWidth;
    int screenHeight;
    int tile_selector_width;
    int tile_selector_line_width;
    int max_menu_horizontal_tiles;
    int max_menu_vertical_tiles;
    int tile_amount;
    
    SDL_Surface* screenSurface;
    
    Tile* findTile(int x, int y, int page);
    void DisplayTileSet();
    
    TileSet(SDL_Surface* screenSurface, std::string tileSetPath, std::string fileFormat, std::string fileName, int tileWidht, int tileHeight, int screenWidht, int screenHeight, int tile_selector_width, int tile_selector_line_width, int max_menu_horizontal_tiles, int max_menu_vertical_tiles, int tile_amount);
private:
    void loadTileSet();
    bool loadMedia(std::string fileName, SDL_Surface ** destination);
};

#endif /* defined(__Map_Editor__TileSet__) */
