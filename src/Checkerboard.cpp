#include "headers/Checkerboard.h"

Checkerboard::Checkerboard(){
	initPieces();
	initBoard();
	whiteNumbers = WHITE_TOTAL;
	blackNumbers = BLACK_TOTAL;
	whiteImage = NULL;
	blackImage = NULL;
	boardImage = NULL;
}

bool Checkerboard::loadImages(){
	whiteImage = Render::assignImage(WHITE_IMAGE);
	blackImage = Render::assignImage(BLACK_IMAGE);
	boardImage = Render::assignImage(BOARD_IMAGE);

	if (whiteImage == NULL || blackImage == NULL || 
			boardImage == NULL)
		return false;

	return true;
}

void Checkerboard::initPieces(){
	for (int i = 0; i < TOTAL_PIECES; i++){
		Piece tempPiece;
		if (i < TOTAL_PIECES - WHITE_TOTAL)
			tempPiece.color = BLACK;
		else
			tempPiece.color = WHITE;

		gamePieces.push_back(tempPiece);
	}
}

void Checkerboard::initBoard(){
	whiteNumbers = WHITE_TOTAL;
	blackNumbers = BLACK_TOTAL;
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
		if (gamePieces[piecesPos].color == fillTurn && 
				((i + oppositeSum) % 2 == 0)){
			boardGame[i] = &gamePieces[piecesPos];
			piecesPos++;
		}
	}
}

void Checkerboard::setValidPositions(int id){
	validPositions = boardGame[id]->positionValues(id,boardGame);
}

void Checkerboard::clearValidPositions(){
	validPositions.clear();
}

void Checkerboard::movePiece(int oldId, int newId, int removeId){
	boardGame[newId] = boardGame[oldId];
	boardGame[oldId] = NULL;
	if (removeId != -1){
		if (boardGame[removeId]->color == WHITE)
			whiteNumbers--;
		else
			blackNumbers--;
		boardGame[removeId] = NULL;
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
			Render::drawImage(displayVideo,blackImage,x,y,
					boardGame[i]->type * PIECE_SIZE,0,PIECE_SIZE,PIECE_SIZE);
		else
			Render::drawImage(displayVideo,whiteImage,x,y,
					boardGame[i]->type * PIECE_SIZE,0,PIECE_SIZE,PIECE_SIZE);

	}
}

void Checkerboard::cleanBoard(){
	SDL_FreeSurface(whiteImage);
	SDL_FreeSurface(blackImage);
	SDL_FreeSurface(boardImage);
	boardGame.clear();
	gamePieces.clear();
	clearValidPositions();
}
