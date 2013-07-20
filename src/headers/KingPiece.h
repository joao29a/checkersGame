#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "Piece.h"

class KingPiece: public Piece{
	public:
		KingPiece(int color);
		std::vector<int> positionValues(int id, std::vector<Piece*> board);
};

#endif
