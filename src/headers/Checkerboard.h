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
		std::vector<Piece*> gamePieces;
		std::vector<int> mandatoryPositions;
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;
		SDL_Surface* validImage;
		void initBoard();

	public:
		Checkerboard();
		std::vector<Piece*> boardGame;
		std::map<int,int> validPositions;
		int whiteNumbers;
		int blackNumbers;
		bool loadImages();
		void initPieces();
		void fillBoard();
		void movePiece(int oldId, int newId);
		void removePiece(int removeId);
		bool hasMoreKill(int newId);
		void checkPromotion(int id);
		void updatePieces(SDL_Surface* displayVideo);
		bool hasMandatoryPositions(int player);
		bool isMandatory(int id);
		void setValidPositions(int id);
		void clearValidPositions();
		void clearMandatoryPositions();
		void clearPieces();
		void clearBoard();
};

#endif
