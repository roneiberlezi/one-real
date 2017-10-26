#include "Command.h"
#include "Global.h"

bool CommandHelp::execute(int argc, char* argv[]){
    help = !help;
    return true;
}

bool CommandSave::execute(int argc, char* argv[]){
    if (argc != 1) {
        printf("\nSpecify the file name!");
        return false;
    }
    mMap->save(argv[0]);
	return true;
}

bool CommandLoad::execute(int argc, char* argv[]){
    if (argc != 1) {
        printf("\nSpecify the file name!");
        return false;
    }
    
    if (mMap != NULL)
        mMap->~Map();
    
    mMap = new Map(argv[0], TILE_WIDTH, TILE_HEIGHT, 3, tileSetName.c_str(), TileSetNumber);
    
    if (mMap->fileNotFound) {
        if (mMap != NULL)
            mMap->~Map();
        mMap = new Map(0, 0, TILE_WIDTH, TILE_HEIGHT, 3, tileSetName.c_str(), TileSetNumber);
    }
    
    mMiniMap->setMapSize(mMap->sizeX, mMap->sizeY);
    return true;
}

bool CommandResize::execute(int argc, char* argv[]){
    if (argc != 3) {
        printf("\nSpecify the file name and size!");
        return false;
    }
    
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    
    if (mMap != NULL)
        mMap->~Map();
    
    mMap = new Map(x, y, argv[0], TILE_WIDTH, TILE_HEIGHT, 3, tileSetName.c_str(), TileSetNumber);
    
    if (mMap->fileNotFound) {
        if (mMap != NULL)
            mMap->~Map();
        mMap = new Map(0, 0, TILE_WIDTH, TILE_HEIGHT, 3, tileSetName.c_str(), TileSetNumber);
    }
    
    mMiniMap->setMapSize(mMap->sizeX, mMap->sizeY);
    return true;
}

bool CommandNew::execute(int argc, char* argv[]){
	if (argc != 2){
		printf("\nArguments are: width height!");
		return false;
	}
	int x = atoi(argv[0]);
	int y = atoi(argv[1]);
	//int layers = atoi(argv[2]);
    int layers = 3;

//	if (layers != 3){
//		printf("\nCurrent version suports only 3 layers!");
//		return false;
//	}

    if (mMap != NULL)
		mMap->~Map();
        
    mMap = new Map(x, y, TILE_WIDTH, TILE_HEIGHT, layers, tileSetName.c_str(), TileSetNumber);
    
    mMiniMap->setMapSize(mMap->sizeX, mMap->sizeY);
    
	printf("\nNew map created, size, layers: %d x %d x %d", x, y, layers);
	return true;
}

bool CommandSetPage::execute(int argc, char* argv[]){
	if (argc != 1){
		printf("\nArguments are: int <page_number>!");
		return false;
	}

	mTileSet->currentPage = atoi(argv[0]);
	return true;
}

bool CommandQuit::execute(int argc, char* argv[]){
	quit = true;
	return true;
}

bool CommandSpeed::execute(int argc, char* argv[]){
    if (argc != 1){
        printf("\nArguments are: int <moviment_speed>!");
        return false;
    }
    mMoviment.speed = atoi(argv[0]);
    return true;
}

bool CommandPosition::execute(int argc, char* argv[]){
    if (argc != 2){
        printf("\nArguments are: Uint <pos_x> Uint <pos_y>!");
        return false;
    }
    int newPositionX = atoi(argv[0]);
    int newPositionY = atoi(argv[1]);
    if (newPositionX >= 0 && newPositionY >= 0) {
        mMoviment.position.x = newPositionX;
        mMoviment.position.y = newPositionY;
    }else{
        printf("\nParameters must be positive numbers!");
    }
    return true;
}

bool CommandLayer::execute(int argc, char* argv[]){
    if (argc != 1){
        printf("\nArguments are: int <layer>!");
        return false;
    }
    if (mMap == NULL) {
        printf("\nFirst use NEW to create a map!");
        return false;
    }
    int newLayer = atoi(argv[0]);
    if (newLayer < 1 || newLayer > 3) {
        printf("\nLayer number shall be between 1 and 3!");
        return false;
    }
    newLayer -= 1;
    mMap->currentLayer = newLayer;
    mMoviment.speed = atoi(argv[0]);
    return true;
}

bool CommandFill::execute(int argc, char* argv[]){
    if (mMap == NULL) {
        printf("\nFirst use NEW to create a map!");
        return false;
    }
    
    if (mTileSet->mTileSelection->selected) {
        mMap->Fill(mTileSet->findTile(mTileSet->mTileSelection->rect.x, mTileSet->mTileSelection->rect.y, mTileSet->mTileSelection->page)->id);
    }else{
        printf("\nNo tile selected!");
        return false;
    }
    
    return true;
}