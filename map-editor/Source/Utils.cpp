#include "Utils.h"

Uint32 color32(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 alpha)
{
	return (Uint32(alpha) << 24) + (Uint32(r) << 16) + (Uint32(g) << 8) + Uint32(b);
}

void drawUnfilledRect(SDL_Surface* dst, SDL_Rect* rect, int line_thickness, Uint32 color){
	SDL_Rect line;
	//top line
	line.x = rect->x;
	line.y = rect->y;
	line.w = rect->w;
	line.h = line_thickness;
	SDL_FillRect(dst, &line, color);

	//left line
	line.x = rect->x;
	line.y = rect->y;
	line.w = line_thickness;
	line.h = rect->h;
	SDL_FillRect(dst, &line, color);

	//bottom line
	line.x = rect->x;
	line.y = rect->y + rect->h;
	line.w = rect->w;
	line.h = line_thickness;
	SDL_FillRect(dst, &line, color);

	//right line
	line.x = rect->x + rect->w - line_thickness;
	line.y = rect->y;
	line.w = line_thickness;
	line.h = rect->h;
	SDL_FillRect(dst, &line, color);
}

bool draw_text(int x, int y, SDL_Surface* dst, SDL_Surface *messageSurface, TTF_Font *font, const char *text, SDL_Color textColor){
	messageSurface = TTF_RenderText_Solid(font, text, textColor);
	if (messageSurface == NULL){
		return false;
	}
	apply_surface(x, y, messageSurface, dst);
	return true;
}

bool draw_debug_text(int x, int y, SDL_Surface* dst, SDL_Surface *messageSurface, TTF_Font *font,const char *text, SDL_Color textColor, Uint32 bgColor){
	messageSurface = TTF_RenderText_Solid(font, text, textColor);
	if (messageSurface == NULL){
		return false;
	}
	
	SDL_Rect bg;
	bg.x = x;
	bg.y = y;
	bg.w = messageSurface->w;
	bg.h = messageSurface->h;

	SDL_FillRect(dst, &bg, bgColor);

	apply_surface(x, y, messageSurface, dst);
	SDL_FreeSurface(messageSurface);
	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface(source, NULL, destination, &offset);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}