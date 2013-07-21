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

	if (!gameControl.loadImages())
		return false;

	return true;
}

void Game::resetGame(){
	oldId = newId = -1;
	player = WHITE;
	winner = NONE;
	gameControl.fillBoard();
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

	if (gameControl.boardGame[id] != NULL && 
			gameControl.boardGame[id]->color == player){
		oldId = id;
		newId = -1;
		gameControl.clearValidPositions();
		gameControl.setValidPositions(id);
	}
	else
		newId = id;
}

void Game::checkGameSituation(){
	if (oldId != newId){
		map<int,int>::iterator itValues;
		for (itValues = gameControl.validPositions.begin(); 
				itValues != gameControl.validPositions.end(); ++itValues){
			if (itValues->first == newId){
				gameControl.movePiece(oldId,newId,itValues->second);
				gameControl.checkPromotion(newId);
				if (player == WHITE)
					player = BLACK;
				else
					player = WHITE;
				gameControl.clearValidPositions();
				oldId = newId = -1;
			}
		}
	}

	if (gameControl.whiteNumbers == 0)
		winner = BLACK;
	else if (gameControl.blackNumbers == 0)
		winner = WHITE;

	if (winner != NONE)
		quitGame();
}

void Game::renderImages(){
	gameControl.updatePieces(displayVideo);
	SDL_Flip(displayVideo);
}

void Game::endGame(){
	SDL_FreeSurface(displayVideo);
	gameControl.cleanBoard();
	SDL_Quit();
}
