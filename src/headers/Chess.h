#ifndef CHESS_H
#define CHESS_H

#include "defines.h"
#include "Board.h"

class Chess: public Board{
    protected:
        void renderPiece(SDL_Surface* displayVideo, SDL_Surface* board, 
                int type, int pos, int x, int y);

    public:
        Chess() : Board(){}
        ~Chess(){}
        void fillBoard();
};

#endif
