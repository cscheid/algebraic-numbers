#include "DrawSurface.h"
DrawSurface::DrawSurface() : surface(NULL), dealloc(false){}
DrawSurface::DrawSurface(const char* file) : surface(NULL), dealloc(true)
{
    surface=load_image(file);
}
DrawSurface::DrawSurface(int xsize, int ysize) : surface(NULL), dealloc(true)
{
    Uint32 rmask,gmask,bmask,amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x00ff0000;
        gmask = 0x0000ff00;
        bmask = 0x000000ff;
        amask = 0xff000000;
    #endif
    surface=SDL_CreateRGBSurface(SDL_SWSURFACE,xsize,ysize,32,rmask,gmask,bmask,amask);
    dealloc=true;
}
DrawSurface::DrawSurface(SDL_Surface* surfacecpy, bool dealloc) : surface(surfacecpy), dealloc(dealloc){}

DrawSurface::DrawSurface(const DrawSurface& r) : surface(NULL), dealloc(true)
{
    assign(r);
}
DrawSurface& DrawSurface::operator=(const DrawSurface& r)
{
    assign(r);
    return *this;
}
DrawSurface& DrawSurface::assign(const DrawSurface& r)
{
    //if(r.dealloc)
        assignAsCopyOf(r);
    //else
        //assignAsReferenceTo(r);
    return *this;
}
DrawSurface& DrawSurface::assignAsReferenceTo(const DrawSurface& r)
{
    if(this!=(&r))
    {
        if(dealloc&&(surface!=NULL))
            SDL_FreeSurface(surface);
        surface=NULL;
        surface=r.surface;
        dealloc=false;
    }
    return *this;
}
DrawSurface& DrawSurface::assignAsCopyOf(const DrawSurface& r)
{
    if(this!=(&r))
    {
        if(dealloc&&(surface!=NULL))
            SDL_FreeSurface(surface);
        surface=NULL;
        surface=r.copyOf();
        if(surface==NULL)
            dealloc=false;
        else
            dealloc=true;
    }
    return *this;
}

DrawSurface::~DrawSurface()
{
    if(dealloc && (surface!=NULL))
    {
        SDL_FreeSurface(surface);
    }
}


Uint32 DrawSurface::getFlags()                      const{return surface->flags;}
const SDL_PixelFormat *DrawSurface::getFormat()      const{return surface->format;}
int DrawSurface::getWidth()                         const{return surface->w;}
int DrawSurface::getHeight()                        const{return surface->h;}
Uint16 DrawSurface::getPitch()                      const{return surface->pitch;}
const Uint32* DrawSurface::getPixels()              const{return (Uint32 *)surface->pixels;}
const SDL_Surface* DrawSurface::constGetSurface()   const{return surface;}
//SDL_Surface* DrawSurface::getSurface(){return surface;}
Uint32 DrawSurface::pickCol(int x, int y) const
{
    return get_dot(surface,x,y);
}

void DrawSurface::clear()
{
    clearCol(0x00FFFFFF);
}
void DrawSurface::clearCol(Uint32 color)
{
    for(int x=0;x<getWidth();x++)
        for(int y=0;y<getHeight();y++)
            dot(surface,x,y,color);
}
void DrawSurface::drawDot(int x, int y, Uint32 color)
{
    dot(surface,x,y,color);
}
void DrawSurface::flipSurface(){SDL_Flip(surface);}
void DrawSurface::drawLine(int x1, int y1, int x2, int y2, Uint32 color)
{
    bline(surface,x1,y1,x2,y2,color);
}
void DrawSurface::drawWuLine(int x1, int y1, int x2, int y2, Uint32 color)
{
    wuline(surface,x1,y1,x2,y2,color);
}
void DrawSurface::drawCircle(int cx, int cy, int r, Uint32 color)
{
    rasterCircle(surface,cx,cy,r,color);
}
void DrawSurface::drawWuCircle(int cx,int cy, int r, Uint32 color)
{
    wuCircle(surface,cx,cy,r,color);
}
void DrawSurface::applyWuCircle(int cx, int cy, int r, Uint32 color)
{
    DrawSurface mysurface=DrawSurface(getWidth(),getHeight());
    mysurface.clear();
    mysurface.drawWuCircle(cx,cy,r,color);
    mysurface.applyTo(surface);
}
void DrawSurface::applyWuLine(int x1, int y1, int x2, int y2, Uint32 color)
{
    DrawSurface mysurface=DrawSurface(getWidth(),getHeight());
    mysurface.clear();
    mysurface.drawWuLine(x1,y1,x2,y2,color);
    mysurface.applyTo(surface);
}
void DrawSurface::batchApplyWuLine(int numLines, int* lineData, Uint32 color)
{
    DrawSurface mysurface=DrawSurface(getWidth(),getHeight());
    mysurface.clear();
    for(int n=0;n<numLines;n++)
    {
        int x1=lineData[n*4];
        int y1=lineData[n*4+1];
        int x2=lineData[n*4+2];
        int y2=lineData[n*4+3];
        mysurface.drawWuLine(x1,y1,x2,y2,color);
    }
    mysurface.applyTo(this);
}
void DrawSurface::batchApplyContigWuLine(int numLines, int* lineData, Uint32 color)
{
    DrawSurface mysurface=DrawSurface(getWidth(),getHeight());
    mysurface.clear();
    int lastx=lineData[0];
    int lasty=lineData[1];
    for(int n=0;n<numLines;n++)
    {
        int x=lineData[n*2+2];
        int y=lineData[n*2+3];
        mysurface.drawWuLine(lastx,lasty,x,y,color);
        lastx=x;lasty=y;
    }
    mysurface.applyTo(this);
}
SDL_Surface* DrawSurface::copyOf() const
{
    if(surface!=NULL)
    {
        int xsize=getWidth();
        int ysize=getHeight();
        Uint32 rmask,gmask,bmask,amask;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        #else
            rmask = 0x00ff0000;
            gmask = 0x0000ff00;
            bmask = 0x000000ff;
            amask = 0xff000000;
        #endif
        SDL_Surface* tempsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,xsize,ysize,32,rmask,gmask,bmask,amask);
        for(int x=0;x<xsize;x++)
            for(int y=0;y<ysize;y++)
                dot(tempsurface,x,y,pickCol(x,y));

        return tempsurface;
    } else
    {
        return NULL;
    }
}

void DrawSurface::applyTo(DrawSurface *surfaceto, int x, int y) const
{surfaceto->applyFrom(surface,x,y);}

void DrawSurface::applyTo(SDL_Surface *surfaceto, int x, int y) const
{apply_surface(x,y,surface,surfaceto);}

void DrawSurface::applyFrom(const DrawSurface *surfacefrom, int x, int y)
{
    surfacefrom->applyTo(surface,x,y);
}
void DrawSurface::applyFrom(const SDL_Surface *surfacefrom, int x, int y)
{
    apply_surface(x,y,surfacefrom,surface);
}
