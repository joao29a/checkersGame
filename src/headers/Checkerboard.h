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
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;
		SDL_Surface* validImage;
		

	public:
		Checkerboard();
		std::vector<Piece*> boardGame;
		std::map<int,int> validPositions;
		int whiteNumbers;
		int blackNumbers;
		bool loadImages();
		void initPieces();
		void initBoard();
		void fillBoard();
		void movePiece(int oldId, int newId);
		void removePiece(int removeId);
		void checkPromotion(int id);
		void updatePieces(SDL_Surface* displayVideo);
		void setValidPositions(int id);
		void clearValidPositions();
		void clearPieces();
		void clearBoard();
};

#endif
