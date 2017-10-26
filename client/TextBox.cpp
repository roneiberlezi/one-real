#include "TextBox.h"

TextBox::TextBox(SDL_Surface* screenSurface
				, TTF_Font *font
				, int fontSize
				, SDL_Color textColor
				, Uint32 bgColor
				, SDL_Rect backgroundRect){
	this->font = font;
	this->fontSize = fontSize;
	this->textColor = textColor;
	this->backgroundColor = bgColor;
	this->screenSurface = screenSurface;

	this->backgroundRect = backgroundRect;

    bool  enable = false;
	position.x = backgroundRect.x;
	position.y = backgroundRect.y;
	
	SDL_StartTextInput();
    
    printf("Console initialized!");
}

bool TextBox::getEnable()
{
	return enable;
}

void TextBox::handleKeys(SDL_Event* e){
    if(this->enable == true){
        
        if (e->type == SDL_KEYDOWN)
        {
            //Handle backspace
            if (e->key.keysym.sym == SDLK_BACKSPACE && this->text.length() > 0)
            {
                //lop off character
                this->text.pop_back();
                renderText = true;
            }
            //Handle copy
            else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            {
                SDL_SetClipboardText(this->text.c_str());
            }
            //Handle paste
            else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            {
                this->text = SDL_GetClipboardText();
                renderText = true;
            }
            if (e->key.keysym.sym == 13){
                if (this->text == "" || this->text == " "){
                    renderText=true;
                    return;
                }
                
                renderText=true;
            }
        }
        //Special text input event
        else if (e->type == SDL_TEXTINPUT)
        {
            if(this->text.length() <16){
            //Not copy or pasting
            if (!((e->text.text[0] == 'c' || e->text.text[0] == 'C') && (e->text.text[0] == 'v' || e->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
            {
                //Append character
                this->text += e->text.text;
                renderText = true;
            }
            }
        }

        if (e->type == SDL_KEYDOWN){
            switch (e->key.keysym.sym){
            case SDLK_BACKQUOTE:
                renderText= true;
                break;
            }
        }
    }
}


void TextBox::update(){
	if (!renderText)
        return;
	
    if (this->text == "")
        this->text = " ";
	
    messageSurface = TTF_RenderText_Solid(font, this->text.c_str(), textColor);
	
    if (messageSurface == NULL){
		return;
	}

	backgroundRect.h = messageSurface->h;

	SDL_FillRect(screenSurface, &backgroundRect, backgroundColor);
    
	SDL_BlitSurface(messageSurface, NULL, screenSurface, &position);

	SDL_FreeSurface(messageSurface);
}

TextBox::~TextBox(){
}

void TextBox::setEnabled(bool enabled){
    this->enable = enabled;
}
void TextBox::setRender(bool render){
    this->renderText = render;
}