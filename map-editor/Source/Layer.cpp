#include "Layer.h"

Layer::Layer(int sizeX, int sizeY, const char* tileSetName)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->tileSet = tileSetName;
	
	//layer = (int **)calloc(sizeX, sizeof(int *));
	//for (unsigned int i = 0; i < sizeX; i++)
	//	layer[i] = (int *)calloc(sizeY, sizeof(int));
	
	layer = new int*[sizeX];
	for (int i = 0; i < sizeX; ++i)
		layer[i] = new int[sizeY];
	
	for (int x = 0; x < sizeX; x++){
		for (int y = 0; y < sizeY; y++)
			layer[x][y] = 0;
	}
}


Layer::~Layer()
{
	for (int i = 0; i < sizeX; ++i) {
		delete [] layer[i];
	}
	delete [] layer;
}
