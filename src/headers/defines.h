#ifndef DEFINES_H
#define DEFINES_H

#define HEIGHT_RESOLUTION 600
#define WIDTH_RESOLUTION 600
#define PIECES_AMOUNT 30 //12 20 30
#define WHITE_TOTAL PIECES_AMOUNT
#define BLACK_TOTAL PIECES_AMOUNT
#define TOTAL_PIECES WHITE_TOTAL+BLACK_TOTAL
#define BOARD_SIZE 144 //64 100 144
#define PIECE_SIZE 50 //75  60  50
#define REVERSE_TABLE 0 // 0 or 1 
#define REVERSE_PIECE !REVERSE_TABLE //! for black, without for white
#define WHITE_IMAGE "images/white12.png" //8 10 12
#define BLACK_IMAGE "images/black12.png"
#define BOARD_IMAGE "images/board12.png"
#define VALID_IMAGE "images/valid12.png"

enum{
	NONE = 0,
	KING,
	WHITE,
	BLACK
};

#endif
