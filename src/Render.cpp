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

void Render::drawImage(SDL_Surface* final, SDL_Surface* dest, int type,
		SDL_Surface* src, int x, int y, int x2, int y2, int w, int h){
	drawImage(final,dest,x,y,type,y2,w,h);
	drawImage(final,src,x,y,x2,y2,w,h);
}

void Render::drawRect(SDL_Rect* dest, int x, int y, int w, int h){
	dest->x = x;
	dest->y = y;
	dest->w = w;
	dest->h = h;
}
