#include "Item.h"


Item::Item(int id, int x, int y, int w, int h, SDL_Surface* agentTexture, float colisionFactor, int type, int info) : Agent(x, y, w, h, agentTexture, colisionFactor)
{
	this->id = id;
	this->type = type;
	this->info = info;
	this->width = agentTexture->w;
	this->height = agentTexture->h;
}


Item::~Item()
{

}
