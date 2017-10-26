//
//  Player.h
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Player_h
#define Game_Project_Player_h

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>

#endif

#include "Agent.h"
#include "Weapon.h"
#include "Utils.h"
#include <math.h>
#include <sstream>

class Player : public Agent{
public:
    int id;
    int maxHP;
    int currentHP;
    int initialTime;
	bool alive;
	char* nickName;
	int kills;
	int deaths;
    TTF_Font *font;
	SDL_Surface* deadSprite;
    bool drawingKill=false;
    int deathTime;
    int lastShot = 0;//last shot time


    //Durante o caminhar do personagem, ele pergunta para o mapa quais objetos estão no setor, em seguida, checa a colisão com o vetor retornado e permite ou não o movimento selecionado.

    Weapon* mWeapon; //arma atual

	Player(int x, int y, int w, int h, SDL_Surface* agentTexture, float colisionFactor, const char* nick, TTF_Font *font, WeaponType weapon, SDL_Surface* dead);
    
    void handleMouseEvent(SDL_Event* e);

	void Heal(int amount);
    
    void renderBullet(SDL_Surface* screenSurface);
    
    void render(SDL_Surface* screenSurface);
    void renderLifeBar(SDL_Surface* screenSurface, int x, int y);
    
    void renderOnMap(SDL_Surface *screenSurface, SDL_Point cameraPosition, std::vector<std::string>* killMessage);
    void renderNickName(SDL_Surface *screenSurface, int x, int y);
    void renderHUD(SDL_Surface *screenSurface,int x, int y);
    
    void renderKillMessage(SDL_Surface *screenSurface, std::vector<std::string>* killMessage);
    
private:
    //variable used to draw the life bar
    SDL_Rect bar;
    //SDL_Surface *nickNameSurface;
    SDL_Surface *hudLife;
	//HUD LIFE
	SDL_Surface *lifebarBG = NULL;
	SDL_Surface *profileImg = NULL;
	//HUD Dead
	TTF_Font* halloweenFont = NULL;
	TTF_Font* killFont = NULL;
	TTF_Font* textFont = NULL;
	SDL_Surface* deathSurface = NULL;
	SDL_Surface* ammoBG = NULL;
	SDL_Surface* textSurface = NULL;

};

#endif
