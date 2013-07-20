#include "headers/KingPiece.h"

KingPiece::KingPiece(int color){
	this->color = color;
}

std::vector<int> KingPiece::positionValues(int id, std::vector<Piece*> board){
	std::vector<int> values;
	int diagonal = (int)sqrt(BOARD_SIZE) - 1;
	int diagId;

	for (int i = 0; i < 2; i++){

		if (id % (int)sqrt(BOARD_SIZE) == 0){
			decrementDiagonal(diagId,id,diagonal,&values,board);
			diagonal += 2;
			incrementDiagonal(diagId,id,diagonal,&values,board);
			return values;
		}

		else if (id % (int)sqrt(BOARD_SIZE) == (int)sqrt(BOARD_SIZE) - 1){
			incrementDiagonal(diagId,id,diagonal,&values,board);
			diagonal += 2;
			decrementDiagonal(diagId,id,diagonal,&values,board);
			return values;
		}
		else{
			decrementDiagonal(diagId,id,diagonal,&values,board);
			incrementDiagonal(diagId,id,diagonal,&values,board);
			diagonal += 2;
		}
	}
	return values;
}
