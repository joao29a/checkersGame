#include "headers/Game.h"

Game::Game(){
    displayVideo = NULL;
    gameControl = new Checkerboard();
    done = false;
    sameTurn = false;
}

bool Game::initGame(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if (TTF_Init() < 0)
        return false;

    displayVideo = SDL_SetVideoMode(WIDTH_RESOLUTION, HEIGHT_RESOLUTION,
            32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (displayVideo == NULL)
        return false;

    return true;
}

void Game::resetGame(){
    oldId = newId = -1;
    sameTurn = false;
    player = WHITE;
    winner = NONE;
    gameControl->clearValidPositions();
    if (MANDATORY_KILL)
        gameControl->clearMandatoryPositions();
    gameControl->fillBoard();
}

void Game::executeGame(){
    if (!initGame())
        return;

    if (!startGame())
        quitGame();

    SDL_Event event;

    while(!done){
        checkEvents(&event);
        if (done) break;
        checkGameSituation();
        renderGame();
    }

    endGame();

}

bool Game::startGame(){
    SDL_FillRect(displayVideo, NULL, 
            SDL_MapRGB(displayVideo->format, 0, 0, 0));
    SDL_Flip(displayVideo);

    gameMenu.executeMenu(&done);
    gameControl->clearBoard();
    if (!gameControl->loadImages())
        return false;
    if (!done)
        resetGame();
    return true;
}

void Game::quitGame(){
    done = true;
}

void Game::keyPressedDown(SDLKey key){
    switch(key){
        case SDLK_r:
            resetGame();
            break;
        case SDLK_e:
            if (!startGame())
                quitGame();
            break;
        case SDLK_ESCAPE:
            quitGame();
            break;
        default:
            break;
    }
}

void Game::mouseLeftPressedDown(int x, int y){
    int id = x / PIECE_SIZE;
    id += (y / PIECE_SIZE) * (int)sqrt(BOARD_SIZE);

    if (id < 0 || id >= BOARD_SIZE) return;

    if (MANDATORY_KILL == true && !sameTurn &&
            gameControl->boardGame[id] != NULL 
            && gameControl->hasMandatoryPositions(player)){
        if (!gameControl->isMandatory(id)){
            return;
        }
    }

    if (!sameTurn && gameControl->boardGame[id] != NULL && 
            gameControl->boardGame[id]->color == player){
        oldId = id;
        newId = -1;
        gameControl->clearValidPositions();
        gameControl->setValidPositions(id);
    }
    else if (gameControl->boardGame[id] == NULL){
        newId = id;
    }
}

void Game::checkGameSituation(){
    if (oldId != newId){
        map<int,int>::iterator itValues;
        for (itValues = gameControl->validPositions.begin(); 
                itValues != gameControl->validPositions.end(); ++itValues){
            if (itValues->first == newId){
                gameControl->movePiece(oldId,newId);
                gameControl->checkPromotion(newId);

                if (itValues->second != -1){ // if will kill a piece
                    gameControl->removePiece(itValues->second);
                    sameTurn = gameControl->hasMoreKill(newId);
                    if (sameTurn){
                        oldId = newId;
                        newId = -1;
                    }
                }

                if (!sameTurn){
                    if (player == WHITE)
                        player = BLACK;
                    else
                        player = WHITE;
                    oldId = newId = -1;
                    gameControl->clearValidPositions();
                }
                gameControl->clearMandatoryPositions();
                break;
            }
        }
    }

    if (!gameControl->hasPieces(BLACK) 
            || !gameControl->canMove(BLACK))
        winner = WHITE;

    else if (!gameControl->hasPieces(WHITE) 
            || !gameControl->canMove(WHITE))
        winner = BLACK;

    if (winner != NONE)
        quitGame();

}

void Game::renderGame(){
    gameControl->renderGame(displayVideo, oldId);
    SDL_Flip(displayVideo);
}

void Game::endGame(){
    gameControl->clearBoard();
    SDL_FreeSurface(displayVideo);
    delete gameControl;
    SDL_Quit();
    TTF_Quit();
}
