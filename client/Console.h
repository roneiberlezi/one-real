#ifndef _CONSOLE_H_
#define _CONSOLE_H_

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
#include <stdio.h>
#include <map>
#include "Command.h"
#include "Utils.h"

#include <vector>


class Console{
	public:
		Console(SDL_Surface* screenSurface
				, int x
				, int y
				, int consoleWidth
				, TTF_Font *font
				, int fontSize
				, SDL_Color textColor
				, Uint32 bgColor
				, std::map< std::string, Command* > commandMap
				, std::string version);
		~Console();
		void update();
		void toogleConsole();
		bool isOpen();
		void handleKeys(SDL_Event *e);

		std::string text;
		std::string version;
	private:
		std::map< std::string, Command* > commandMap;
		SDL_Surface* messageSurface;
		SDL_Surface* screenSurface;
		SDL_Rect position;
		bool isConsoleOpen = false;
		bool renderText = false;
		SDL_Rect backgroundRect;
		int fontSize;
		TTF_Font* font = NULL;
		SDL_Color textColor;
		Uint32 backgroundColor;
};

#endif