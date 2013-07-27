#include "headers/MainMenu.h"

int PIECES_AMOUNT;
int TOTAL_PIECES;
int BOARD_SIZE;
int PIECE_SIZE;
bool MANDATORY_KILL = false;
const char* WHITE_IMAGE;
const char* BLACK_IMAGE;
const char* BOARD_IMAGE;

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
			defineGame(12,64,75,8); //8x8 game
			break;
		case SDLK_2:
			defineGame(20,100,60,10); //10x10 game
			break;
		case SDLK_3:
			defineGame(30,144,50,12); //12x12 game
			break;
		case SDLK_4:
			MANDATORY_KILL = !MANDATORY_KILL;
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

void MainMenu::defineGame(int pieces_amount, int board_size, int piece_size,
		int type){
	PIECES_AMOUNT = pieces_amount;
	TOTAL_PIECES = PIECES_AMOUNT + PIECES_AMOUNT;
	BOARD_SIZE = board_size;
	PIECE_SIZE = piece_size;

	if (type == 8){
			WHITE_IMAGE = "images/white8.png";
			BLACK_IMAGE = "images/black8.png";
			BOARD_IMAGE = "images/board8.png";
	}
	else if (type == 10){
			WHITE_IMAGE = "images/white10.png";
			BLACK_IMAGE = "images/black10.png";
			BOARD_IMAGE = "images/board10.png";
	}
	else if (type == 12){
			WHITE_IMAGE = "images/white12.png";
			BLACK_IMAGE = "images/black12.png";
			BOARD_IMAGE = "images/board12.png";
	}
	
	doneMenu = true;
}
