#ifndef MAINMENU_H
#define MAINMENU_H

#include "EventHandler.h"

class MainMenu: public EventHandler{
	protected:
		bool* doneGame;
		bool doneMenu;

	public:
		void executeMenu(bool* doneGame);
		void quitGame();
		void keyPressedDown(SDLKey key);
};

#endif
