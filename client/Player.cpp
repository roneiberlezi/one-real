//
//  Player.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Player.h"

#define PI 3.14159265

Player::Player(int x, int y, int w, int h, SDL_Surface* agentTexture, float colisionFactor, const char* nick, TTF_Font *font, WeaponType weapon, SDL_Surface* dead) : Agent(x, y, w, h, agentTexture, colisionFactor){
    
    this->font = font;
    this->kills = 0;
    this->deaths = 0;
	this->nickName = new char[50];
	this->currentHP = 100;
    this->maxHP = 100;
	this->deadSprite = dead;
    
    mMovement.speed = 160;


    mWeapon = new Weapon(100, 2, weapon);

	this->alive = true;

	strcpy(this->nickName, nick);
    
    this->playerType = playerType;
}

void Player::Heal(int amount)
{
	this->currentHP += amount;
	if (this->currentHP > this->maxHP)
	{
		this->currentHP = this->maxHP;
	}
}

void Player::handleMouseEvent(SDL_Event* e)
{
    if (!alive)
        return;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        if(SDL_BUTTON(SDL_BUTTON_LEFT)){
            
            //control fire rate
            if (SDL_GetTicks() < lastShot + (1000/mWeapon->weaponType.fireRate))
                return;
            
            lastShot = SDL_GetTicks();
            if (mWeapon->weaponType.type == 4) {
                mWeapon->Shoot(mMovement.position.x+width/2-8, mMovement.position.y+height/2-8, mMovement.lookAngle-8);
                mWeapon->Shoot(mMovement.position.x+width/2-8, mMovement.position.y+height/2-8, mMovement.lookAngle+8 );
            }
            mWeapon->Shoot(mMovement.position.x+width/2-8, mMovement.position.y+height/2-8, mMovement.lookAngle );
        }
    }

    
}

void Player::render(SDL_Surface *screenSurface){
	if (this->alive)
		Agent::render(screenSurface);
	else
	{
        destRect.x = mMovement.screenPosition.x;
        destRect.y = mMovement.screenPosition.y;
        SDL_Rect src;
        int time = SDL_GetTicks() - deathTime;
        
        src.y = 0;
        src.w = 80;
        src.h = 120;
        
        destRect.x += 10;
        destRect.y -= 50;
        
        if (time < 200)
            src.x = 0;
        else if(time >= 100 && time < 200)
            src.x = 80;
        else if(time >= 200 && time < 300)
            src.x = 160;
        else if(time >= 300 && time < 400)
            src.x = 240;
        else
            src.x = 320;
            

        SDL_BlitSurface(this->deadSprite, &src, screenSurface, &destRect);
	}


    renderLifeBar(screenSurface, mMovement.screenPosition.x, mMovement.screenPosition.y);
    renderNickName(screenSurface, mMovement.screenPosition.x, mMovement.screenPosition.y);
    renderHUD(screenSurface, mMovement.screenPosition.x, mMovement.screenPosition.y);
}

void Player::renderHUD(SDL_Surface *screenSurface,int x, int y){
    
    //HUD Ammo
    std::string auxString;
    std::stringstream auxIntCurrent;
    std::stringstream auxIntMax;
	SDL_Rect temp;

	if (ammoBG == NULL)
		loadMedia("ammoBG.png", &ammoBG);

	temp.x = 1024 - ammoBG->clip_rect.w;
	temp.y = 640 - ammoBG->clip_rect.h;

	SDL_BlitSurface(ammoBG, NULL, screenSurface, &temp);
	
	if (textFont == NULL)
	{
		textFont = TTF_OpenFont("ARIAL.ttf", 17);
		TTF_SetFontStyle(textFont, TTF_STYLE_BOLD);
	}
    if (mWeapon->currentAmmo<10){
        auxIntCurrent << "00" << mWeapon->currentAmmo;
    }else if(mWeapon->currentAmmo<100){
        auxIntCurrent << "0" << mWeapon->currentAmmo;
    }else{
        auxIntCurrent << mWeapon->currentAmmo;
    }
    auxIntMax << mWeapon->maxAmmo;
    
    auxString = "Ammo: " + auxIntCurrent.str() + " / " + auxIntMax.str();
    
    SDL_Color color = {255,255,255,0};
    
    textSurface = TTF_RenderText_Solid(textFont, auxString.c_str(), color);
    
	bar.x = temp.x + ammoBG->w / 2 - mWeapon->weaponType.weaponSurface->w / 2;
	bar.y = temp.y + ammoBG->h / 2 - mWeapon->weaponType.weaponSurface->h / 2;
    
	SDL_BlitSurface(mWeapon->weaponType.weaponSurface, NULL, screenSurface, &bar);
    
	temp.x = temp.x + ammoBG->w / 2 - textSurface->w / 2;
	temp.y = bar.y + (mWeapon->weaponType.weaponSurface->h + 5);
    //temp.w = (1024-temp.x);
    //temp.h = (768-temp.y);
    //SDL_FillRect(screenSurface, &temp, color32(80, 80, 80, 0));
    
    SDL_BlitSurface(textSurface,NULL,screenSurface, &temp);
	SDL_FreeSurface(textSurface);
    
    bar.y -= (mWeapon->weaponType.weaponSurface->h + 10);
    //SDL_BlitSurface(mWeapon->weaponType.weaponSurface, NULL, screenSurface, &bar);
   
    //HUD Life

	SDL_Rect profileSheet;
	SDL_Rect posLifebar;

	if (profileImg == NULL)
		loadMedia("profile.png", &profileImg);

	profileSheet.h = 72;
	profileSheet.w = 80;
	if (currentHP > 80)
	{
		profileSheet.x = 0;
		profileSheet.y = 0;
	}
	else if (currentHP > 60)
	{
		profileSheet.x = 80;
		profileSheet.y = 160;
	}
	else if (currentHP > 30)
	{
		profileSheet.x = 160;
		profileSheet.y = 160;
	}
	else 
	{
		profileSheet.x = 240;
		profileSheet.y = 160;
	}
	posLifebar.x = 3;
	posLifebar.y = 637 - 74;

	if (lifebarBG==NULL)
		loadMedia("lifebar.png", &lifebarBG);

	posLifebar.x = 1;
	posLifebar.y = 639 - lifebarBG->clip_rect.h;

	SDL_BlitSurface(profileImg, &profileSheet, screenSurface, &posLifebar);
	SDL_BlitSurface(lifebarBG, NULL, screenSurface, &posLifebar);

	bar.x = posLifebar.x+ 85;
    bar.y = posLifebar.y+ 37;
    bar.w = 390;
	bar.h = 34;
    
    drawUnfilledRect(screenSurface, &bar, 2, color32(0, 0, 0, 0));
    
    bar.x = bar.x + 2;
    bar.y = bar.y + 2;
    bar.w = currentHP*(3.86);
    bar.h = 32;
    
    SDL_FillRect(screenSurface, &bar, color32(0, 255, 0, 0));
	
	textSurface = TTF_RenderText_Solid(textFont, nickName, color);

	bar.x = posLifebar.x + 216 - textSurface->clip_rect.w/2;
	bar.y = posLifebar.y + 18 - textSurface->clip_rect.h / 2;
	SDL_BlitSurface(textSurface, NULL, screenSurface, &bar);
	SDL_FreeSurface(textSurface);	
    
    //HUD Death
    
    if (this->alive == false){
        int diferenceTime;
        std::string deathString;
        std::stringstream diferenceString;
        SDL_Rect position;
		if (halloweenFont== NULL)
			halloweenFont = TTF_OpenFont("halloween.ttf", 100);
        color = {255,0,0,0};
        
        //Loading Skull
		if (deathSurface == NULL)
		{
			loadMedia("skull.bmp", &deathSurface);
			SDL_SetColorKey(deathSurface, SDL_TRUE, SDL_MapRGB(deathSurface->format, 0, 0, 0));
		}
        
        position.x = (screenSurface->w/2) - (deathSurface->w/2);
        position.y = ((screenSurface->h/2) - (deathSurface->h)) -23 ;
        
        SDL_BlitSurface(deathSurface,NULL,screenSurface,&position);
        //Loading text You are dead
        deathString = "You are dead!";
        textSurface = TTF_RenderText_Solid(halloweenFont, deathString.c_str(), color);
        
        position.x= (screenSurface->w/2) - (textSurface->w/2);
        position.y= ((screenSurface->h/2) - (textSurface->h/2)) - 10;
        
        SDL_BlitSurface(textSurface,NULL,screenSurface,&position);
		SDL_FreeSurface(textSurface);
        //Loading respawn counting
        position.y = position.y+60;
        
        diferenceTime = 6 - ((SDL_GetTicks() - this->deathTime)/1000) ;
        if (diferenceTime >0) {
            diferenceString << diferenceTime;
        }else{
            diferenceString << "0";
        }
        deathString = " Respawn in " + diferenceString.str();
        
        textSurface = TTF_RenderText_Solid(halloweenFont, deathString.c_str(), color);
        SDL_BlitSurface(textSurface,NULL,screenSurface,&position);
		SDL_FreeSurface(textSurface);
        
    }
    
    
}

//tem q deletar a surface do nickname
void Player::renderNickName(SDL_Surface *screenSurface, int x, int y){

	SDL_Color color = { 255, 255, 255, 0 };
	textSurface = TTF_RenderText_Solid(font, this->nickName, color);

    bar.x = x + width/2 - textSurface->w/2;
    if (isNPC)
        bar.y = y-32;
    else
        bar.y = y-12;
    
    
    SDL_BlitSurface(textSurface,NULL,screenSurface,&bar);
	SDL_FreeSurface(textSurface);
}

void Player::renderLifeBar(SDL_Surface *screenSurface, int x, int y){
    bar.x = x + width/2 - 25;
    if (isNPC)
        bar.y = y-20;
    else
        bar.y = y;
    bar.w = 52;
    bar.h = 10;
    
    drawUnfilledRect(screenSurface, &bar, 1, color32(255, 0, 0, 0));
    
    bar.x = x + width/2 - 24;
    bar.y = bar.y + 1;
    bar.w = currentHP/2;
    bar.h = 9;
    if (isNPC)
        SDL_FillRect(screenSurface, &bar, color32(237, 108, 38, 0));
    else
        SDL_FillRect(screenSurface, &bar, color32(0, 255, 0, 0));
}

void Player::renderBullet(SDL_Surface* screenSurface){    
    for (std::map<int,Bullet*>::iterator it=mWeapon->bulletMap.begin(); it!=mWeapon->bulletMap.end(); ++it)
        (*it).second->render(screenSurface, mMovement.cameraPosition);
}

void Player::renderKillMessage(SDL_Surface *screenSurface, std::vector<std::string>* killMessage){
    textSurface=NULL;
    SDL_Rect messagePos;
    SDL_Color color = {255,255,255,0};
 
    if(killMessage->size() >0){
        if (this->drawingKill ==false){
            this->initialTime=SDL_GetTicks();
            this->drawingKill=true;
        }
		killFont = TTF_OpenFont("titulo.ttf", 40);
        textSurface = TTF_RenderText_Solid(killFont, (*killMessage)[0].c_str(), color);
		messagePos.x = (screenSurface->w/2)-(textSurface->w/2);
		messagePos.y = 60;
        SDL_BlitSurface(textSurface,NULL,screenSurface,&messagePos);
		SDL_FreeSurface(textSurface);
        if( SDL_GetTicks() > this->initialTime + 3000){
            this->drawingKill=false;
            killMessage->erase(killMessage->begin());
        }
    }
}

void Player::renderOnMap(SDL_Surface *screenSurface, SDL_Point cameraPosition, std::vector<std::string>* killMessage){
    destRect.x = mMovement.position.x - cameraPosition.x;
    destRect.y = mMovement.position.y - cameraPosition.y;
    
    if (isNPC) {
        
        if (SDL_GetTicks() > frameTimer+150) {
            frameTimer = SDL_GetTicks();
            if (frameIncreasing) {
                currentFrame++;
                if (currentFrame > 2) {
                    currentFrame = 1;
                    frameIncreasing = false;
                }
            }else if (frameIncreasing == false){
                currentFrame--;
                if (currentFrame < 0) {
                    currentFrame = 1;
                    frameIncreasing = true;
                }
            }
        }
        
        sourceRect.x = (playerType-1)*96 + (currentFrame*32);
        
        if (mMovement.lookAngle >= 315 || mMovement.lookAngle < 45) {
            sourceRect.y = 32;
        }else if (mMovement.lookAngle >= 45 && mMovement.lookAngle < 135) {
            sourceRect.y = 96;
        }else if (mMovement.lookAngle >= 135 && mMovement.lookAngle < 225) {
            sourceRect.y = 64;
        }else if (mMovement.lookAngle >= 225 && mMovement.lookAngle < 315) {
            sourceRect.y = 0;
        }
    }
    
    if (alive)
        SDL_BlitSurface(texture, &sourceRect, screenSurface, &destRect);
    else{
        SDL_Rect src;
        int time = SDL_GetTicks() - deathTime;
        
        src.y = 0;
        src.w = 80;
        src.h = 120;
        
        destRect.x += 10;
        destRect.y -= 50;
        
        if (time < 200)
            src.x = 0;
        else if(time >= 100 && time < 200)
            src.x = 80;
        else if(time >= 200 && time < 300)
            src.x = 160;
        else if(time >= 300 && time < 400)
            src.x = 240;
        else
            src.x = 320;
        
        
        SDL_BlitSurface(deadSprite, &src, screenSurface, &destRect);
    }
    
    renderLifeBar(screenSurface, mMovement.position.x - cameraPosition.x, mMovement.position.y - cameraPosition.y);
    renderNickName(screenSurface, mMovement.position.x - cameraPosition.x, mMovement.position.y - cameraPosition.y);
    renderKillMessage(screenSurface, killMessage);
}
