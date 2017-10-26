//
//  pauseMenu.cpp
//  game-project
//
//  Created by Breno Antunes on 20/11/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#include "pauseMenu.h"

pauseMenu::pauseMenu(){
	color[0] = { 255, 255, 255, 0 };
	color[1] = { 0, 0, 255, 0 };
	enabled = false;
}

void pauseMenu::showPauseMenu(SDL_Surface* screen, TTF_Font* font){
	label[0] = "CONTINUE";
	label[1] = "EXIT";
	selected[0] = false;
	selected[1] = false;
    fontPause = font;


    loadMedia("resources/images/menu/menu.png", &menuSurface);
	textSurface = TTF_RenderText_Solid(fontPause, "MENU", color[1]);
	textSurOP[0] = TTF_RenderText_Solid(font, label[0].c_str(), color[0]);
	textSurOP[1] = TTF_RenderText_Solid(font, label[1].c_str(), color[0]);

	menuPos.x=(screen->w/2) - (menuSurface->w/2);
    menuPos.y=(screen->h/2) - (menuSurface->w/2);

	textPos.x = menuPos.x + 170 - textSurface->clip_rect.w/2;
	textPos.y = menuPos.y + 40;

	textOp[0].x = menuPos.x + 170 - textSurOP[0]->clip_rect.w / 2;
	textOp[0].y = menuPos.y + 143 - textSurOP[0]->clip_rect.h;

	textOp[1].x = menuPos.x + 170 - textSurOP[1]->clip_rect.w / 2;
	textOp[1].y = menuPos.y + 145 + textSurOP[1]->clip_rect.h;


	SDL_BlitSurface(menuSurface, NULL, screen, &menuPos);
	SDL_BlitSurface(textSurface, NULL, screen, &textPos);
	SDL_BlitSurface(textSurOP[0], NULL, screen, &textOp[0]);
	SDL_BlitSurface(textSurOP[1], NULL, screen, &textOp[1]);
}

void pauseMenu::enablePause(){
    if (this->enabled)
        this->enabled = false;
    else
        this->enabled = true;
}
