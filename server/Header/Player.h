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
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_net.h>

#endif



class Player{
public:
    int id;
    TCPsocket socket;
    int socketTimeout;
    int maxHP = 100;
    int currentHP = 100;
    int bulletType = 0;
	bool alive = true;
    int deathTime;
	char nickname[50];
	int kills;
	int deaths;
	int killStreak;

    
    SDL_Point position;
    SDL_Rect collisionRect;

    int width = 96;
    int height = 96;
    float collisionFactor = 0.33;
    
    //Durante o caminhar do personagem, ele pergunta para o mapa quais objetos estão no setor, em seguida, checa a colisão com o vetor retornado e permite ou não o movimento selecionado.

    Player(int id);
    Player(int id, TCPsocket socket);
    bool setPosition(int x, int y);
    void init(int id);
    void initRoundValues();
    void death(int ticks);
};

#endif
