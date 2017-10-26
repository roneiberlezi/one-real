//
//  Ranking.cpp
//  game-project
//
//  Created by Breno Antunes on 18/11/14.
//  Copyright (c) 2014 beantunes. All rights reserved.
//

#include "Ranking.h"


Ranking::Ranking(){
    
    this->rankingPosition.x=20;
    this->rankingPosition.y=20;
}

void Ranking::rankingDraw(Player* p, std::map<int, Player*>* enemies, SDL_Surface *screenSurface, TTF_Font *font){

	if (rankingBox==NULL)
		loadMedia("rankingBG.png", &rankingBox);

	SDL_Rect posRank;

	posRank.x = screenSurface->clip_rect.w / 2 - rankingBox->clip_rect.w / 2;
	posRank.y = screenSurface->clip_rect.h / 2 - rankingBox->clip_rect.h / 2;
	
	this->rankingPosition.x = posRank.x + 50;
	this->rankingPosition.y = posRank.y + 50;

	SDL_BlitSurface(rankingBox, NULL, screenSurface, &posRank);

	SDL_Rect scorePosition;

	scorePosition.x = rankingPosition.x + 300;
	scorePosition.y = rankingPosition.y;
	


	SDL_Color color = { 255, 255, 255, 0 };
	SDL_Color colorTitle = { 0, 0, 120, 0 };
    std::string rankingString, scoreString;

    std::string auxCharNick;
    auxCharNick = p->nickName;

	rankingString = "NAME";
	scoreString = "K / D";

	this->rankingScreen = TTF_RenderText_Solid(font, rankingString.c_str(), colorTitle);
	rankingScore = TTF_RenderText_Solid(font, scoreString.c_str(), colorTitle);

	SDL_Rect line;
	line.x = rankingPosition.x;
	line.y = rankingPosition.y + rankingScreen->clip_rect.h+2;
	line.h = 2;
	line.w = 270 + rankingScreen->w + rankingScore->w;

	SDL_FillRect(screenSurface, &line, color32(255, 255, 255, 0));

	SDL_BlitSurface(this->rankingScreen, NULL, screenSurface, &this->rankingPosition);
	SDL_FreeSurface(rankingScreen);
	SDL_BlitSurface(rankingScore, NULL, screenSurface, &scorePosition);
	SDL_FreeSurface(rankingScore);

	this->rankingPosition.y += 30;
	scorePosition.y += 30;

	rankingString = auxCharNick;
	scoreString = " " + std::to_string(p->kills) + " / " + std::to_string(p->deaths);

	this->rankingScreen = TTF_RenderText_Solid(font, rankingString.c_str(), color);
	rankingScore = TTF_RenderText_Solid(font, scoreString.c_str(), color);
	
	SDL_BlitSurface(this->rankingScreen, NULL, screenSurface, &this->rankingPosition);
	SDL_FreeSurface(rankingScreen);
	SDL_BlitSurface(rankingScore, NULL, screenSurface, &scorePosition);
	SDL_FreeSurface(rankingScore);

    //info dos inimigos
    std::map<int, Player*>::iterator tempEnemie;
    for(std::map<int, Player*>::iterator iterator = enemies->begin();iterator != enemies->end(); iterator++ ){
        if (!iterator->second->isNPC) {
            auxCharNick= iterator->second->nickName;
            
            //rankingString = rankingString + auxCharNick + "     " + auxIntKill.str() + "/" +auxIntDeath.str() +"\n";
            
            rankingString = auxCharNick + "     ";
            scoreString = " " + std::to_string(iterator->second->kills) + " / " + std::to_string(iterator->second->deaths);
            
            this->rankingScreen = TTF_RenderText_Solid(font, rankingString.c_str(), color);
            rankingScore = TTF_RenderText_Solid(font, scoreString.c_str(), color);
            this->rankingPosition.y += 30;
            scorePosition.y += 30;
            
            SDL_BlitSurface(this->rankingScreen, NULL, screenSurface, &this->rankingPosition);
            SDL_FreeSurface(rankingScreen);
            SDL_BlitSurface(rankingScore, NULL, screenSurface, &scorePosition);
            SDL_FreeSurface(rankingScore);
        }
    }
    
}