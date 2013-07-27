#include "headers/Checkerboard.h"

Checkerboard::Checkerboard(){
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

void Checkerboard::fillBoard(){
	clearBoardGame();

	int notFillBegin = ((sqrt(BOARD_SIZE) / 2) - 1) * sqrt(BOARD_SIZE);
	int notFillEnd = (((sqrt(BOARD_SIZE) / 2) + 1) * sqrt(BOARD_SIZE)) - 1;

	int oppositeSum = REVERSE_PIECE;
	int blackPieces = 0;
	int whitePieces = 0;

	for (int i = 0; i < BOARD_SIZE; i++){
		Piece *tempPiece = NULL;

		int modValue = i % (int)sqrt(BOARD_SIZE);

		if (modValue == 0)
			oppositeSum = !oppositeSum;

		int modOpposite = (i + oppositeSum) % 2;

		if (i < notFillBegin && modOpposite == 0 && 
				blackPieces <= PIECES_AMOUNT){
			tempPiece = new Piece(BLACK);
			blackPieces++;
		}
		else if (i > notFillEnd && modOpposite == 0 && 
				whitePieces <= PIECES_AMOUNT){
			tempPiece = new Piece(WHITE);
			whitePieces++;
		}

		boardGame.push_back(tempPiece);
	}
}

bool Checkerboard::hasPieces(int color){
	for (Uint32 i = 0; i < boardGame.size(); i++){
		if (boardGame[i] != NULL && boardGame[i]->color == color)
			return true;
	}
	return false;
}

bool Checkerboard::canMove(int color){
	for (Uint32 i = 0; i < boardGame.size(); i++){
		map<int,int> tempPositions;
		if (boardGame[i] != NULL && boardGame[i]->color == color){
			tempPositions = boardGame[i]->positionValues(i,boardGame);
			if (!tempPositions.empty())
				return true;
		}
	}
	return false;
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
	delete boardGame[removeId];
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

void Checkerboard::renderGame(SDL_Surface* displayVideo, int pos){
	renderBoard(displayVideo);
	renderPos(displayVideo,pos);
	if (MANDATORY_KILL)
		renderMandatory(displayVideo);
	renderValid(displayVideo);
}

//draw the board game
void Checkerboard::renderBoard(SDL_Surface* displayVideo){
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

		else
			renderPiece(displayVideo,boardImage,
					((i + oppositeSum) % 2) * PIECE_SIZE,i,x,y);
	}

}

//draw the select position
void Checkerboard::renderPos(SDL_Surface* displayVideo, int pos){
	int x = (pos % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
	int y = (pos / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

	if (pos != -1 && boardGame[pos] != NULL){
		Render::drawRect(displayVideo, x, y, PIECE_SIZE, PIECE_SIZE,
				R_POS, G_POS, B_POS);

		renderPiece(displayVideo,NULL,0,pos,x,y);
	}

}

//draw mandatory positions
void Checkerboard::renderMandatory(SDL_Surface* displayVideo){
	for (Uint32 i = 0; i < mandatoryPositions.size(); i++){
		int x = (mandatoryPositions[i] % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		int y = (mandatoryPositions[i] / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

		Render::drawRect(displayVideo, x, y, PIECE_SIZE, PIECE_SIZE,
				R_POS, G_POS, B_POS);

		renderPiece(displayVideo,NULL,0,mandatoryPositions[i],x,y);
	}
}

//draw valid positions
void Checkerboard::renderValid(SDL_Surface* displayVideo){
	map<int,int>::iterator itValue;
	for (itValue = validPositions.begin(); itValue != validPositions.end();
			++itValue){
		int x = (itValue->first % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		int y = (itValue->first / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

		Render::drawRect(displayVideo, x, y, PIECE_SIZE, PIECE_SIZE,
				R_VALID, G_VALID, B_VALID);
	}
}

void Checkerboard::renderPiece(SDL_Surface* displayVideo, SDL_Surface* board,
		int type, int pos, int x, int y){
	if (boardGame[pos]->color == BLACK)
		Render::drawImage(displayVideo, board, type, blackImage, x, y, 
				boardGame[pos]->type * PIECE_SIZE, 0, 
				PIECE_SIZE,PIECE_SIZE);

	else if (boardGame[pos]->color == WHITE)
		Render::drawImage(displayVideo, board, type, whiteImage, x, y, 
				boardGame[pos]->type * PIECE_SIZE, 0, 
				PIECE_SIZE,PIECE_SIZE);
}

void Checkerboard::clearValidPositions(){
	validPositions.clear();
}

void Checkerboard::clearMandatoryPositions(){
	mandatoryPositions.clear();
}

void Checkerboard::clearBoardGame(){
	for (Uint32 i = 0; i < boardGame.size(); i++){
		if (boardGame[i] != NULL)
			delete boardGame[i];
	}
	boardGame.clear();
}

void Checkerboard::clearBoard(){
	SDL_FreeSurface(whiteImage);
	SDL_FreeSurface(blackImage);
	SDL_FreeSurface(boardImage);
	clearValidPositions();
	clearMandatoryPositions();
	clearBoardGame();
}
