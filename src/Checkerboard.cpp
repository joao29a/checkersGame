#include "headers/Checkerboard.h"

Checkerboard Checkerboard::gameControl;

Checkerboard::Checkerboard(){
	whiteNumbers = WHITE_TOTAL;
	blackNumbers = BLACK_TOTAL;
	winnerGame = NONE_WINNER;
	whiteImage = NULL;
	blackImage = NULL;
	boardImage = NULL;
	boardGame.resize(BOARD_SIZE,NULL);
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

bool Checkerboard::fillBoard(){

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
		if (gamePieces[piecesPos].color == fillTurn && ((i + oppositeSum) % 2 == 0)){
			boardGame[i] = &gamePieces[piecesPos];
			piecesPos++;
		}
	}
}

SDL_Surface* Checkerboard::assignImage(const char* file){
	SDL_Surface* newImage;
	SDL_Surface* tempImage = IMG_Load(file);

	if (tempImage == NULL) 
		return NULL;

	newImage = SDL_DisplayFormatAlpha(tempImage);

	return newImage;
}

bool Checkerboard::loadImages(){
	whiteImage = assignImage(WHITE_IMAGE);
	blackImage = assignImage(BLACK_IMAGE);
	boardImage = assignImage(BOARD_IMAGE);

	if (whiteImage == NULL || blackImage == NULL || 
			boardImage == NULL)
		return false;

	return true;
}

void Checkerboard::renderImages(SDL_Surface* displayVideo){
	int oppositeSum = REVERSE_TABLE;
	for (int i = 0; i < boardGame.size(); i++){
		int x = (i % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		int y = (i / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
		
		if (i % (int)sqrt(BOARD_SIZE) == 0)
			oppositeSum = !oppositeSum;
		
		if (boardGame[i] == NULL)
			drawImage(displayVideo,boardImage,x,y,
					((i + oppositeSum) % 2) * PIECE_SIZE,0,
					PIECE_SIZE, PIECE_SIZE);
		else if (boardGame[i]->color == BLACK)
			drawImage(displayVideo,blackImage,x,y,0,0,PIECE_SIZE,
					PIECE_SIZE);
		else
			drawImage(displayVideo,whiteImage,x,y,0,0,PIECE_SIZE,
				PIECE_SIZE);

	}
}

void Checkerboard::drawImage(SDL_Surface* dest, SDL_Surface* src, int x,
		int y, int x2, int y2, int w, int h){
	SDL_Rect destRec;

	destRec.x = x;
	destRec.y = y;

	SDL_Rect srcRec;

	srcRec.x = x2;
	srcRec.y = y2;
	srcRec.w = w;
	srcRec.h = h;

	SDL_BlitSurface(src,&srcRec,dest,&destRec);
}

void Checkerboard::cleanBoard(){
	SDL_FreeSurface(whiteImage);
	SDL_FreeSurface(blackImage);
	SDL_FreeSurface(boardImage);
	boardGame.clear();
	gamePieces.clear();
}
