#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SDL/SDL.h"

class EventHandler{
	public:
		void eventType(SDL_Event* event);
		virtual void quitGame();
		virtual void keyPressedDown(SDLKey key);
};

#endif
