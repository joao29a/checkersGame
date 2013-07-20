#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL/SDL.h"
#include "Checkerboard.h"
#include "EventHandler.h"
#include "defines.h"

using namespace std;

class Game: public EventHandler{
	private:
		int player;
		int winner;
		bool done;
		int oldId, newId;
		SDL_Surface* displayVideo;
		void renderImages();
		Checkerboard gameControl;
	public:
		Game();
		bool initGame();
		void resetGame();
		void executeGame();
		void endGame();
		void checkEvents(SDL_Event* event);
		void checkGameSituation();
		void quitGame();
		void keyPressedDown(SDLKey key);
		void mouseLeftPressedDown(int x, int y);
};

#endif
