#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include <cmath>
#include "Object.h"
#include "Render.h"
#include "defines.h"

class Board{
    protected:
        SDL_Surface* whiteImage;
        SDL_Surface* blackImage;
        SDL_Surface* boardImage;
        void renderBoard(SDL_Surface* displayVideo);
        void renderPos(SDL_Surface* displayVideo, int pos);
        void renderValid(SDL_Surface* displayVideo);

        virtual void renderPiece(SDL_Surface* displayVideo,
                SDL_Surface* board, int type, int pos, int x, int y);

    public:
        Board();
        virtual ~Board(){}
        vector<Object*> boardGame;
        map<int,int> validPositions;
        bool loadImages();
        bool hasPieces(int color);
        void movePiece(int oldId, int newId);	 		
        void removePiece(int removeId);
        void setValidPositions(int id);
        void clearValidPositions();
        void clearBoardGame();
        void clearBoard();

        virtual void renderGame(SDL_Surface* displayVideo, int pos);
        virtual void fillBoard();
        virtual bool hasMandatoryPositions(int player);
        virtual bool isMandatory(int id);
        virtual void checkPromotion(int id);
        virtual bool hasMoreKill(int newId);
        virtual void clearMandatoryPositions();
        virtual bool canMove(int color);
};

#endif
