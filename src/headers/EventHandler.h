#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "defines.h"

class EventHandler{
    public:
        void eventType(SDL_Event* event);
        void checkEvents(SDL_Event* event);
        virtual void quitGame();
        virtual void keyPressedDown(SDLKey key);
        virtual void mouseLeftPressedDown(int x, int y);
};

#endif
