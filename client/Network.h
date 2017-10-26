//
//  Network.h
//  game-project
//
//  Created by Diogo Falcao on 06/10/14.
//  Copyright (c) 2014 dfdf. All rights reserved.
//

#ifndef __Game_Project__Network__
#define __Game_Project__Network__

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL_net.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL_net.h>

#endif

#include <map>
#include <cstdio>
#include <iostream>
#include "Player.h"
#include "Item.h"

class network{

	//Jogo continuar sem ficar parando
	SDLNet_SocketSet server;

	TCPsocket connection;
public:
	bool connected = false;
	bool ready = false;
	char tmp[1400];

	network(const char* ip, char* nickname);
	~network();
	void send(Player* p);
	void requestName(int id);
	void requestScore();
	void sendShot(Player* p);
	void recv(Player* p, std::map<int, Player*>* enemies, std::map<int, Item*>* itens);
};

#endif