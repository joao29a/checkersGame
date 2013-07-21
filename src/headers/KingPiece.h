#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "Piece.h"

class KingPiece: public Piece{
	protected:
		void selectTarget(int diagId, int diagonal, map<int,int>* values,
				vector<Piece*> board);
	public:
		KingPiece(int color);
			map<int,int> positionValues(int id, vector<Piece*> board);
};

#endif
