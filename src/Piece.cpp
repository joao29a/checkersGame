#include "headers/Piece.h"

Piece::Piece(){
	color = NONE;
}

vector<int> Piece::positionValues(int id, vector<Piece*> board){
	vector<int> values;
	int diagonal = (int)sqrt(BOARD_SIZE) - 1;
	int diagId = 0;

	for (int i = 0; i < 2; i++){
		if (id % (int)sqrt(BOARD_SIZE) == (int)sqrt(BOARD_SIZE) - 1){
			diagonal += 2;
			continue;
		}

		if (this->color == WHITE)
			decrementDiagonal(diagId,id,diagonal,&values,board);
		else
			incrementDiagonal(diagId,id,diagonal,&values,board);

		if (id % (int)sqrt(BOARD_SIZE) == 0)
			return values;

		diagonal += 2;
	}

	return values;
}

void Piece::markPosition(int diagId, int diagonal, vector<int>* values, 
					vector<Piece*> board){
	if (board[diagId] != NULL){
		if (this->color == WHITE && board[diagId]->color == BLACK && 
				board[diagId -= diagonal] == NULL){
			values->push_back(diagId);
		}
		else if (this->color == BLACK && board[diagId]->color == WHITE && 
				board[diagId += diagonal] == NULL){
			values->push_back(diagId);
		}
	}
	else
		values->push_back(diagId);
}

void Piece::decrementDiagonal(int diagId, int id, int diagonal,
				vector<int>* values, vector<Piece*> board){
		diagId = id - diagonal;
		markPosition(diagId,diagonal,values,board);

}

void Piece::incrementDiagonal(int diagId, int id, int diagonal,
				vector<int>* values, vector<Piece*> board){
		diagId = id + diagonal;
		markPosition(diagId,diagonal,values,board);

}
