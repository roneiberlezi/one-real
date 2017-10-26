//
//  TileSelection.h
//  Map Editor
//
//  Created by Ronei Berlezi on 27/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __Map_Editor__TileSelection__
#define __Map_Editor__TileSelection__

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "Tile.h"

//TODO, Somente um tile será armazenado durante a seleção, o quadrado informa quantos a direita e abaixo foram selecionados junto com o primeiro
class TileSelection{
public:
    bool selected = false;
    bool isSingle = true;
    bool isSelecting = false;
    bool valid = false;
    int page = 0;
    int tileWidth;
    int tileHeight;
    SDL_Point maxPosition;
    Tile* selectedTile = NULL;

    SDL_Rect rect;
    SDL_Point startPosition;
    SDL_Point endPosition;
    
    TileSelection(int tileWidth, int tileHeight, int maxXposition, int maxYposition);
    bool updateSelection(int x, int y, int page);
    void startSelection(int x, int y, int page);
    void endSelection(int x, int y, int page);
    void cancelSelection();
    void selectSingle(SDL_Rect tile, int page);
private:
    bool isPositionValid(int x, int y);
};

#endif /* defined(__Map_Editor__TileSelection__) */
