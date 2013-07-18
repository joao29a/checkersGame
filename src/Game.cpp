#include "headers/Game.h"

Game::Game(){
	displayVideo = NULL;
	done = false;
	player = WHITE;
}

bool Game::initGame(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	displayVideo = SDL_SetVideoMode(WIDTH_RESOLUTION, HEIGHT_RESOLUTION,
			32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (displayVideo == NULL)
		return false;

	if (!Checkerboard::gameControl.loadImages())
		return false;

	return true;
}

void Game::executeGame(){
	if (!initGame())
		return;

	SDL_Event event;
	
	while(!done){
		checkEvents(&event);
		renderImages();
	}

	cleanGame();

}

void Game::checkEvents(SDL_Event* event){
	while (SDL_PollEvent(event))
		eventType(event);
}

void Game::quitGame(){
	done = true;
}

void Game::keyPressedDown(SDLKey key){
	switch(key){
		case SDLK_r:
			Checkerboard::gameControl.initPieces();
			Checkerboard::gameControl.fillBoard();
			break;
		case SDLK_ESCAPE:
			quitGame();
			break;
	}
}

void Game::renderImages(){
	Checkerboard::gameControl.renderImages(displayVideo);
	SDL_Flip(displayVideo);
}

void Game::cleanGame(){
	SDL_FreeSurface(displayVideo);
	Checkerboard::gameControl.cleanBoard();
	SDL_Quit;
}

