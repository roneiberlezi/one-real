#include "Item.h"


Item::Item(int id, int x, int y, int w, int h, float colisionFactor, int type, int info) : Agent(x, y, w, h, colisionFactor)
{
	this->id = id;
    this->type = type;
    this->iInfo = info;
}


Item::~Item()
{

}
