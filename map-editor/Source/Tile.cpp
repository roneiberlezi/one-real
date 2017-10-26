#include "Tile.h"

Tile::Tile(int id, SDL_Surface* tile, int x, int y, int tileWidth, int tileHeight, int page){
	//set the offsets
	this->id = id;
	this->tile = tile;
	square.x = x;
	square.y = y;

	//Set the collision box
	square.w = tileWidth;
	square.h = tileHeight;

	//Get the tile type
	this->page = page;
}