#include "headers/MainMenu.h"


void MainMenu::executeMenu(bool* doneGame){
	this->doneGame = NULL;
	doneMenu = false;
	
	this->doneGame = doneGame;

	SDL_Event event;
	
	while (!doneMenu){
		checkEvents(&event);
	}
}

void MainMenu::keyPressedDown(SDLKey key){
	switch(key){
		case SDLK_1:
			doneMenu = true;
			break;
		case SDLK_ESCAPE:
			quitGame();
			break;
		default:
			break;
	}
}

void MainMenu::quitGame(){
	*doneGame = true;
	doneMenu = true;
}
