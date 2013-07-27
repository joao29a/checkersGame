#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include "SDL/SDL.h"
#include "Render.h"
#include "Piece.h"
#include "KingPiece.h"
#include "defines.h"

class Checkerboard{
	private:
		std::vector<int> mandatoryPositions;
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;
		void renderBoard(SDL_Surface* displayVideo);
		void renderPiece(SDL_Surface* displayVideo, SDL_Surface* board, 
				int type, int pos, int x, int y);
		void renderPos(SDL_Surface* displayVideo, int pos);
		void renderMandatory(SDL_Surface* displayVideo);
		void renderValid(SDL_Surface* displayVideo);

	public:
		Checkerboard();
		std::vector<Piece*> boardGame;
		std::map<int,int> validPositions;
		bool loadImages();
		void fillBoard();
		bool hasPieces(int color);
		bool canMove(int color);
		void movePiece(int oldId, int newId);
		void removePiece(int removeId);
		bool hasMoreKill(int newId);
		void checkPromotion(int id);
		void renderGame(SDL_Surface* displayVideo, int pos);
		bool hasMandatoryPositions(int player);
		bool isMandatory(int id);
		void setValidPositions(int id);
		void clearValidPositions();
		void clearMandatoryPositions();
		void clearBoardGame();
		void clearBoard();
};

#endif
