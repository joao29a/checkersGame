#include "headers/Board.h"

Board::Board(){
    whiteImage = NULL;
    blackImage = NULL;
    boardImage = NULL;
}

bool Board::loadImages(){
    whiteImage = Render::assignImage(WHITE_IMAGE);
    blackImage = Render::assignImage(BLACK_IMAGE);
    boardImage = Render::assignImage(BOARD_IMAGE);

    if (whiteImage == NULL || blackImage == NULL ||
            boardImage == NULL)
        return false;

    return true;
}

bool Board::hasPieces(int color){
    for (Uint32 i = 0; i < boardGame.size(); i++){
        if (boardGame[i] != NULL && boardGame[i]->color == color)
            return true;
    }
    return false;
}

void Board::movePiece(int oldId, int newId){
    boardGame[newId] = boardGame[oldId];
    boardGame[oldId] = NULL;

}

void Board::removePiece(int removeId){
    delete boardGame[removeId];
    boardGame[removeId] = NULL;
}

void Board::setValidPositions(int id){
    clearValidPositions();
    validPositions = boardGame[id]->positionValues(id,boardGame);
}

void Board::renderGame(SDL_Surface* displayVideo, int pos){
    renderBoard(displayVideo);
    renderPos(displayVideo,pos);
    renderValid(displayVideo);
}

void Board::renderBoard(SDL_Surface* displayVideo){
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

void Board::renderPos(SDL_Surface* displayVideo, int pos){
    int x = (pos % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
    int y = (pos / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

    if (pos != -1 && boardGame[pos] != NULL){
        Render::drawRect(displayVideo, x, y, PIECE_SIZE, PIECE_SIZE,
                R_POS, G_POS, B_POS);

        renderPiece(displayVideo,NULL,0,pos,x,y);
    }
}

void Board::renderValid(SDL_Surface* displayVideo){
    map<int,int>::iterator itValue;
    for (itValue = validPositions.begin(); itValue != validPositions.end();
            ++itValue){
        int x = (itValue->first % (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;
        int y = (itValue->first / (int)sqrt(BOARD_SIZE)) * PIECE_SIZE;

        Render::drawRect(displayVideo, x, y, PIECE_SIZE, PIECE_SIZE,
                R_VALID, G_VALID, B_VALID);
    }
}
void Board::clearValidPositions(){
    validPositions.clear();
}

void Board::clearBoardGame(){
    for (Uint32 i = 0; i < boardGame.size(); i++){
        if (boardGame[i] != NULL)
            delete boardGame[i];
    }
    boardGame.clear();
}

void Board::clearBoard(){
    SDL_FreeSurface(whiteImage);
    SDL_FreeSurface(blackImage);
    SDL_FreeSurface(boardImage);
    clearValidPositions();
    clearMandatoryPositions();
    clearBoardGame();
}

void Board::renderPiece(SDL_Surface* displayVideo,
        SDL_Surface* board, int type, int pos, int x, int y){}
void Board::fillBoard(){}
bool Board::hasMandatoryPositions(int player){ return false; }
bool Board::isMandatory(int id){ return false; }
void Board::checkPromotion(int id){}
bool Board::hasMoreKill(int newId){ return false; }
void Board::clearMandatoryPositions(){}
bool Board::canMove(int color) { return true; }
