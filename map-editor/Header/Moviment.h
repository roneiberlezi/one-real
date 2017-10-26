//
//  Moviment.h
//  Map Editor
//
//  Created by Ronei Berlezi on 26/09/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Map_Editor_Moviment_h
#define Map_Editor_Moviment_h

#include <SDL2/SDL.h>

struct Moviment{
//    const int RIGHT = 1;
//    const int LEFT = 2;
//    const int UP = 3;
//    const int DOWN = 4;
//    const int STOPED = 0;
    int speed = 1;
//    int direction = 0;
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;
    SDL_Point position;
};

#endif
