//
//  Ranking.h
//  game-project
//
//  Created by Breno Antunes on 18/11/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#ifndef __game_project__Ranking__
#define __game_project__Ranking__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL_ttf.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL_ttf.h>

#endif

#include <stdio.h>
#include "Player.h"
#include <iostream>
#include <map>
#include <string>

class Ranking{
	public:
		SDL_Rect rankingPosition;
		Ranking();
		void rankingDraw(Player* p, std::map<int, Player*>* enemies, SDL_Surface *screenSurface, TTF_Font *font);
	private:
		SDL_Surface* rankingBox = NULL;
		SDL_Surface* rankingScore = NULL;
		SDL_Surface* rankingScreen = NULL;
};
#endif /* defined(__game_project__Ranking__) */
