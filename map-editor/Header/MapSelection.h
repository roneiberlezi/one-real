//
//  MapSelection.h
//  Map Editor
//
//  Created by Ronei Berlezi on 27/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __Map_Editor__MapSelection__
#define __Map_Editor__MapSelection__

#include <stdio.h>
#include <SDL2/SDL.h>

class MapSelection{
public:
    int tileWidth;
    int tileHeight;
    SDL_Rect rect;
    SDL_Point startPosition;
    SDL_Point endPosition;
    SDL_Point startOffset;
    SDL_Point endOffset;
    bool valid = false;
    bool isSelecting = false;
    bool updateSelection(int x, int y, int offsetX, int offsetY);
    void startSelection(int x, int y, int offsetX, int offsetY);
    void endSelection(int x, int y, int offsetX, int offsetY);
    void cancelSelection();
    MapSelection(int tileWidth, int tileHeight);
};

#endif /* defined(__Map_Editor__MapSelection__) */
