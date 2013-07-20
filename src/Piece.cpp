#include "headers/Piece.h"

Piece::Piece(){
	color = NONE;
	type = NONE;
	canKill = false;
}

map<int,int> Piece::positionValues(int id, vector<Piece*> board){
	map<int,int> values;
	int diagonal = (int)sqrt(BOARD_SIZE) - 1;
	int diagId = 0;

	for (int i = 0; i < 2; i++){
		if (id % (int)sqrt(BOARD_SIZE) == (int)sqrt(BOARD_SIZE) - 1){

			if (this->color == BLACK)
				incrementDiagonal(diagId,id,diagonal,&values,board);
			diagonal += 2;
			if (this->color == WHITE)
				decrementDiagonal(diagId,id,diagonal,&values,board);
			break;
		}
		if (id % (int)sqrt(BOARD_SIZE) == 0){
		
			if (this->color == WHITE)
				decrementDiagonal(diagId,id,diagonal,&values,board);
			diagonal += 2;
			if (this->color == BLACK)
				incrementDiagonal(diagId,id,diagonal,&values,board);
			break;
		}

		else{
			if (this->color == WHITE)
				decrementDiagonal(diagId,id,diagonal,&values,board);
			else 
				incrementDiagonal(diagId,id,diagonal,&values,board);
		}
		diagonal += 2;
	}
	removeUnkilledPositions(&values);
	return values;
}

void Piece::markPosition(int diagId, int diagonal, map<int,int>* values, 
		vector<Piece*> board){
	if (board[diagId] != NULL) {
		
		if (diagId % (int)sqrt(BOARD_SIZE) == 0 ||
				diagId % (int)sqrt(BOARD_SIZE) == (int)sqrt(BOARD_SIZE) - 1)
			return;

		if (this->color == WHITE && board[diagId]->color == BLACK &&
				board[diagId -= diagonal] == NULL){
			values->insert(pair<int,int>(diagId,diagId + diagonal));
			canKill = true;
		}
		else if (this->color == BLACK && board[diagId]->color == WHITE && 
				board[diagId += diagonal] == NULL){
			values->insert(pair<int,int>(diagId,diagId - diagonal));
			canKill = true;
		}

	}
	else
		values->insert(pair<int,int>(diagId,-1));
}

void Piece::decrementDiagonal(int diagId, int id, int diagonal,
		map<int,int>* values, vector<Piece*> board){
	diagId = id - diagonal;
	markPosition(diagId,diagonal,values,board);

}

void Piece::incrementDiagonal(int diagId, int id, int diagonal,
		map<int,int>* values, vector<Piece*> board){
	diagId = id + diagonal;
	markPosition(diagId,diagonal,values,board);
}

void Piece::removeUnkilledPositions(map<int,int>* values){
	if (!canKill) return;

	map<int,int>::iterator itValues;
	for (itValues = values->begin(); itValues != values->end(); ++itValues){
		if (itValues->second == -1)
			values->erase(itValues);
	}
	canKill = false;
}
