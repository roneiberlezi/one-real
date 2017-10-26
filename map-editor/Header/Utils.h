#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <vector>


//Create a single 32 bit value containing the red, green, blue and alpha components
Uint32 color32(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 alpha);

//Draw an empty rect in the screen
void drawUnfilledRect(SDL_Surface* dst, SDL_Rect* rect, int line_thickness, Uint32 color);

//Draw text to the screen
bool draw_text(int x, int y, SDL_Surface* dst, SDL_Surface *messageSurface, TTF_Font *font, const char *text, SDL_Color textColor);

//Draw text to the screen, with a specified background color
bool draw_debug_text(int x, int y, SDL_Surface* dst, SDL_Surface *messageSurface, TTF_Font *font,const char *text, SDL_Color textColor, Uint32 bgColor);

//Draw the surface to the specified position
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);


std::vector<std::string> split(const std::string &s, char delim);