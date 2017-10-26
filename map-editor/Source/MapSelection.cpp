//
//  MapSelection.cpp
//  Map Editor
//
//  Created by Ronei Berlezi on 27/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "MapSelection.h"

MapSelection::MapSelection(int tileWidth, int tileHeight){
    this->tileHeight = tileHeight;
    this->tileWidth = tileWidth;
}

bool MapSelection::updateSelection(int x, int y, int offsetX, int offsetY){
//    if ((x >= startPosition.x && y >= startPosition.y) && (offsetX >= startOffset.x && offsetY >= startOffset.y)) {
    if ((x + offsetX >= startPosition.x + startOffset.x) && (y + offsetY >= startPosition.y + startOffset.y)) {
        rect.x = (startPosition.x - (offsetX - startOffset.x)) * tileWidth;
        rect.y = (startPosition.y - (offsetY - startOffset.y)) * tileHeight;
        rect.w = tileWidth + (tileWidth * ((x - startPosition.x) + (offsetX - startOffset.x)));
        rect.h = tileHeight + (tileHeight * ((y - startPosition.y) +(offsetY - startOffset.y)));
        valid = true;
        return true;
    }else{
        valid = false;
        return false;
    }

}

void MapSelection::startSelection(int x, int y, int offsetX, int offsetY){
    startPosition.x = x;
    startPosition.y = y;
    startOffset.x = offsetX;
    startOffset.y = offsetY;
    rect.x = x * tileWidth;
    rect.y = y * tileHeight;
    rect.w = tileWidth;
    rect.h = tileHeight;
    isSelecting = true;
}

void MapSelection::endSelection(int x, int y, int offsetX, int offsetY){
    endPosition.x = x + offsetX;
    endPosition.y = y + offsetY;
    isSelecting = false;
}

void MapSelection::cancelSelection(){
    isSelecting = false;
    valid = false;
}