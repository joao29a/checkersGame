#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Render{
	public:
		static SDL_Surface* assignImage(const char* file);
		static void drawImage(SDL_Surface* dest, SDL_Surface* src, int x,
					int y, int x2, int y2, int w, int h);

};

#endif
