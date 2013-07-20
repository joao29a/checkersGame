#include "headers/Game.h"

Game::Game(){
	displayVideo = NULL;
	done = false;
	oldId = newId = -1;
	player = WHITE;
	winner = NONE;
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

void Game::resetGame(){
	oldId = newId = -1;
	player = WHITE;
	winner = NONE;
	Checkerboard::gameControl.fillBoard();
}

void Game::executeGame(){
	if (!initGame())
		return;

	SDL_Event event;

	while(!done){
		checkEvents(&event);
		checkGameSituation();
		renderImages();
	}

	endGame();

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
			resetGame();
			break;
		case SDLK_ESCAPE:
			quitGame();
			break;
	}
}

void Game::mouseLeftPressedDown(int x, int y){
	int id = x / PIECE_SIZE;
	id += (y / PIECE_SIZE) * (int)sqrt(BOARD_SIZE);

	if (id < 0 || id >= BOARD_SIZE) return;

	if (Checkerboard::gameControl.boardGame[id] != NULL && 
			Checkerboard::gameControl.boardGame[id]->color == player){
		oldId = id;
		newId = -1;
		Checkerboard::gameControl.clearValidPositions();
		Checkerboard::gameControl.setValidPositions(id);
	}
	else
		newId = id;
}

void Game::checkGameSituation(){
	if (oldId != newId){
		for (int i = 0; i < Checkerboard::gameControl.validPositions.size();
				i++){
			if (Checkerboard::gameControl.validPositions[i] == newId){
				Checkerboard::gameControl.movePiece(oldId,newId);
				if (player == WHITE)
					player = BLACK;
				else
					player = WHITE;
				Checkerboard::gameControl.clearValidPositions();
				oldId = newId = -1;
			}
		}
	}
}

void Game::renderImages(){
	Checkerboard::gameControl.updatePieces(displayVideo);
	SDL_Flip(displayVideo);
}

void Game::endGame(){
	SDL_FreeSurface(displayVideo);
	Checkerboard::gameControl.cleanBoard();
	SDL_Quit();
}
