//
//  Utils.cpp
//  Game Project
//
//  Created by Ronei Berlezi on 06/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>

#endif

#include <sstream>

#include "Utils.h"

Uint32 color32(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 alpha)
{
    return (Uint32(alpha) << 24) + (Uint32(r) << 16) + (Uint32(g) << 8) + Uint32(b);
}

void drawUnfilledRect(SDL_Surface* dst, SDL_Rect* rect, int line_thickness, Uint32 color){
    SDL_Rect line;
    //top line
    line.x = rect->x;
    line.y = rect->y;
    line.w = rect->w;
    line.h = line_thickness;
    SDL_FillRect(dst, &line, color);
    
    //left line
    line.x = rect->x;
    line.y = rect->y;
    line.w = line_thickness;
    line.h = rect->h;
    SDL_FillRect(dst, &line, color);
    
    //bottom line
    line.x = rect->x;
    line.y = rect->y + rect->h;
    line.w = rect->w;
    line.h = line_thickness;
    SDL_FillRect(dst, &line, color);
    
    //right line
    line.x = rect->x + rect->w - line_thickness;
    line.y = rect->y;
    line.w = line_thickness;
    line.h = rect->h;
    SDL_FillRect(dst, &line, color);
}


bool loadMedia(std::string filename, SDL_Surface ** destination)
{
    //Loading success flag
    bool success = true;
    return success;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty())
            elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}