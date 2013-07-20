#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "defines.h"

using namespace std;

class Piece{
	protected:
		void markPosition(int diagId, int diagonal, vector<int>* values, 
				vector<Piece*> board);

		void incrementDiagonal(int diagId, int id, int diagonal,
				vector<int>* values, vector<Piece*> board);

		void decrementDiagonal(int diagId, int id, int diagonal,
				vector<int>* values, vector<Piece*> board);
	public:
		Piece();
		int color;
		virtual std::vector<int> positionValues(int id, 
						std::vector<Piece*> board);
		
};

#endif
