#ifndef RENDER_H
#define RENDER_H

#include "defines.h"

class Render{
    public:
        static SDL_Surface* assignImage(const char* file);

        static void drawImage(SDL_Surface* dest, SDL_Surface* src, int x,
                int y, int x2, int y2, int w, int h);

        static void drawImage(SDL_Surface* final, SDL_Surface* dest, int type,
                SDL_Surface* src, int x, int y, int x2, int y2, int w, int h);

        static void drawRect(SDL_Surface* dest, int x, int y, int w, int h, 
                int r, int g, int b);

};

#endif
