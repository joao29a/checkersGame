#ifndef DEFINES_H
#define DEFINES_H

#define HEIGHT_RESOLUTION 640
#define WIDTH_RESOLUTION 640
#define WHITE_TOTAL 12
#define BLACK_TOTAL 12
#define TOTAL_PIECES WHITE_TOTAL+BLACK_TOTAL
#define BOARD_SIZE 64 //8x8
#define PIECE_SIZE WIDTH_RESOLUTION / sqrt(BOARD_SIZE)
#define REVERSE_TABLE 0 // 0 or 1 
#define REVERSE_PIECE !REVERSE_TABLE //! for black, without for white
#define WHITE_IMAGE "images/white.png"
#define BLACK_IMAGE "images/black.png"
#define BOARD_IMAGE "images/board.png"

enum{
	NONE_WINNER = 0,
	WHITE_WINNER,
	BLACK_WINNER,
	DEAD,
	ALIVE,
	WHITE,
	BLACK
};

#endif
