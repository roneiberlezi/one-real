//
//  pauseMenu.h
//  game-project
//
//  Created by Breno Antunes on 20/11/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#ifndef __game_project__PauseMenu__
#define __game_project__PauseMenu__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#include <string>
#include <iostream>
#include "utils.h"

class pauseMenu{
public:
    pauseMenu();
    void showPauseMenu(SDL_Surface* screen,  TTF_Font* font);
    void enablePause();
	bool enabled;
	SDL_Rect textOp[2];
	SDL_Surface* textSurOP[2];
	bool selected[2];
	SDL_Color color[2];
	std::string label[2];
private:
	SDL_Rect menuPos;
	SDL_Rect textPos;
	TTF_Font* fontPause = NULL;
	SDL_Surface* menuSurface = NULL;
	SDL_Surface* textSurface = NULL;

};
#endif