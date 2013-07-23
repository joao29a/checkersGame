#ifndef DEFINES_H
#define DEFINES_H

#include <string>

using namespace std;

#define HEIGHT_RESOLUTION 600
#define WIDTH_RESOLUTION 600
#define REVERSE_TABLE 0 // don't change it
#define REVERSE_PIECE !REVERSE_TABLE // don't change it
extern int PIECES_AMOUNT; //12 20 30
extern int TOTAL_PIECES;
extern int BOARD_SIZE; //64 100 144
extern int PIECE_SIZE; //75  60  50
extern bool MANDATORY_KILL;
extern const char* WHITE_IMAGE; //"images/white12.png" //8 10 12
extern const char* BLACK_IMAGE; // "images/black12.png"
extern const char* BOARD_IMAGE; //"images/board12.png"
extern const char* VALID_IMAGE; //"images/valid12.png"

enum{
	NONE = 0,
	KING,
	WHITE,
	BLACK
};

#endif
