#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include "SDL_net.h"

typedef char charbuf[256];

class CNet{
public:
	static bool Init(); //Initialize SDL_net
	static void Quit(); //Exit SDL_net
};