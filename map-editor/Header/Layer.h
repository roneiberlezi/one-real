#ifndef _LAYER_H_
#define _LAYER_H_
#pragma once


#include <string>

class Layer
{
public:
	//should store the tile number
	std::string tileSet;
	int** layer;
	Layer(int sizeX, int sizeY, const char* tileSetName);
	~Layer();
private:
	int sizeX;
	int sizeY;
};

#endif