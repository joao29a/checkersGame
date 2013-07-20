#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include "SDL/SDL.h"
#include "Render.h"
#include "Piece.h"
#include "defines.h"

class Checkerboard{
	private:
		std::vector<Piece> gamePieces;
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;
		

	public:
		Checkerboard();
		std::vector<Piece*> boardGame;
		std::map<int,int> validPositions;
		int whiteNumbers;
		int blackNumbers;
		void initPieces();
		void initBoard();
		void fillBoard();
		void setValidPositions(int id);
		void clearValidPositions();
		bool loadImages();
		void cleanBoard();
		void updatePieces(SDL_Surface* displayVideo);
		void movePiece(int oldId, int newId, int removeId);
};

#endif
