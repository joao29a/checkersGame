#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <cmath>
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Piece.h"
#include "defines.h"

class Checkerboard{
	private:
		std::vector<Piece> gamePieces;
		std::vector<Piece*> boardGame;
		SDL_Surface* whiteImage;
		SDL_Surface* blackImage;
		SDL_Surface* boardImage;
		SDL_Surface* assignImage(const char* file);
		void drawImage(SDL_Surface* dest, SDL_Surface* src,
				int x, int y, int x2, int y2, int w, int h);

	public:
		Checkerboard();
		int whiteNumbers;
		int blackNumbers;
		int winnerGame;
		static Checkerboard gameControl;
		void initPieces();
		bool fillBoard();
		bool loadImages();
		void cleanBoard();
		void renderImages(SDL_Surface* displayVideo);
};

#endif
