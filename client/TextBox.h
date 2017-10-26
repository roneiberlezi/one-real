#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

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
#include <vector>


class TextBox{
	public:
		TextBox(SDL_Surface* screenSurface
				, TTF_Font *font
				, int fontSize
				, SDL_Color textColor
				, Uint32 bgColor
				, SDL_Rect backgroundRect);
		~TextBox();
		void update();
		void handleKeys(SDL_Event *e);
		std::string text;
        void setEnabled(bool enabled);
        void setRender(bool render);
		bool getEnable();
    
	private:
		SDL_Surface* messageSurface;
		SDL_Surface* screenSurface;
		SDL_Rect position;
		bool renderText = false;
		SDL_Rect backgroundRect;
		int fontSize;
		TTF_Font* font = NULL;
		SDL_Color textColor;
		Uint32 backgroundColor;
        bool enable = false;
};

#endif