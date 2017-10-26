#include "Console.h"

bool Console::isOpen(){
	return isConsoleOpen;
}

Console::Console(SDL_Surface* screenSurface
				, int x
				, int y
				, int consoleWidth
				, TTF_Font *font
				, int fontSize
				, SDL_Color textColor
				, Uint32 bgColor
				, std::map< std::string, Command* > commandMap
				, std::string version){
	this->font = font;
	this->fontSize = fontSize;
	this->textColor = textColor;
	this->backgroundColor = bgColor;
	this->screenSurface = screenSurface;
	this->commandMap = commandMap;

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = consoleWidth;

	position.x = x;
	position.y = y;

	this->version = version.append(" > ");
    
    printf("Console initialized!");
}

void Console::toogleConsole(){
	isConsoleOpen = !isConsoleOpen;
	if (isConsoleOpen){
		SDL_StartTextInput();
		text = "";
		renderText = true;
	}
	else{
		SDL_StopTextInput();
		renderText = false;
	}
}

void Console::handleKeys(SDL_Event* e){
	if (isConsoleOpen){
		if (e->type == SDL_KEYDOWN)
		{
			//Handle backspace
			if (e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
			{
				//lop off character
				text.pop_back();
				renderText = true;
			}
			//Handle copy
			else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(text.c_str());
			}
			//Handle paste
			else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				text = SDL_GetClipboardText();
				renderText = true;
			}
			else{
				if (e->key.keysym.sym >= 32 && e->key.keysym.sym <= 126){
					text += (char(e->key.keysym.sym));
					renderText = true;
				}
			}

			if (e->key.keysym.sym == 13){
				if (text == "" || text == " "){
					toogleConsole();
					return;
				}
				//*argv[] creation and parsing it to the correct command;
				std::vector<char *> args;

				std::vector<std::string> arguments = split(text, ' ');

				for (int index = 1; index < arguments.size(); index++){
					char *arg = new char[arguments[index].size() + 1];
					for (int i = 0; i < arguments[index].size(); i++){
						arg[i] = arguments[index][i];
					}
					arg[arguments[index].size()] = '\0';
					args.push_back(arg);
				}
				args.push_back(0);
				text = "";

				if (commandMap.count(arguments[0]) == 0){
					printf("\nCommand %s not found!", arguments[0].c_str());
					for (size_t i = 0; i < args.size(); i++)
						delete[] args[i];
					toogleConsole();
					return;
				}

				commandMap[arguments[0]]->execute(args.size()-1, &args[0]);

				for (size_t i = 0; i < args.size(); i++)
					delete[] args[i];
				
				toogleConsole();
			}
		}
		//Special text input event
		else if (e->type == SDL_TEXTINPUT)
		{
			//Not copy or pasting
			if (!((e->text.text[0] == 'c' || e->text.text[0] == 'C') && (e->text.text[0] == 'v' || e->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
			{
				//Append character
				text += e->text.text;
				renderText = true;
			}
		}
	}
	if (e->type == SDL_KEYDOWN){
		switch (e->key.keysym.sym){
		case SDLK_BACKQUOTE:
			toogleConsole();
			break;
		}
	}
}

void Console::update(){
	if (!renderText) return;
	if (text == "") text = " ";
	std::string textVersion = version;
	messageSurface = TTF_RenderText_Solid(font, textVersion.append(text).c_str(), textColor);
	if (messageSurface == NULL){
		return;
	}
    
	backgroundRect.h = messageSurface->h;

	SDL_FillRect(screenSurface, &backgroundRect, backgroundColor);

	SDL_BlitSurface(messageSurface, NULL, screenSurface, &position);

	SDL_FreeSurface(messageSurface);
}

Console::~Console(){
	TTF_Quit();
	SDL_StopTextInput();
}