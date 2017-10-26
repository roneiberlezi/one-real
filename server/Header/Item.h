#pragma once
#include "Agent.h"

class Item : public Agent{
public:
	int id, type, iInfo;
	Item(int id, int x, int y, int w, int h, float colisionFactor, int type, int info);
	~Item();
};
