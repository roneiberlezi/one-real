#include "Menu.h"
#include "Global.h"

Menu::Menu( SDL_Surface* screen
           , TTF_Font* font
           , int fontSize
           , SDL_Window* window)
{
    this->screen = screen;
    this->font = font;
    this->fontSize = fontSize;
    this->window = window;
};

bool Menu::startButton(){
    std::regex reg1("\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    txtServer->text.erase(txtServer->text.begin());
    txtPlayer->text.erase(txtPlayer->text.begin());
    
    bool sucess = std::regex_match(txtServer->text.begin(), txtServer->text.end(), reg1);
    
    if (sucess){
        std::cout << "IP Address Valid";
        
        strcpy(ipMenu, txtServer->text.c_str());
        strcpy(nickMenu, txtPlayer->text.c_str());


        mPlayer = new Player(50, 50, 96, 96, playerSprite, 0.33, nickMenu,font, weapon1, dead);
        
        
        net = new network(ipMenu, mPlayer->nickName);
        
        if(net->connected == true)
            return true;
        else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Connection Error", "Can not connect to the IP Address", this->window);
            return false;
        }
    }
    else{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Connection Error", "IP Address is not Valid!", this->window);
        return false;
    }
}

int Menu::showMenu(){
    int x, y;
    
    TTF_SetFontStyle(this->font, TTF_STYLE_BOLD);
    /*NUMMENU is the number of options the menu will have*/
    const int NUMMENU= 4;
    /*A label for each menu option*/
    const char* labels[NUMMENU] = {"PLAYER","SERVER","START", "EXIT"};

    SDL_Surface* menus[NUMMENU];
    bool selected[NUMMENU] = {0,0,0,0};
    SDL_Color color[3] = {{255,255,255,0},{0,0,255,0} , {0,0,0,0}};
    
	if (tituloFont == NULL);
		tituloFont = TTF_OpenFont("titulo.ttf", 150);
    
	if (menuBox == NULL)
		loadMedia("menu.png", &menuBox);

	SDL_Rect posMenu;
    
    
	posMenu.x = screen->clip_rect.w / 2 - menuBox->clip_rect.w / 2;
	posMenu.y = screen->clip_rect.h / 2 - menuBox->clip_rect.h / 2;

    /*Sets the menu's surfaces*/
    menus[0] = TTF_RenderText_Solid(font,labels[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font,labels[1], color[0]);
    menus[2] = TTF_RenderText_Solid(font,labels[2], color[0]);
    menus[3] = TTF_RenderText_Solid(font,labels[3], color[0]);
    
    
    /*create rectangle for each label*/
    SDL_Rect pos[NUMMENU];
    
    pos[0].x = posMenu.x + 70;
    pos[0].y = posMenu.y + 70;
    pos[0].w = menus[0]->clip_rect.w;
    pos[0].h = menus[0]->clip_rect.h;
    
    pos[1].x = posMenu.x + 70;
    pos[1].y = pos[0].y + menus[0]->h +25;
    pos[1].w = menus[1]->clip_rect.w;
    pos[1].h = menus[1]->clip_rect.h;
    
    pos[2].x = posMenu.x + 145;
    pos[2].y = posMenu.y + 155;
    pos[2].w = menus[2]->clip_rect.w;
    pos[2].h = menus[2]->clip_rect.h;
    
    pos[3].x = posMenu.x + 150;
    pos[3].y = pos[2].y + menus[2]->h + 20;
    pos[3].w = menus[3]->clip_rect.w;
    pos[3].h = menus[3]->clip_rect.h;
    
    
    
    /*create rectangle for each textbox*/
    SDL_Rect posTxt[2];
    posTxt[0].x = pos[0].x + menus[0]->clip_rect.w +10;
    posTxt[0].y = pos[0].y;
    posTxt[0].w = 120;
    posTxt[0].h = menus[0]->clip_rect.h;
    
    posTxt[1].x = posTxt[0].x;
    posTxt[1].y = pos[1].y;
    posTxt[1].w = 120;
    posTxt[1].h = menus[1]->clip_rect.h;
    
    
    
    //opening the text box
    txtPlayer = new TextBox(screen, font, fontSize, color[0], color32(10, 10, 70, 0), posTxt[0]);
    txtPlayer->setRender(true);
    txtServer = new TextBox(screen, font, fontSize, color[0], color32(10, 10, 70, 0), posTxt[1]);
    txtServer->setRender(true);
    
    SDL_Rect auxTxt[2];
    auxTxt[0].x = pos[0].x + menus[0]->clip_rect.w +10;
    auxTxt[0].y = pos[0].y;
    auxTxt[0].w = 130;
    auxTxt[0].h = menus[0]->clip_rect.h;
    
    auxTxt[1].x = pos[1].x + menus[1]->clip_rect.w +10;
    auxTxt[1].y = pos[1].y;
    auxTxt[1].w = 130;
    auxTxt[1].h = menus[1]->clip_rect.h;
    
    
    
    SDL_FillRect(screen, &auxTxt[0], color32(10, 10, 70, 0));
    
    SDL_FillRect(screen, &auxTxt[1], color32(10, 10, 70, 0));
    
    //Building title
    std::string tituloString = "ONE    REAL";
    SDL_Rect titlePos;
    titlePos.x = screen->w/5;
    titlePos.y = (screen->h/2) - 280;
    tituloSurface = TTF_RenderText_Solid(tituloFont, tituloString.c_str(), color[0]);
    
	if (titleLogo == NULL)
		loadMedia("skull_logo.bmp", &titleLogo);

    SDL_SetColorKey(titleLogo, SDL_TRUE, SDL_MapRGB(titleLogo->format, 0, 0, 0));
    
    SDL_Rect logoPos;
    logoPos.x = (screen->w/2) - titleLogo->w/2;
    logoPos.y = (screen->h/2) - 300;
    
	if (background == NULL)
		background = SDL_LoadBMP("background.bmp");
	if (splashScreen == NULL)
		splashScreen = SDL_LoadBMP("splashScreen.bmp");
	if (ammoSplash == NULL)
		loadMedia("ammoSplash.png", &ammoSplash);
    SDL_Rect ammoSplashPos;
    bool sucess1 = true;
    bool sucess2 = true;
    bool sucess3 = true;
    bool startGame = false;
    
    int time;
    time = SDL_GetTicks();
    
    SDL_Event event;
	txtPlayer->setEnabled(true);
	txtServer->setEnabled(false);
	while(true)
	{
        
		SDL_BlitSurface(background, NULL, screen, NULL);
		
        SDL_BlitSurface(titleLogo,NULL,screen,&logoPos);
        
        SDL_BlitSurface(tituloSurface,NULL,screen,&titlePos);
        
		SDL_BlitSurface(menuBox, NULL, screen, &posMenu);

        SDL_BlitSurface(menus[0],NULL,screen,&pos[0]);
        
        SDL_BlitSurface(menus[1],NULL,screen,&pos[1]);
        
        SDL_BlitSurface(menus[2],NULL,screen,&pos[2]);
        
        SDL_BlitSurface(menus[3],NULL,screen,&pos[3]);
        
        txtPlayer->update();
        txtServer->update();
        
		while(SDL_PollEvent(&event))
		{
            txtPlayer->handleKeys(&event);
            txtServer->handleKeys(&event);
			switch (event.type)
			{
				case SDL_QUIT:
					for (int i=0;i<NUMMENU;i++)
						SDL_FreeSurface(menus[i]);
					
					SDL_FreeSurface(background);
					SDL_FreeSurface(menuBox);
					SDL_FreeSurface(splashScreen);
					SDL_FreeSurface(tituloSurface);
					SDL_FreeSurface(ammoSplash);
					SDL_FreeSurface(titleLogo);
					txtPlayer->~TextBox();
					txtServer->~TextBox();
					return 0;
				/*when the mouse goes over the text label it will change
				**to the color RED, when the mouse goes out it will change
				**back to the color white*/
				case SDL_MOUSEMOTION:
					x=event.motion.x;
					y=event.motion.y;
					for (int i=2; i<NUMMENU; i++)
					{
						if((x>=pos[i].x && x<=(pos[i].x+menus[i]->w)) && (y>=pos[i].y && y<=(pos[i].y+menus[i]->h)))
						{
							if (!selected[i])
							{
								selected[i]=1;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i], color[1]);
							}
						}else{
							if (selected[i])
							{
								selected[i]=0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i], color[0]);
							}
						}
					}
                    break;
				case SDL_MOUSEBUTTONDOWN:
					if (SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						x = event.motion.x;
						y = event.motion.y;
						for (int i = 2; i < NUMMENU; i++)
						{
							if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
							{
								if (i == 2){
									//if click start button
									startGame = startButton();
                                    txtPlayer->text = "";
                                    txtServer->text= "";
                                    
								}
                                if(startGame== true || i==3){
                                    for (int j = 0; j<4; j++)
                                        SDL_FreeSurface(menus[j]);
                                    SDL_FreeSurface(background);
                                    SDL_FreeSurface(menuBox);
                                    SDL_FreeSurface(splashScreen);
                                    SDL_FreeSurface(tituloSurface);
                                    SDL_FreeSurface(ammoSplash);
                                    SDL_FreeSurface(titleLogo);
                                    txtPlayer->~TextBox();
                                    txtServer->~TextBox();
                                    return i;
                                }
							}
							for (int i = 0; i < 2; i++){
								if (x >= auxTxt[i].x && x <= auxTxt[i].x + auxTxt[i].w && y >= auxTxt[i].y && y <= auxTxt[i].y + auxTxt[i].h)
								{
									if (i == 0){
										txtPlayer->setEnabled(true);
										txtServer->setEnabled(false);
									}
									else{
										txtServer->setEnabled(true);
										txtPlayer->setEnabled(false);
									}
								}
							}
						}
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym==SDLK_ESCAPE)
						return 0;
					if (event.key.keysym.sym == 13)
					{
						startGame = startButton();
                        
                        if (startGame == true){
                            for (int j = 0; j<4; j++)
                                SDL_FreeSurface(menus[j]);

                            SDL_FreeSurface(background);
                            SDL_FreeSurface(menuBox);
                            SDL_FreeSurface(splashScreen);
                            SDL_FreeSurface(tituloSurface);
                            SDL_FreeSurface(ammoSplash);
                            SDL_FreeSurface(titleLogo);
                            txtPlayer->~TextBox();
                            txtServer->~TextBox();
                            return 2;
                        }
					}
					if (event.key.keysym.sym == SDLK_TAB)
					{
						if (!txtPlayer->getEnable())
						{
							txtPlayer->setEnabled(true);
							txtServer->setEnabled(false);
						}
						else if (txtPlayer->getEnable())
						{
							txtPlayer->setEnabled(false);
							txtServer->setEnabled(true);
						}
					}
			}
		}
        
        //Splash screen
        if (time + 4000 > SDL_GetTicks()){
            SDL_BlitSurface(splashScreen,NULL,screen,NULL);
            if (SDL_GetTicks() > 1000) {
                if(sucess1){
                    Mix_PlayChannel(-1, gOpenning, 0);
                    sucess1=false;
                }
                ammoSplashPos.x = 320;
                ammoSplashPos.y = 160;
                SDL_BlitSurface(ammoSplash,NULL,screen,&ammoSplashPos);
            }
            if (SDL_GetTicks() > 1500){
                if(sucess2){
                    Mix_PlayChannel(-1, gOpenning, 0);
                    sucess2=false;
                }
                ammoSplashPos.x = 640;
                ammoSplashPos.y = 300;
                SDL_BlitSurface(ammoSplash,NULL,screen,&ammoSplashPos);
            }
            if(SDL_GetTicks()>2000){
                if(sucess3){
                    Mix_PlayChannel(-1,gOpenning,0);
                    sucess3=false;
                }
                ammoSplashPos.x = 320;
                ammoSplashPos.y = 400;
                SDL_BlitSurface(ammoSplash,NULL,screen,&ammoSplashPos);
            }
        }
        SDL_UpdateWindowSurface(window);
    }
}

