#include "headers/Checkerboard.h"

Checkerboard::Checkerboard(){
	whiteImage = NULL;
	blackImage = NULL;
	boardImage = NULL;
	validImage = NULL;
}

bool Checkerboard::loadImages(){
	whiteImage = Render::assignImage(WHITE_IMAGE);
	blackImage = Render::assignImage(BLACK_IMAGE);
	boardImage = Render::assignImage(BOARD_IMAGE);
	validImage = Render::assignImage(VALID_IMAGE);

	if (whiteImage == NULL || blackImage == NULL || 
			boardImage == NULL || validImage == NULL)
		return false;

	return true;
}

void Checkerboard::initPieces(){
	clearPieces();
	for (int i = 0; i < TOTAL_PIECES; i++){
		Piece *tempPiece = new Piece;
		if (i < TOTAL_PIECES - PIECES_AMOUNT)
			tempPiece->color = BLACK;
		else
			tempPiece->color = WHITE;

		gamePieces.push_back(tempPiece);
	}
	whiteNumbers = PIECES_AMOUNT;
	blackNumbers = PIECES_AMOUNT;
}

void Checkerboard::initBoard(){
	boardGame.clear();
	boardGame.resize(BOARD_SIZE,NULL);
}

void Checkerboard::fillBoard(){
	initBoard();

	int notFillBegin = ((sqrt(BOARD_SIZE) / 2) - 1) * sqrt(BOARD_SIZE);
	int notFillEnd = (((sqrt(BOARD_SIZE) / 2) + 1) * sqrt(BOARD_SIZE));

	int fillTurn = BLACK;
	int piecesPos = 0;
	int oppositeSum = REVERSE_PIECE;

	for (int i = 0; i < BOARD_SIZE; i++){
		if (i == notFillBegin){
			fillTurn = WHITE;
			i = notFillEnd;
		}
		if (i % (int)sqrt(BOARD_SIZE) == 0)
			oppositeSum = !oppositeSum;
		if (gamePieces[piecesPos] != NULL && 
				gamePieces[piecesPos]->color == fillTurn && 
				((i + oppositeSum) % 2 == 0)){
			boardGame[i] = gamePieces[piecesPos];
			piecesPos++;
		}
	}
}

void Checkerboard::setValidPositions(int id){
	clearValidPositions();
	validPositions = boardGame[id]->positionValues(id,boardGame);
}

bool Checkerboard::hasMandatoryPositions(int player){
	clearMandatoryPositions();
	bool hasMandatory = false;
	map<int,int> tempPos;
	for (int i = 0; i < BOARD_SIZE; i++){
		if (boardGame[i] != NULL && boardGame[i]->color == player){
			tempPos = boardGame[i]->positionValues(i,boardGame);
			if (!tempPos.empty() && tempPos.begin()->second != -1){
				mandatoryPositions.push_back(i);
				hasMandatory = true;
			}
		}
	}
	return hasMandatory;
}

bool Checkerboard::isMandatory(int id){
	bool isMandatory = false;
	for (Uint32 i = 0; i < mandatoryPositions.size(); i++){
		if (mandatoryPositions[i] == id)
			isMandatory = true;
	}
	return isMandatory;
}


void Checkerboard::movePiece(int oldId, int newId){
	boardGame[newId] = boardGame[oldId];
	boardGame[oldId] = NULL;

}

void Checkerboard::removePiece(int removeId){
	if (boardGame[removeId]->color == WHITE)
		whiteNumbers--;

	else if (boardGame[removeId]->color == BLACK)
		blackNumbers--;

	boardGame[removeId] = NULL;
}

bool Checkerboard::hasMoreKill(int newId){
	setValidPositions(newId);
	map<int,int>::iterator it;
	for (it = validPositions.begin(); it != validPositions.end(); ++it){
		if (it->second != -1){
			boardGame[newId]->removeUnkilledPositions(&validPositions);
			return true;
		}
	}
	clearValidPositions();
	return false;
}

void Checkerboard::checkPromotion(int id){
	if ((id / (int)sqrt(BOARD_SIZE) == 0 && 
				boardGame[id]->color == WHITE) || 
			(id / (int)sqrt(BOARD_SIZE) == (int)sqrt(BOARD_SIZE) - 1
			 && boardGame[id]->color == BLACK)){

		delete boardGame[id];
		boardGame[id] = new KingPiece(boardGame[id]->color);
	}
}

void Checkerboard::updatePieces(SDL_Surface* displayVideo){
	int oppositeSum = REVERSE_TABLE;
	
	for (int i = 0; i < BOARD_SIZE; i++){
		int x = (i % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		int y = (i / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

		if (i % (int)sqrt(BOARD_SIZE) == 0)
			oppositeSum = !oppositeSum;

		if (boardGame[i] == NULL)
			Render::drawImage(displayVideo,boardImage,x,y,
					((i + oppositeSum) % 2) * PIECE_SIZE,0,PIECE_SIZE, 
					PIECE_SIZE);

		else if (boardGame[i]->color == BLACK)
			Render::drawImage(displayVideo, boardImage, ((i + oppositeSum) % 2)
					* PIECE_SIZE, blackImage, x, y, boardGame[i]->type * 
					PIECE_SIZE, 0, PIECE_SIZE,PIECE_SIZE);

		else if (boardGame[i]->color == WHITE)
			Render::drawImage(displayVideo, boardImage, ((i + oppositeSum) % 2)
					* PIECE_SIZE, whiteImage, x, y, boardGame[i]->type * 
					PIECE_SIZE, 0, PIECE_SIZE,PIECE_SIZE);
	}

	map<int,int>::iterator itValue;
	for (itValue = validPositions.begin(); itValue != validPositions.end();
			++itValue){
		int x = (itValue->first % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		int y = (itValue->first / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

		Render::drawImage(displayVideo,validImage,x,y,0,0,PIECE_SIZE,
				PIECE_SIZE);
	}
}

void Checkerboard::clearValidPositions(){
	validPositions.clear();
}

void Checkerboard::clearMandatoryPositions(){
	mandatoryPositions.clear();
}

void Checkerboard::clearPieces(){
	for (Uint32 i = 0; i < gamePieces.size(); i++){
		delete gamePieces[i];
	}
	gamePieces.clear();
}

void Checkerboard::clearBoard(){
	SDL_FreeSurface(whiteImage);
	SDL_FreeSurface(blackImage);
	SDL_FreeSurface(boardImage);
	SDL_FreeSurface(validImage);
	clearPieces();
	clearValidPositions();
	clearMandatoryPositions();
	boardGame.clear();
}
