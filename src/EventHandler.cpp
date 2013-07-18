#include "headers/EventHandler.h"

void EventHandler::eventType(SDL_Event* event){
	switch(event->type){
		case SDL_KEYDOWN:
			keyPressedDown(event->key.keysym.sym);
			break;
		case SDL_QUIT:
			quitGame();
			break;
	}
}

void EventHandler::quitGame(){}
void EventHandler::keyPressedDown(SDLKey key){}
