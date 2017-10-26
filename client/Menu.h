#ifndef _MENU_H_
#define _MENU_H_

#if defined(__APPLE__)						// If we are using a mac.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)	// If we are using a windows machine
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#include <string>
#include <iostream>
#include <regex>
#include "TextBox.h"
#include "Utils.h"
#include "Player.h"


class Menu{
	public: 
		Menu(SDL_Surface* screen 
			, TTF_Font* font
			, int fontSize
            , SDL_Window* window);
        int showMenu();
		bool startButton();
	private:
		Uint32 time;
		SDL_Color color[2];
		SDL_Surface* screen;
		TTF_Font* font;
		int fontSize;
		SDL_Color textColor;
		Uint32 bgColor;
        SDL_Window* window;
		

		//TEXTBOX
		TextBox* txtPlayer;
		TextBox* txtServer;

		//SURFACES
		SDL_Surface* background = NULL;
		SDL_Surface* menuBox = NULL;
		SDL_Surface* splashScreen = NULL;
		SDL_Surface* tituloSurface = NULL;
		SDL_Surface* ammoSplash = NULL;
		SDL_Surface* titleLogo = NULL;

		//Font
		TTF_Font* tituloFont = NULL;

};
#endif
