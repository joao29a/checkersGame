#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "defines.h"

class Piece{
	protected:
		void markPosition(int diagId, int diagonal, map<int,int>* values, 
				vector<Piece*> board);
		
		virtual void selectTarget(int diagId, int diagonal, map<int,int>* values,
						vector<Piece*> board);

		void incrementDiagonal(int diagId, int id, int diagonal,
				map<int,int>* values, vector<Piece*> board);

		void decrementDiagonal(int diagId, int id, int diagonal,
				map<int,int>* values, vector<Piece*> board);

		void removeUnkilledPositions(map<int,int>* values);
		
		int canKill; //variable to check if this Piece will kill other piece

	public:
		Piece();
		virtual ~Piece(){}
		int color;
		int type;
		virtual map<int,int> positionValues(int id, 
						std::vector<Piece*> board);
		
};

#endif
