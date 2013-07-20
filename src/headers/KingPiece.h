#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "Piece.h"

class KingPiece: public Piece{
	public:
		KingPiece(int color);
			map<int,int> positionValues(int id, vector<Piece*> board);
};

#endif
