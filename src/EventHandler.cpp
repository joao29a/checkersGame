#include "headers/EventHandler.h"

void EventHandler::eventType(SDL_Event* event){
    switch(event->type){
        case SDL_KEYDOWN:
            keyPressedDown(event->key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseLeftPressedDown(event->button.x,event->button.y);
            break;
        case SDL_QUIT:
            quitGame();
            break;
    }
}

void EventHandler::checkEvents(SDL_Event* event){
    while (SDL_PollEvent(event))
        eventType(event);
}

void EventHandler::quitGame(){}
void EventHandler::keyPressedDown(SDLKey key){}
void EventHandler::mouseLeftPressedDown(int x, int y){}
