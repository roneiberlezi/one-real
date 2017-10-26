//
//  TileSelection.cpp
//  Map Editor
//
//  Created by Ronei Berlezi on 27/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "TileSelection.h"

TileSelection::TileSelection(int tileWidth, int tileHeight, int maxXposition, int maxYposition){
    maxPosition.x = maxXposition;
    maxPosition.y = maxYposition;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

void TileSelection::startSelection(int x, int y, int page){
    if (!isPositionValid(x, y)) {
        return;
    }
    
    selected = false;
    valid = false;
    isSelecting = true;
    this->page = page;
    startPosition.x = x;
    startPosition.y = y;
    rect.x = x;
    rect.y = y;
    rect.h = tileHeight;
    rect.w = tileWidth;
}

void TileSelection::selectSingle(SDL_Rect tile, int page){
    this->page = page;
    selected = true;
    rect = tile;
    startPosition.x = tile.x;
    startPosition.y = tile.y;
    endPosition.x = tile.x;
    endPosition.y = tile.y;
}

bool TileSelection::updateSelection(int x, int y, int page){
    if ((x >= startPosition.x && y >= startPosition.y) && (page == this->page && isPositionValid(x, y))) {
        rect.w = tileWidth + (x - startPosition.x);
        rect.h = tileHeight + (y - startPosition.y);
        valid = true;
        return true;
    }else{
        if (this->page != page) {
            cancelSelection();
        }
        valid = false;
        return false;
    }
    
    return true;
}

void TileSelection::endSelection(int x, int y, int page){
    isSelecting = false;
    if ((x >= startPosition.x && y >= startPosition.y) && (page == this->page && isPositionValid(x, y))) {
        rect.w = tileWidth + (x - startPosition.x);
        rect.h = tileHeight + (y - startPosition.y);
        endPosition.x = x;
        endPosition.y = y;
        selected = true;
        valid = true;
    }else{
        cancelSelection();
    }
}

void TileSelection::cancelSelection(){
    valid = false;
    isSelecting = false;
}

bool TileSelection::isPositionValid(int x, int y){
    if (x > maxPosition.x || y > maxPosition.y)
        return false;
    else
        return true;
}