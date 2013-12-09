#include "headers/Render.h"

SDL_Surface* Render::assignImage(const char* file){
    if (file == NULL)
        return NULL;

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
    if (dest != NULL)
        drawImage(final,dest,x,y,type,y2,w,h);
    drawImage(final,src,x,y,x2,y2,w,h);
}

void Render::drawRect(SDL_Surface* dest, int x, int y, int w, int h,
        int r, int g, int b){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_FillRect(dest,&rect,SDL_MapRGB(dest->format,r,g,b));
}
