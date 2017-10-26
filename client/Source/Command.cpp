#include "Command.h"
#include "Global.h"
//
//bool CommandHelp::execute(int argc, char* argv[]){
//    help = !help;
//    return true;
//}
//
//bool CommandSave::execute(int argc, char* argv[]){
//    if (argc != 1) {
//        printf("\nSpecify the file name!");
//        return false;
//    }
//    mMap->save(argv[0]);
//	return true;
//}
//


bool CommandConnect::execute(int argc, char* argv[]){
	

	if (net != NULL)
	{
		printf("\n You still are connected!");
		return true;
	}
	else
	{
		if (argc < 2) {
			printf("\nSpecify the server ip and nickname!");
			return false;
		}

		net = new network(argv[0], argv[1]);
	}
		
	

	return true;
}

bool CommandDisconnect::execute(int argc, char* argv[]){

	if (net != NULL)
		delete net;

	net = NULL;

	printf("\n Disconnected!");

	return true;
}

bool CommandLoad::execute(int argc, char* argv[]){
    if (argc != 1) {
        printf("\nSpecify the file name!");
        return false;
    }
    
    if (mMap != NULL)
        mMap->~Map();
    
    mMap = new Map(argv[0], TILE_WIDTH, TILE_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if (mMap->fileNotFound) {
        if (mMap != NULL)
            mMap->~Map();
        mMap = NULL;
    }
    
    
    return true;
}

bool CommandPlayerDemo::execute(int argc, char* argv[]){
   // SDL_Surface* bufferSurface;
 //   loadMedia("SpriteSheet.png", &bufferSurface);
//    loadMedia("player.bmp", &bufferSurface);
//    mPlayer = new Player(50, 50, 64, 64, bufferSurface);
	mPlayer = new Player(50, 50, 96, 96, playerSprite, 0.33, nickMenu, font, weapon1, dead);
    return true;
}

bool CommandDemoServer::execute(int argc, char* argv[]){
    //SDL_Surface* bufferSurface;
    //loadMedia("SpriteSheet.png", &bufferSurface);
    //    loadMedia("player.bmp", &bufferSurface);
    //    mPlayer = new Player(50, 50, 64, 64, bufferSurface);
	mPlayer = new Player(50, 50, 96, 96, playerSprite, 0.33, nickMenu, font, weapon1, dead);
    
    if (mMap != NULL)
        mMap->~Map();
    
    mMap = new Map("map", TILE_WIDTH, TILE_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if (mMap->fileNotFound) {
        if (mMap != NULL)
            mMap->~Map();
        mMap = NULL;
    }
    
    if (net != NULL)
    {
        printf("\n You still are connected!");
        return true;
    }
    else
    {
        net = new network("127.0.0.1",mPlayer->nickName);
    }
    
    return true;
}
