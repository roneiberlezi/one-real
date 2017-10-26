//
//  Agent.h
//  Game Project
//
//  Created by Ronei Berlezi on 05/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef Game_Project_Agent_h
#define Game_Project_Agent_h

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>

#endif

#include "Utils.h"
#include <math.h>

class Agent{
public:
    int width;
    int height;
    
    Movement mMovement; //Position and directions
    SDL_Surface* texture; //frames de animação do player
    SDL_Rect sourceRect;//posição da textura que vai copiar
    SDL_Rect destRect;//Posição na tela que vai desenhar
    SDL_Rect colisionRect;
    int deltaTime;
    
    bool isNPC = false;
    int playerType = 0;
    int currentFrame = 0;
    bool frameIncreasing = true;
    int frameTimer;

    
    //Agent's collision circle
    //Circle mCollider;
    //Circle mColliderNext;
    
    //Moves the collision circle relative to the agent's offset
    void setPosition(int x, int y, int mapSizeX, int mapSizeY);
    
    //
    void setColisionRectPosition(int x, int y);

    void handleEvent(SDL_Event* e);
    
    Agent( int x, int y, int w, int h,SDL_Surface* agentTexture, float colisionFactor);
    
    //Moves the agent and checks collision
    //void move( SDL_Rect& square, Circle& circle, int width, int height );
    
    //Shows the agent on the screen
    void render(SDL_Surface* screenSurface);
    void renderAsItem(SDL_Surface* screenSurface, SDL_Point cameraPosition);
    
    void setLookPosition(int x, int y);
	void setLookAngle(int a);
    //Gets collision circle
    //Circle& getCollider();
   // Circle& getCollider(SDL_Point newPos);
};


#endif
