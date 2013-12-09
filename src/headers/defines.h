#ifndef DEFINES_H
#define DEFINES_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

using namespace std;

#define HEIGHT_RESOLUTION 600
#define WIDTH_RESOLUTION 600
#define REVERSE_TABLE 0 //0 or 1 //if reverse_table != reverse_piece then
#define REVERSE_PIECE 1 //0 or 1 //piece will be on black spots
// else on white spots

#define R_VALID 58//valid for positions a piece can go
#define G_VALID 26
#define B_VALID 106

#define R_POS 13//pos for chosen piece
#define G_POS 97
#define B_POS 107

extern int PIECES_AMOUNT; //12 20 30
extern int BOARD_SIZE; //64 100 144
extern int PIECE_SIZE; //75  60  50
extern bool MANDATORY_KILL;
extern const char* WHITE_IMAGE; //"images/white12.png" //8 10 12
extern const char* BLACK_IMAGE; // "images/black12.png"
extern const char* BOARD_IMAGE; //"images/board12.png"

enum{
    NONE = 0,
    KING,
    WHITE,
    BLACK
};

#endif
