#ifndef MAINMENU_H
#define MAINMENU_H

#include "EventHandler.h"
#include "defines.h"

class MainMenu: public EventHandler{
    private:
        bool* doneGame;
        bool doneMenu;
        void defineGame(int pieces_amount, int board_size, int piece_size,
                int type);

    public:
        void executeMenu(bool* doneGame);
        void quitGame();
        void keyPressedDown(SDLKey key);
};

#endif
