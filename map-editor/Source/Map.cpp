#include "Map.h"


Map::Map(int sizeX, int sizeY, int tileWidth, int tileHeight, int layerAmount, const char* tileSetName, int tileSetNumber)
{
	this->layerAmount = layerAmount;
	this->currentLayer = 0;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->tileSetName = tileSetName;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
    this->tileSetNumber = tileSetNumber;
	area.w = sizeX*tileWidth;
	area.h = sizeY*tileHeight;
	area.x = 0;
	area.y = 0;
    
    //initializes the selection object
    mMapSelection = new MapSelection(tileWidth, tileHeight);

	for (int a = 0; a < layerAmount; a++)
		layer.push_back(new Layer(sizeX, sizeY, tileSetName));
}

Map::Map(const char* fileName, int tileWidth, int tileHeight, int layerAmount, const char* tileSetName, int tileSetNumber)
{
    file = SDL_RWFromFile(fileName, "r+b" );
    
    //File does not exist
    if( file == NULL )
    {
        printf( "Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
        fileNotFound = true;
    }
    //File exists
    else
    {
        fileNotFound = false;
        //Load data
        printf( "Reading file...!\n" );
        SDL_RWread( file, &sizeX, sizeof(int), 1);
        SDL_RWread( file, &sizeY, sizeof(int), 1);
        SDL_RWread( file, &tileSetNumber, sizeof(int), 1);
        
        this->layerAmount = 3;
        this->currentLayer = 0;
        this->tileSetName = "space";
        area.w = sizeX*tileWidth;
        area.h = sizeY*tileHeight;
        area.x = 0;
        area.y = 0;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        this->tileSetNumber = tileSetNumber;
        
        //initializes the selection object
        mMapSelection = new MapSelection(tileWidth, tileHeight);
        
        for (int a = 0; a < layerAmount; a++)
            layer.push_back(new Layer(sizeX, sizeY, tileSetName));
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &layer[0]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &layer[1]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &layer[2]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        //Close file handler
        SDL_RWclose( file );
    }
}

Map::Map(int newX, int newY, const char* fileName, int tileWidth, int tileHeight, int layerAmount, const char* tileSetName, int tileSetNumber)
{
    file = SDL_RWFromFile(fileName, "r+b" );
    
    //File does not exist
    if( file == NULL )
    {
        printf( "Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
        fileNotFound = true;
    }
    //File exists
    else
    {
        fileNotFound = false;
        //Load data
        printf( "Reading file...!\n" );
        SDL_RWread( file, &sizeX, sizeof(int), 1);
        SDL_RWread( file, &sizeY, sizeof(int), 1);
        SDL_RWread( file, &tileSetNumber, sizeof(int), 1);
        
        this->layerAmount = 3;
        this->currentLayer = 0;
        this->tileSetName = "space";
        area.w = newX*tileWidth;
        area.h = newY*tileHeight;
        area.x = 0;
        area.y = 0;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        this->tileSetNumber = tileSetNumber;
        
        //initializes the selection object
        mMapSelection = new MapSelection(tileWidth, tileHeight);
        
        for (int a = 0; a < layerAmount; a++)
            layer.push_back(new Layer(newX, newY, tileSetName));

        int tileID = 0;
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &tileID, sizeof(int), 1 );
                if (x < newX && y < newY) {
                    layer[0]->layer[x][y] = tileID;
                }
            }
        }
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &tileID, sizeof(int), 1 );
                if (x < newX && y < newY) {
                    layer[1]->layer[x][y] = tileID;
                }
            }
        }
        
        for( int x = 0; x < sizeX; x++ )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWread( file, &tileID, sizeof(int), 1 );
                if (x < newX && y < newY) {
                    layer[2]->layer[x][y] = tileID;
                }
            }
        }
        
        sizeX = newX;
        sizeY = newY;
        
        //Close file handler
        SDL_RWclose( file );
    }
}


void Map::drawMap(SDL_Surface* screen, TileSet* tileSet, int width, int height, int posx, int posy){
	SDL_Rect dst;
	for (std::vector<Layer*>::iterator it = layer.begin(); it != layer.end(); ++it){
		dst.x = 0;
		dst.y = 0;
		for (int x = posx, dX = 0; x < sizeX && dst.x < width - tileWidth - 1; x++, dX++){
			for (int y = posy, dY = 0; y < sizeY && dst.y < height - tileHeight - 1; y++, dY++){
				dst.x = dX * tileWidth;
				dst.y = dY * tileHeight;
                if ((*it)->layer[x][y] != 0)
                    SDL_BlitSurface(tileSet->tiles[(*it)->layer[x][y]]->tile
                                    , NULL
                                    , screen
                                    , &dst);
			}
			dst.y = 0;
		}
	}
}


void Map::drawLayer(SDL_Surface* screen, int layer_, std::vector<Tile*> tileSet, int width, int height, int posx, int posy){
	SDL_Rect dst;
	dst.x = 0 * tileWidth;
	dst.y = 0 * tileHeight;
	for (int x = posx; x < sizeX && dst.x < width-33; x++){
		for (int y = posy; y < sizeY && dst.y < height; y++){
			dst.x = (x) * tileWidth;
			dst.y = (y) * tileHeight;
			SDL_BlitSurface(tileSet[layer[(layer_ - 1)]->layer[x][y]]->tile
							, NULL
							, screen
							, &dst);
		}
		dst.y = 0;
	}
}

void Map::setAreaWithTile(int tileID){
    for (int x = mMapSelection->startPosition.x + mMapSelection->startOffset.x; x <= mMapSelection->endPosition.x && x < sizeX; x++) {
        for (int y = mMapSelection->startPosition.y + mMapSelection->startOffset.y; y <= mMapSelection->endPosition.y && y < sizeY; y++) {
            layer[currentLayer]->layer[x][y] = tileID;
        }
    }
}

void Map::Fill(int tileID){
    for (int x = 0; x < sizeX; x++){
        for (int y = 0; y < sizeY; y++){
            layer[currentLayer]->layer[x][y] = tileID;
        }
    }
}

void Map::setTile(int x, int y, TileSet* tileSet){
    if (!tileSet->mTileSelection->selected) return;

    int x_tiles;
    int y_tiles;
    
    int difference = (tileSet->mTileSelection->endPosition.x - tileSet->mTileSelection->startPosition.x);
    
    if (difference == 0) {
        x_tiles = 1;
    }else{
        x_tiles = (difference/tileWidth) + 1;
    }
    
    difference = (tileSet->mTileSelection->endPosition.y - tileSet->mTileSelection->startPosition.y);
    
    if (difference == 0) {
        y_tiles = 1;
    }else{
        y_tiles = (difference/tileWidth) + 1;
    }
    
    
    
    int tileID;
    Tile* tile;
    for (int ix = 0; ix < x_tiles && ix + x < sizeX; ix++) {
        for (int iy = 0; iy < y_tiles && iy + y < sizeY; iy++) {
            tile = tileSet->findTile(tileSet->mTileSelection->startPosition.x + (ix * tileWidth) + 1, tileSet->mTileSelection->startPosition.y + (iy * tileHeight), tileSet->mTileSelection->page);
            if (tile == NULL) {
                tileID = 0;
            }else{
                tileID = tileSet->findTile(tileSet->mTileSelection->startPosition.x + (ix * tileWidth) + 1, tileSet->mTileSelection->startPosition.y + (iy * tileHeight), tileSet->mTileSelection->page)->id;
            }
            layer[currentLayer]->layer[x+ix][y+iy] = tileID;
        }
    }
    
}

bool Map::save(const char* fileName){
    bool success = true;
    
    //Open data for writing
    file = SDL_RWFromFile(fileName, "w+b" );
    if( file != NULL )
    {
        //Save sizeX and sizeY
        SDL_RWwrite( file, &sizeX, sizeof(int), 1 );
        SDL_RWwrite( file, &sizeY, sizeof(int), 1 );
        SDL_RWwrite( file, &tileSetNumber, sizeof(int), 1 );
        //Save data
        for( int x = 0; x < sizeX; ++x )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWwrite( file, &layer[0]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        for( int x = 0; x < sizeX; ++x )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWwrite( file, &layer[1]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        for( int x = 0; x < sizeX; ++x )
        {
            for (int y = 0; y < sizeY; y++) {
                SDL_RWwrite( file, &layer[2]->layer[x][y], sizeof(int), 1 );
            }
        }
        
        //Close file handler
        SDL_RWclose( file );
    }
    else
    {
        printf( "Error: Unable to save file! %s\n", SDL_GetError() );
    }
    
    return success;
}

Map::~Map()
{
	for (std::vector<Layer*>::iterator it = layer.begin(); it != layer.end(); ++it)
		(*it)->~Layer();
}
