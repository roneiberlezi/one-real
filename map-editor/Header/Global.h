#ifndef _MY_GLOBALS_H_
#define _MY_GLOBALS_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "Console.h"
#include "Layer.h"
#include "Map.h"
#include "Tile.h"
#include "Moviment.h"
#include "TileSet.h"
#include "MiniMap.h"

extern bool quit;
extern bool help;

extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;

extern const int TOTAL_HORIZONTAL_TILES;
extern const int VERTICAL_TILES;
extern const int SELECTOR_HORIZONTAL_TILES;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Menu constants
extern const int TILE_SELECTOR_WIDTH;
extern const int TILE_SELECTOR_LINE_WIDTH;
//const int MAX_MENU_HORIZONTAL_TILES = (TILE_SELECTOR_WIDTH - TILE_SELECTOR_LINE_WIDTH) / TILE_WIDTH;
extern const int MAX_MENU_HORIZONTAL_TILES;
extern const int MAX_MENU_VERTICAL_TILES;

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

extern const int EMPTY_RECT_LINE_THICKNESS;

//Tiles amount
extern const int TILE_AMOUNT;

//Tile set properties
extern int TileSetNumber;
extern std::string tileSetName; //used to identify the tile folder
extern std::string tileSetPath;
extern std::string fileFormat;
extern std::string fileName;

//Vector to store all tiles from tile set
extern TileSet* mTileSet;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//general variables for drawing text;
extern SDL_Surface* text;
extern TTF_Font* font;
extern std::string fontPath;

//Console variables
extern const SDL_Color CONSOLE_TEXT_COLOR;
extern const Uint32 CONSOLE_BACKGROUD_COLOR;
extern const int CONSOLE_TEXT_SIZE;
extern const int CONSOLE_X;
extern const int CONSOLE_Y;
extern const std::string GAME_VERSION;

extern Console* mConsole;

//Map variables
extern Map* mMap;
extern Moviment mMoviment;
extern MiniMap* mMiniMap;
#endif