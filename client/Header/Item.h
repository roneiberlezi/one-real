#pragma once
#include "Agent.h"

class Item : public Agent{
public:
	int id;
	int type;
	int info;
	Item(int id, int x, int y, int w, int h, SDL_Surface* agentTexture, float colisionFactor, int type, int info);
	~Item();
};
