//
//  MiniMap.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

//
//  MiniMap.cpp
//  Map Editor
//
//  Created by Ronei Berlezi on 29/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "MiniMap.h"

MiniMap::MiniMap(int tileWidth, int tileHeight, int screenWidth, int screenHeight){
    mapSizeX = 0;
    mapSizeY = 0;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
    this->horizontalTiles = (screenWidth)/tileWidth;
    this->verticalTiles = screenHeight/tileHeight;
    
    miniMap.w = 192;
    miniMap.h = 128;
    miniMap.x = screenWidth - miniMap.w - 3;
    miniMap.y = 3;
}

void MiniMap::draw(SDL_Surface *screen, int x_offset, int y_offset){
    if (mapSizeX == 0 || mapSizeY == 0)
        return;
    
    this->mapOffset.x = x_offset;
    this->mapOffset.y = y_offset;
    
    drawUnfilledRect(screen, &miniMap, 1, color32(0, 0, 255, 0));
    
    
    position.w = (horizontalTiles * miniMap.w/mapSizeX);
    position.h = (verticalTiles * miniMap.h/mapSizeY);
    if (x_offset == 0) {
        position.x = miniMap.x;
    }else if (x_offset > mapSizeX - horizontalTiles){
        position.x = ((mapSizeX - horizontalTiles) * miniMap.w/mapSizeX) + miniMap.x;
    }else{
        position.x = (x_offset * miniMap.w/mapSizeX) + miniMap.x;
    }
    
    if (y_offset == 0) {
        position.y = miniMap.y;
    }else if (y_offset > mapSizeY - verticalTiles){
        position.y = ((mapSizeY - verticalTiles) * miniMap.h/mapSizeY) + miniMap.y;
    }else{
        position.y = (y_offset * miniMap.h/mapSizeY) + miniMap.y;
    }
    
    
    //    SDL_FillRect(screen, &position, color32(255, 0, 0, 0));
    drawUnfilledRect(screen, &position, 1, color32(255, 0, 0, 0));
    
}

void MiniMap::setMapSize(int x, int y){
    mapSizeX = x;
    mapSizeY = y;
}