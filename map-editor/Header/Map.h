#pragma once
#include "Layer.h"
#include <vector>
#include <SDL2/SDL.h>
#include "Tile.h"
#include "MapSelection.h"
#include "TileSet.h"

class Map
{
public:
	SDL_Rect area;
	int currentLayer;
	int layerAmount;
	const char* tileSetName;
	int sizeX;
	int sizeY;
	std::vector<Layer*> layer;
    SDL_RWops* file;
    int tileSetNumber;
    bool fileNotFound = false;
    
    MapSelection* mMapSelection;
    
    //Constructor to create a new map
	Map(int sizeX
		, int sizeY
		, int tileWidth
		, int tileHeight
		, int layerAmount
		, const char* tileSetName
        , int tileSetNumber);
    
    //Constructor to load a map
    Map(const char* fileName, int tileWidth
        , int tileHeight
        , int layerAmount
        , const char* tileSetName
        , int tileSetNumber);
    
    //Constructor to resize a map
    Map(int newX, int newY, const char* fileName, int tileWidth
        , int tileHeight
        , int layerAmount
        , const char* tileSetName
        , int tileSetNumber);

	void drawMap(SDL_Surface* screen, TileSet* tileSet, int width, int height, int posx, int posy);
	void drawLayer(SDL_Surface* screen, int layer_, std::vector<Tile*> tileSet, int width, int height, int posx, int posy);
    
    void setAreaWithTile(int tileID);
    
    
    void setTile(int x, int y, TileSet* tileSet);
    void Fill(int tileID);
    void drawGroup(int x, int y, TileSelection* selection, std::vector<Tile*> tileSet);
    
    bool save(const char* fileName);
    ~Map();
private:
	int tileWidth;
	int tileHeight;
};

