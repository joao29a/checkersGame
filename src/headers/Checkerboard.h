#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <cmath>
#include <iostream>
#include "SDL/SDL.h"
#include "Render.h"
#include "Piece.h"
#include "defines.h"

class Checkerboard{
	private:
		std::vector<Piece> gamePieces;
		std::vector<int> validPositions;
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;

	public:
		Checkerboard();
		std::vector<Piece*> boardGame;
		int whiteNumbers;
		int blackNumbers;
		static Checkerboard gameControl;
		void initPieces();
		void fillBoard();
		void setValidPositions(int id);
		bool loadImages();
		void cleanBoard();
		void updatePieces(SDL_Surface* displayVideo);
};

#endif
