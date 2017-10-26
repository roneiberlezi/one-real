#include "Global.h"
#include "Utils.h"

bool quit = false;
bool help = false;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

const int TOTAL_HORIZONTAL_TILES = 20;
const int VERTICAL_TILES = 11;
const int SELECTOR_HORIZONTAL_TILES = 10;

const int SCREEN_WIDTH = TILE_WIDTH * TOTAL_HORIZONTAL_TILES;
const int SCREEN_HEIGHT = TILE_HEIGHT * VERTICAL_TILES;

//Menu constants
const int TILE_SELECTOR_WIDTH = SELECTOR_HORIZONTAL_TILES * TILE_WIDTH;
const int TILE_SELECTOR_LINE_WIDTH = 0;
const int MAX_MENU_HORIZONTAL_TILES = (TILE_SELECTOR_WIDTH - TILE_SELECTOR_LINE_WIDTH) / TILE_WIDTH;
//const int MAX_MENU_HORIZONTAL_TILES = 8;
const int MAX_MENU_VERTICAL_TILES = SCREEN_HEIGHT / TILE_HEIGHT;

const int MAP_WIDTH = SCREEN_WIDTH - TILE_SELECTOR_WIDTH;
const int MAP_HEIGHT = SCREEN_HEIGHT;

const int EMPTY_RECT_LINE_THICKNESS = 1;

//Tiles amount
const int TILE_AMOUNT = 110;

//Tile set properties
int TileSetNumber = 1; //SPACE = 1; FORESTE = 2;....
std::string tileSetName = "space"; //used to identify the tile folder
std::string tileSetPath = "space/";
std::string fileFormat = ".bmp";
std::string fileName = "space";

//Vector to store all tiles from tile set
TileSet* mTileSet = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//general variables for drawing text;
SDL_Surface* text = NULL;
TTF_Font* font = NULL;
std::string fontPath = "arial.ttf";

//Console state and variables
const SDL_Color CONSOLE_TEXT_COLOR = { 255, 255, 255 };
const Uint32 CONSOLE_BACKGROUD_COLOR = color32(48, 56, 138, 0);
const int CONSOLE_TEXT_SIZE = 12;
const int CONSOLE_X = 0;
const int CONSOLE_Y = 0;
const std::string GAME_VERSION = "Unreal Map Creator 1.0";

Console* mConsole = NULL;

//Map variables
Map* mMap = NULL;
Moviment mMoviment;
MiniMap* mMiniMap = NULL;