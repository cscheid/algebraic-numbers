#ifndef UTIL_H
#define UTIL_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <cmath>
#include <iostream>
#include <string>



//Nothing in this file should rely on global variables. Only what is passed in the function arguments.

SDL_Surface *load_image(const char* filename,Uint8 r, Uint8 g, Uint8 b);
SDL_Surface *load_image(const char* filename);
void apply_surface(int x,int y,const SDL_Surface *source,SDL_Surface *destination);
void apply_surface(int x,int y,const SDL_Surface *source,SDL_Surface *destination,const SDL_Rect *cliprect);
Uint32 get_dot(const SDL_Surface *surface,int x,int y);
void dot(SDL_Surface *surface, int x,int y,Uint32 pixel);
Uint8 rgbb(Uint32 pixel);
Uint8 rgbg(Uint32 pixel);
Uint8 rgbr(Uint32 pixel);
Uint8 rgba(Uint32 pixel);
Uint8 lerp(Uint8 a, Uint8 b, double t);
void wuline(SDL_Surface *surface,int x1,int y1,int x2,int y2, Uint32 pixel);
void wuCircle(SDL_Surface *surface, int cx, int cy, int r, Uint32 color);
void rasterCircle(SDL_Surface* surface,  int x0, int y0, int radius,Uint32 color);
double fract(double x);
void bline(SDL_Surface* surface, int x,int y,int x2, int y2, Uint32 color);

#endif // UTIL_H
