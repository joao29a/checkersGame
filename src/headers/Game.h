#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL/SDL.h"
#include "Checkerboard.h"
#include "EventHandler.h"
#include "defines.h"

class Game: public EventHandler{
	private:
		int player;
		bool done;
		SDL_Surface* displayVideo;
		void renderImages();
	public:
		Game();
		bool initGame();
		void executeGame();
		void cleanGame();
		void checkEvents(SDL_Event* event);
		void quitGame();
		void keyPressedDown(SDLKey key);
};

#endif
