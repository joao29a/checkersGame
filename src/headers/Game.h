#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "SDL/SDL.h"
#include "Checkerboard.h"
#include "EventHandler.h"
#include "MainMenu.h"
#include "defines.h"

using namespace std;

class Game: public EventHandler{
	private:
		int player;
		bool sameTurn;
		int winner;
		bool done;
		int oldId, newId;
		SDL_Surface* displayVideo;
		void renderImages();
		Checkerboard gameControl;
		MainMenu gameMenu;
	
	public:
		Game();
		bool initGame();
		void resetGame();
		void executeGame();
		void endGame();
		void checkGameSituation();
		void quitGame();
		void keyPressedDown(SDLKey key);
		void mouseLeftPressedDown(int x, int y);
};

#endif
