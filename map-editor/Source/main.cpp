#include "Global.h"
#include "Command.h"
#include "Utils.h"
#include "Layer.h"

#include <stdio.h>
#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>

bool init()
{
    mMoviment.position.x = 0;
    mMoviment.position.y = 0;
    
    mMiniMap = new MiniMap(TILE_WIDTH, TILE_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, TILE_SELECTOR_WIDTH);
    
	std::map< std::string, Command* > commandMap;
	commandMap["save"] = new CommandSave();
	commandMap["new"] = new CommandNew();
	commandMap["page"] = new CommandSetPage();
	commandMap["quit"] = new CommandQuit();
	commandMap["speed"] = new CommandSpeed();
    commandMap["pos"] = new CommandPosition();
    commandMap["layer"] = new CommandLayer();
    commandMap["fill"] = new CommandFill();
    commandMap["load"] = new CommandLoad();
    commandMap["resize"] = new CommandResize();
    commandMap["help"] = new CommandHelp();
    
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Unreal Map Creator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		printf("TTF_Init() Failed: %s", TTF_GetError());
		success = false;
	}
	else{
		font = TTF_OpenFont(fontPath.c_str(), 12);
		if (font == NULL){
			printf("TTF_OpenFont() Failed: %s", TTF_GetError());
			success = false;
		}
	}

	//initialize console with all settings
	mConsole = new Console(gScreenSurface
						  , CONSOLE_X
						  , CONSOLE_Y
						  , SCREEN_WIDTH
						  , font
						  , CONSOLE_TEXT_SIZE
						  , CONSOLE_TEXT_COLOR
						  , CONSOLE_BACKGROUD_COLOR
						  , commandMap
						  , GAME_VERSION);
    

    //Create a new TileSet and load it into the internal vector
    mTileSet = new TileSet(gScreenSurface
                           , tileSetPath
                           , fileFormat
                           , fileName
                           , TILE_WIDTH
                           , TILE_HEIGHT
                           , SCREEN_WIDTH
                           , SCREEN_HEIGHT
                           , TILE_SELECTOR_WIDTH
                           , TileSetNumber
                           , MAX_MENU_HORIZONTAL_TILES
                           , MAX_MENU_VERTICAL_TILES
                           , TILE_AMOUNT);
    
    
    
    //initializes a default map
    mMap = new Map(0, 0, TILE_WIDTH, TILE_HEIGHT, 3, tileSetName.c_str(), TileSetNumber);

	return success;
}

void draw_mouse_rect(SDL_Rect* mouse_rect){
	SDL_GetMouseState(&mouse_rect->x, &mouse_rect->y);
    int x = mouse_rect->x;
    int y = mouse_rect->y;
    if (mouse_rect->x > SCREEN_WIDTH - TILE_SELECTOR_WIDTH){
		mouse_rect->x = int((mouse_rect->x / TILE_WIDTH)*TILE_WIDTH) + TILE_SELECTOR_LINE_WIDTH;
	}
	else{
		mouse_rect->x = int((mouse_rect->x / TILE_WIDTH)*TILE_WIDTH);
	}
	mouse_rect->y = int((mouse_rect->y / TILE_HEIGHT)*TILE_HEIGHT);
    
    //if there is an selection occuring in the menu, update its selection
    if (mTileSet->mTileSelection->isSelecting && mouse_rect->x > SCREEN_WIDTH - TILE_SELECTOR_WIDTH){
        x = int((x / TILE_WIDTH)*TILE_WIDTH) + TILE_SELECTOR_LINE_WIDTH;
        y = int((y / TILE_HEIGHT)*TILE_HEIGHT);
        mTileSet->mTileSelection->updateSelection(x, y, mTileSet->currentPage);
        if (mTileSet->mTileSelection->valid) drawUnfilledRect(gScreenSurface, &mTileSet->mTileSelection->rect, EMPTY_RECT_LINE_THICKNESS, color32(255, 0, 0, 100));
        else drawUnfilledRect(gScreenSurface, &mTileSet->mTileSelection->rect, EMPTY_RECT_LINE_THICKNESS, color32(0, 0, 255, 100));
    }//if there is a selection occuring in the map, update it
    else if (mMap->mMapSelection->isSelecting && x < SCREEN_WIDTH - TILE_SELECTOR_WIDTH) {
        x = int((x / TILE_WIDTH));
        y = int((y / TILE_HEIGHT));
        mMap->mMapSelection->updateSelection(x, y, mMoviment.position.x, mMoviment.position.y);
        
        if (mMap->mMapSelection->valid) drawUnfilledRect(gScreenSurface, &mMap->mMapSelection->rect, EMPTY_RECT_LINE_THICKNESS, color32(255, 0, 0, 100));
        else drawUnfilledRect(gScreenSurface, &mMap->mMapSelection->rect, EMPTY_RECT_LINE_THICKNESS, color32(0, 0, 255, 100));

            
    }else if(mTileSet->mTileSelection->selected && x < SCREEN_WIDTH - TILE_SELECTOR_WIDTH){
        SDL_Rect area = mTileSet->mTileSelection->rect;
        area.x = int((x / TILE_WIDTH)*TILE_WIDTH);
        area.y = int((y / TILE_HEIGHT)*TILE_HEIGHT);
        if (area.x + area.w > SCREEN_WIDTH - TILE_SELECTOR_WIDTH - TILE_SELECTOR_LINE_WIDTH) {
            area.w = ((SCREEN_WIDTH - TILE_SELECTOR_WIDTH)) - area.x;
        }
        drawUnfilledRect(gScreenSurface, &area, EMPTY_RECT_LINE_THICKNESS, color32(255, 0, 0, 100));
    }
    else{//if there is nothing happing, just draw the regular square
        drawUnfilledRect(gScreenSurface, mouse_rect, EMPTY_RECT_LINE_THICKNESS, color32(255, 0, 0, 100));
    }
}

bool loadMedia(std::string filename, SDL_Surface ** destination)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	*destination = IMG_Load(filename.c_str());
	if (*destination == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	mConsole->~Console();
	mConsole = NULL;
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

void drawMenu(){
	//Create a window separator
	SDL_Rect menuSeparator;
	menuSeparator.x = SCREEN_WIDTH - TILE_SELECTOR_WIDTH;
	menuSeparator.y = 0;
	menuSeparator.h = SCREEN_HEIGHT;
	//menuSeparator.w = TILE_SELECTOR_LINE_WIDTH;
    menuSeparator.w = 4;
    
    //Draw the current tileset page on the menu
	mTileSet->DisplayTileSet();

   	SDL_FillRect(gScreenSurface, &menuSeparator, color32(7, 16, 146, 0));
}

//Function used to display all values during runtime
void Debug(){
	int x, y;
	std::string string_buffer;

    string_buffer = "X: ";
    string_buffer.append(std::to_string(mMoviment.position.x));
    draw_debug_text(0, 0, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255}, color32(0, 0, 0, 0));
    
    string_buffer = "Y: ";
    string_buffer.append(std::to_string(mMoviment.position.y));
    draw_debug_text(0, 13, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255}, color32(0, 0, 0, 0));
    
	SDL_GetMouseState(&x, &y);

	string_buffer = "Mouse x: ";
	string_buffer.append(std::to_string(x));
	draw_debug_text(0, 300, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255}, color32(0, 0, 0, 0));

	string_buffer = "Mouse Y: ";
	string_buffer.append(std::to_string(y));
	draw_debug_text(0, 315, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255 }, color32(0, 0, 0, 0));
    
    string_buffer = "Map size X: ";
    string_buffer.append(std::to_string(mMap->sizeX));
    draw_debug_text(0, 330, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255 }, color32(0, 0, 0, 0));
    
    string_buffer = "Map size Y: ";
    string_buffer.append(std::to_string(mMap->sizeY));
    draw_debug_text(0, 345, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255 }, color32(0, 0, 0, 0));

    string_buffer = "Tile page: ";
    string_buffer.append(std::to_string(mTileSet->currentPage));
    draw_debug_text(0, 360, gScreenSurface, text, font, string_buffer.c_str(), { 255, 255, 255 }, color32(0, 0, 0, 0));
    
    if (help) {
        string_buffer = "CONSOLE COMMAND LIST:";
        draw_debug_text(0, 400, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "new <size_x> <size_y>: Creates a new map with the specified size";
        draw_debug_text(0, 415, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "save <filename>: Saves the file in any extension specified";
        draw_debug_text(0, 430, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "load <filename>: Load the file into the editor";
        draw_debug_text(0, 445, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "resize <filename> <size_x> <size_y>: Load the file with a new size";
        draw_debug_text(0, 460, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "layer <layer_number>: Change between layers 1, 2 and 3";
        draw_debug_text(0, 475, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "fill: Fills the map with the selected tile";
        draw_debug_text(0, 490, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "page <page_number>: Change the tile set page";
        draw_debug_text(0, 505, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "quit: Exit application";
        draw_debug_text(0, 520, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "speed <new_speed>: Change walking speed on the map";
        draw_debug_text(0, 535, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "position <x> <y>: Go to the specified offset";
        draw_debug_text(0, 550, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));
        
        string_buffer = "help: show/hide command list";
        draw_debug_text(0, 565, gScreenSurface, text, font, string_buffer.c_str(), { 255, 0, 0 }, color32(0, 0, 0, 0));

    }
}

void handleMouseEvents(SDL_Event *e){
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        if (x > SCREEN_WIDTH - TILE_SELECTOR_WIDTH + TILE_SELECTOR_LINE_WIDTH && keyStates[SDL_SCANCODE_LGUI] ) {
            if (mMap != NULL) mMap->mMapSelection->cancelSelection();
            x = int((x / TILE_WIDTH)*TILE_WIDTH) + TILE_SELECTOR_LINE_WIDTH;
            y = int((y / TILE_HEIGHT)*TILE_HEIGHT);
            mTileSet->mTileSelection->startSelection(x, y, mTileSet->currentPage);
        }else if (x < SCREEN_WIDTH - TILE_SELECTOR_WIDTH + TILE_SELECTOR_LINE_WIDTH && keyStates[SDL_SCANCODE_LGUI]){
            mTileSet->mTileSelection->cancelSelection();
            if (mTileSet->mTileSelection->selected && mMap != NULL) {
                x = int((x / TILE_WIDTH));
                y = int((y / TILE_HEIGHT));
                mMap->mMapSelection->startSelection(x, y, mMoviment.position.x, mMoviment.position.y);
            }
        }
    }
    else if (e->type == SDL_MOUSEBUTTONUP){
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        
        //If click on menu, select the clicked tile
        if (x > SCREEN_WIDTH - TILE_SELECTOR_WIDTH + TILE_SELECTOR_LINE_WIDTH) {
            if (mMap != NULL) mMap->mMapSelection->cancelSelection();
            x = int((x / TILE_WIDTH)*TILE_WIDTH) + TILE_SELECTOR_LINE_WIDTH;
            y = int((y / TILE_HEIGHT)*TILE_HEIGHT);
            
            if (mTileSet->mTileSelection->isSelecting) {
                mTileSet->mTileSelection->endSelection(x, y, mTileSet->currentPage);
            }else{
                Tile* selected = mTileSet->findTile(x, y, mTileSet->currentPage);
                if (selected != NULL) {
                    mTileSet->mTileSelection->selectSingle(selected->square, mTileSet->currentPage);
                }
            }
        }else{
            if (mTileSet->mTileSelection->selected && mMap->mMapSelection->isSelecting) {
                x = int((x / TILE_WIDTH));
                y = int((y / TILE_HEIGHT));
                mMap->mMapSelection->endSelection(x, y, mMoviment.position.x, mMoviment.position.y);
                mMap->setAreaWithTile(mTileSet->findTile(mTileSet->mTileSelection->startPosition.x, mTileSet->mTileSelection->startPosition.y, mTileSet->mTileSelection->page)->id);
            }else{
                if (mTileSet->mTileSelection->selected) {
                    x = int((x / TILE_WIDTH)) + mMoviment.position.x;
                    y = int((y / TILE_HEIGHT)) + mMoviment.position.y;
                    mMap->setTile(x, y, mTileSet);
                }
            }
        }
    }
}

void updatePosition(){
    if (mMoviment.right)
        mMoviment.position.x += mMoviment.speed;
    if (mMoviment.left)
        mMoviment.position.x -= mMoviment.speed;
    if (mMoviment.up)
        mMoviment.position.y -= mMoviment.speed;
    if (mMoviment.down)
        mMoviment.position.y += mMoviment.speed;
    
    if (mMoviment.position.x < 0)
        mMoviment.position.x = 0;
    if (mMoviment.position.y < 0)
        mMoviment.position.y = 0;
}

void handleKeys(SDL_Event *e){
	//if console is enabled, the keys goes to the console output
	//if the ` key is pressed, the console is opened
	//otherwise this funcion does nothing
    if (!mConsole->isOpen()) {
        if (e->type == SDL_KEYDOWN){
            //Handle backspace
            if (e->key.keysym.sym == SDLK_d )
                mMoviment.right = true;
            else if (e->key.keysym.sym == SDLK_a )
                mMoviment.left = true;
            else if (e->key.keysym.sym == SDLK_w )
                mMoviment.up = true;
            else if (e->key.keysym.sym == SDLK_s )
                mMoviment.down = true;
        }else if (e->type == SDL_KEYUP){
            if (e->key.keysym.sym == SDLK_d )
                mMoviment.right = false;
            else if (e->key.keysym.sym == SDLK_a )
                mMoviment.left = false;
            else if (e->key.keysym.sym == SDLK_w )
                mMoviment.up = false;
            else if (e->key.keysym.sym == SDLK_s )
                mMoviment.down = false;
        }
    }else{
        mMoviment.right = false;
        mMoviment.left = false;
        mMoviment.up = false;
        mMoviment.down = false;
    }
    mConsole->handleKeys(e);
}

void drawEmptyBg(){
	SDL_Rect emptybg;
	emptybg.w = SCREEN_WIDTH;
	emptybg.h = SCREEN_HEIGHT;
	emptybg.x = 0;
	emptybg.y = 0;

	SDL_FillRect(gScreenSurface, &emptybg, color32(0, 0, 0, 0));
}

bool drawMap(){
	if (mMap == NULL) return false;
	if (mMap->sizeX == 0 || mMap->sizeY == 0) return false;
	
	mMap->drawMap(gScreenSurface, mTileSet, MAP_WIDTH, MAP_HEIGHT, mMoviment.position.x, mMoviment.position.y);

	return true;
}

void drawSelection(){
    if (mTileSet->mTileSelection->selected && mTileSet->currentPage == mTileSet->mTileSelection->page) {
        drawUnfilledRect(gScreenSurface, &mTileSet->mTileSelection->rect, 1, color32(0, 255, 0, 0));
    }
}

int main(int argc, char* args[]){
	SDL_Event event;
	//Rect to represent the current tile over the mouse
	SDL_Rect mouse_rect;
	mouse_rect.w = TILE_WIDTH;
	mouse_rect.h = TILE_HEIGHT;
	mouse_rect.x = 0;
	mouse_rect.y = 0;

	if (!init())
	{
		printf("Failed to initialize!\n");
	}

	while (!quit)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT){
				quit = true;
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				handleKeys(&event);
            if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
                handleMouseEvents(&event);
		}

		SDL_Delay(30);

		//Draw a rect in the current mouse position
		//DisplayTileSet deve ser aplicado somente para os tiles em que o mouse estava em cima, consome muito processamento se atulizar todo o set de uma vez
        
        updatePosition();
		drawEmptyBg();
		drawMenu();
        drawSelection();
		drawMap();
		draw_mouse_rect(&mouse_rect);
        
        mMiniMap->draw(gScreenSurface, mMoviment.position.x, mMoviment.position.y);

		//update the console surface if there is anything to render
		//otherwise do nothing
		Debug();
		mConsole->update();


		SDL_UpdateWindowSurface(gWindow);
	}

	//Free resources and close SDL
	close();

	return 0;
}
