//
//  Agent.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Agent.h"


#define PI 3.14159265


Agent::Agent( int x, int y, int w, int h, float colisionFactor){
    width = w;
    height = h;
    
    mMovement.position.x = x;
    mMovement.position.y = y;
	mMovement.cameraPosition.x = 0;
	mMovement.cameraPosition.y = 0;
    
    sourceRect.w = w;
    sourceRect.h = h;
    sourceRect.x = 0;
    sourceRect.y = 0;
    
    destRect.w = w;
    destRect.h = h;
    destRect.x = x;
    destRect.y = y;
    
    colisionRect.x = x;
    colisionRect.y = y;
    colisionRect.w = w;
    colisionRect.h = h;
}


void Agent::render(SDL_Surface* screenSurface){
    destRect.x = mMovement.screenPosition.x;
    destRect.y = mMovement.screenPosition.y;
    SDL_BlitSurface(texture, &sourceRect, screenSurface, &destRect);
}

void Agent::setPosition(int x, int y){
    mMovement.position.x = x;
    mMovement.position.y = y;
    
    if (x > 512-width/2) {
        mMovement.cameraPosition.x = mMovement.position.x - (512-width/2);
        mMovement.screenPosition.x = 512-width/2;
    }else{
        mMovement.cameraPosition.x = 0;
        mMovement.screenPosition.x = x;
    }
    
    if (y > 320-height/2) {
        mMovement.cameraPosition.y = mMovement.position.y - (320-height/2);
        mMovement.screenPosition.y = 320-height/2;
    }else{
        mMovement.cameraPosition.y = 0;
        mMovement.screenPosition.y = y;
    }
    
    //mCollider.x = x;
    //mCollider.y = y;
    destRect.x = mMovement.screenPosition.x;
    destRect.y = mMovement.screenPosition.y;
    setColisionRectPosition(x, y);
}

void Agent::setColisionRectPosition(int x, int y){
    colisionRect.x = x + (width*0.33);
    colisionRect.y = y + height/3;
}

void Agent::setLookAngle(int a){
	mMovement.lookAngle = a;
	//printf ("The arc tangent is %d degrees\n", result);
	if ((a <= 3) || (a > 357)){
		//0 = 480 192 96 96
		sourceRect.x = 480;
		sourceRect.y = 192;
	}
	else if (a <= 15) {
		//11,25 = 672 0 96 96
		sourceRect.x = 672;
		sourceRect.y = 0;
	}
	else if (a <= 27) {
		//22,5 = 672 96 96 96
		sourceRect.x = 672;
		sourceRect.y = 96;
	}
	else if (a <= 39) {
		//33,75 = 576 192 96 96
		sourceRect.x = 576;
		sourceRect.y = 192;
	}
	else if (a <= 51) {
		//45 = 480 288 96 96
		sourceRect.x = 480;
		sourceRect.y = 288;
	}
	else if (a <= 63) {
		//56,25 = 576 288 96 96
		sourceRect.x = 576;
		sourceRect.y = 288;
	}
	else if (a <= 75) {
		//67,5 = 672 192 96 96
		sourceRect.x = 672;
		sourceRect.y = 192;
	}
	else if (a <= 87) {
		//78,75= 672 288 96 96
		sourceRect.x = 672;
		sourceRect.y = 288;
	}
	else if (a <= 93) {
		//90 = 0 0 96 96
		sourceRect.x = 0;
		sourceRect.y = 0;
	}
	else if (a <= 105) {
		//101,25 = 96 0 96 96
		sourceRect.x = 96;
		sourceRect.y = 0;
	}
	else if (a <= 117) {
		//112,5 = 0 96 96 96
		sourceRect.x = 0;
		sourceRect.y = 96;
	}
	else if (a <= 129) {
		//123,75 = 96 96 96 96
		sourceRect.x = 96;
		sourceRect.y = 96;
	}
	else if (a <= 141) {
		//135 = 192 0 96 96
		sourceRect.x = 192;
		sourceRect.y = 0;
	}
	else if (a <= 153) {
		//146,25 = 192 96 96 96
		sourceRect.x = 192;
		sourceRect.y = 96;
	}
	else if (a <= 165) {
		//157,5 = 288 0 96 96
		sourceRect.x = 288;
		sourceRect.y = 0;
	}
	else if (a <= 177) {
		//168,75 = 384 0 96 96
		sourceRect.x = 384;
		sourceRect.y = 0;
	}
	else if (a <= 183) {
		//180 = 288 96 96 96
		sourceRect.x = 288;
		sourceRect.y = 96;
	}
	else if (a <= 195) {
		//191,25 = 384 96 96 96
		sourceRect.x = 384;
		sourceRect.y = 96;
	}
	else if (a <= 207) {
		//202,5 = 0 192 96 96
		sourceRect.x = 0;
		sourceRect.y = 192;
	}
	else if (a <= 219) {
		//213,75 = 96 192 96 96
		sourceRect.x = 96;
		sourceRect.y = 192;
	}
	else if (a <= 231) {
		//225 = 0 288 96 96
		sourceRect.x = 0;
		sourceRect.y = 288;
	}
	else if (a <= 243) {
		//236,25 = 192 192 96 96
		sourceRect.x = 192;
		sourceRect.y = 192;
	}
	else if (a <= 255) {
		//247,5 = 96 288 96 96
		sourceRect.x = 96;
		sourceRect.y = 288;
	}
	else if (a <= 267) {
		//258,75 = 288 192 96 96
		sourceRect.x = 288;
		sourceRect.y = 192;
	}
	else if (a <= 273) {
		//270 = 192 288 96 96
		sourceRect.x = 192;
		sourceRect.y = 288;
	}
	else if (a <= 285) {
		//281,25 = 288 288 96 96
		sourceRect.x = 288;
		sourceRect.y = 288;
	}
	else if (a <= 297) {
		//292,5 = 384 192 96 96
		sourceRect.x = 384;
		sourceRect.y = 192;
	}
	else if (a <= 309) {
		//303,75 = 384 288 96 96
		sourceRect.x = 384;
		sourceRect.y = 288;
	}
	else if (a <= 321) {
		//315 = 480 0 96 96
		sourceRect.x = 480;
		sourceRect.y = 0;
	}
	else if (a <= 333) {
		//326,25 = 576 0 96 96
		sourceRect.x = 576;
		sourceRect.y = 0;
	}
	else if (a <= 345) {
		//337,5 = 480 96 96 96
		sourceRect.x = 480;
		sourceRect.y = 96;
	}
	else if (a <= 357) {
		//348,75 = 576 96 96 96
		sourceRect.x = 576;
		sourceRect.y = 96;
	}
}

void Agent::setLookPosition(int x, int y){
    mMovement.lookPosition.x = x;
    mMovement.lookPosition.y = y;
    
    int result;
    result = atan2((mMovement.screenPosition.y+48)-y, (mMovement.screenPosition.x+48)-x) * 180 / PI;
    if (result < 0) {
        result += 360;
    }

	setLookAngle(result);
}

void Agent::handleEvent(SDL_Event* e )
{
    if (e->type == SDL_KEYDOWN){
        switch (e->key.keysym.sym){
            case SDLK_w:
                if (!mMovement.up) {
                    mMovement.up = true;
                    mMovement.velY -= mMovement.speed;
                }
                break;
            case SDLK_s:
                if (!mMovement.down) {
                    mMovement.down = true;
                    mMovement.velY += mMovement.speed;
                }
                break;
            case SDLK_d:
                if (!mMovement.right) {
                    mMovement.right = true;
                    mMovement.velX += mMovement.speed;
                }
                break;
            case SDLK_a:
                if (!mMovement.left) {
                    mMovement.left = true;
                    mMovement.velX -= mMovement.speed;
                }
                break;
        }
    } else {
        if (e->type == SDL_KEYUP){ // this should also be checked for which key has gone up.
            switch (e->key.keysym.sym){
                case SDLK_w:
                    mMovement.up = false;
                    mMovement.velY += mMovement.speed;
                    break;
                case SDLK_s:
                    mMovement.down = false;
                    mMovement.velY -= mMovement.speed;
                    break;
                case SDLK_d:
                    mMovement.right = false;
                    mMovement.velX -= mMovement.speed;
                    break;
                case SDLK_a:
                    mMovement.left = false;
                    mMovement.velX += mMovement.speed;
                    break;
            }
        }
    }
}