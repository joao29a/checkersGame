#include "headers/Render.h"

SDL_Surface* Render::assignImage(const char* file){
	SDL_Surface* newImage;
	SDL_Surface* tempImage = IMG_Load(file);

	if (tempImage == NULL) 
		return NULL;

	newImage = SDL_DisplayFormatAlpha(tempImage);
	SDL_FreeSurface(tempImage);

	return newImage;
}

void Render::drawImage(SDL_Surface* dest, SDL_Surface* src, int x,
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
