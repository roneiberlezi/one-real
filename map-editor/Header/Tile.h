#ifndef _TILE_H_
#define _TILE_H_

#include <SDL2/SDL.h>

class Tile
{
public:
	//Initializes the variables
	Tile(int id, SDL_Surface* tile, int x, int y, int tileWidth, int tileHeight, int page);

	//The attributes of the tile
	SDL_Rect square;
	SDL_Surface* tile;

	//Tile id
	int id;

	//The tile type
	int page;
};

#endif