#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include "Board.h"
#include "KingPiece.h"
#include "defines.h"

class Checkerboard: public Board{
    protected:
        vector<int> mandatoryPositions;

        void renderMandatory(SDL_Surface* displayVideo);
        void renderPiece(SDL_Surface* displayVideo, SDL_Surface* board,
                int type, int pos, int x, int y);
    public:
        Checkerboard() : Board(){}
        ~Checkerboard(){}
        void fillBoard();
        bool canMove(int color);
        bool hasMandatoryPositions(int player);
        bool isMandatory(int id);
        bool hasMoreKill(int newId);
        void checkPromotion(int id);
        void renderGame(SDL_Surface* displayVideo, int pos);
        void clearMandatoryPositions();
};

#endif
