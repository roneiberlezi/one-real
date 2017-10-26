//
//  Map.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Map.h"

Map::Map(const char* fileName, int tileWidth, int tileHeight, int screenWidth, int screenHeight)
{


    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
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
        area.w = sizeX*tileWidth;
        area.h = sizeY*tileHeight;
        area.x = 0;
        area.y = 0;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        
        for (int a = 0; a < layerAmount; a++)
            layer.push_back(new Layer(sizeX, sizeY));
        
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
        
        currentTileSet = new TileSet(tileWidth, tileHeight, tileSetNumber);
        
        miniMap = new MiniMap(tileWidth, tileHeight, screenWidth, screenHeight);
        
        miniMap->setMapSize(sizeX, sizeY);
    }
}

void Map::drawMap(SDL_Surface* screen, int width, int height, SDL_Point cameraPosition){
    int spareX = cameraPosition.x%tileWidth;
    int spareY = cameraPosition.y%tileHeight;
    
    cameraPosition.x = cameraPosition.x/tileWidth;
    cameraPosition.y = cameraPosition.y/tileHeight;
    

    SDL_Rect dst;
    for (std::vector<Layer*>::iterator it = layer.begin(); it != layer.end(); ++it){
        dst.x = 0;
        dst.y = 0;
        for (int x = cameraPosition.x, dX = 0; x < sizeX && dst.x < width - tileWidth - 1; x++, dX++){
            for (int y = cameraPosition.y, dY = 0; y < sizeY && dst.y < height - tileHeight - 1; y++, dY++){
				dst.x = dX * tileWidth - spareX;
                dst.y = dY * tileHeight - spareY;
                if ((*it)->layer[x][y] != 0)
                    SDL_BlitSurface(currentTileSet->tiles[(*it)->layer[x][y]]->tile
                                    , NULL
                                    , screen
                                    , &dst);
            }
            dst.y = 0;
        }
    }
    
    miniMap->draw(screen, cameraPosition.x, cameraPosition.y);
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