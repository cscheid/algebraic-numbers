#include "SDL/SDL.h"
#include <iostream>
#include "DrawSurface.h"
#include <limits>
#include "SDL/SDL_opengl.h"
#include "algebraic.h"
#include <vector>
#include "vector2.h"
#include "complex.h"
#include "CameraController.h"
using namespace std;
bool sRunning;
int mouseposx;
int mouseposy;
CameraController cam;

int getMousePosX();
int getMousePosY();
bool sLoop();
void sInit();
void sHandleEvents();
void sSync();
void sQuit();
	bool mousedown=false;
	int mousezoom=0;
	double ndcmousex=0;
	double ndcmousey=0;
const int scwidth=1280;
const int scheight=720;


//square function. used in texture generation.
float sq(float arg) { return arg*arg;}

void putblob(const float x,const float y,const float r)
{
        glTexCoord2f(1,1); glVertex2f(x+r*16,y+r*16);
        glTexCoord2f(1,0); glVertex2f(x+r*16,y-r*16);
        glTexCoord2f(0,0); glVertex2f(x-r*16,y-r*16);
        glTexCoord2f(0,1); glVertex2f(x-r*16,y+r*16);
}
 
//generate circular OpenGL mipmapped texture.
GLuint othertex(const unsigned sz)
{
        GLuint ret; glGenTextures(1,&ret);
        glBindTexture(GL_TEXTURE_2D,ret);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        //aniso();
	int n,x,y,xs=sz,ys=sz;
        unsigned char *td=new unsigned char[xs*ys*3]; float f;
        for (y=ys-1;y>=0;y--) for (x=xs-1;x>=0;x--)
        {
                n=(y*xs+x)*3;
                f=sq((float)sz/2)/(1+sq((float)x-xs/2)+sq((float)y-ys/2));
		f=floor(f);
		if(f>255) f=255;
                td[n]=td[n+1]=td[n+2]=(unsigned char)f;
        }
        gluBuild2DMipmaps(GL_TEXTURE_2D,3,xs,ys,GL_RGB,GL_UNSIGNED_BYTE,td);
        delete td;
        return ret;
}

int main(int argc, char** argv)
{
	sInit();
	int list=0;
	vector<Point> p=precalc(14);
	GLuint tex=othertex(256);

	while(sLoop())
	{
		
		 glClear( GL_COLOR_BUFFER_BIT );
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
		cam.applyCameraTransform();
                //glScaled(.8,.8*1280/800.0,1);
               // glTranslated(-.5,-.30,0);
                if (!list)
                {
			list=glGenLists(1); glNewList(list,GL_COMPILE_AND_EXECUTE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE,GL_ONE);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex);
			glBegin(GL_QUADS);
			float k1=.125;
			float k2=.55;
			for (int n=0;n<p.size();n++)
			{
				switch (p.at(n).o)
				{
					case 1: glColor3f(1,0,0); break;
					case 2: glColor3f(0,1,0); break;
					case 3: glColor3f(0,0,1); break;
					case 4: glColor3f(0.7,0.7,0); break;
					case 5: glColor3f(1,0.6,0); break;
					case 6: glColor3f(0,1,1); break;
					case 7: glColor3f(1,0,1); break;
					case 8: glColor3f(0.6,0.6,0.6); break;
					default: glColor3f(1,1,1); break;
				}
				putblob(p.at(n).x,p.at(n).y,k1*pow(k2,p.at(n).h-3));
				//cout<<vector2(p.at(n).x,p.at(n).y)<<endl;
			}
			glEnd();
			glEndList();
                }
                else if (list) glCallList(list);
		//cout<<list;
		glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
		cam.update(1);
		sSync();
		//cout<<Complex(1,1).length2()<<endl;

	}
	sQuit();
}
bool sLoop()
{
	sHandleEvents();
	return sRunning;
}
void sInit()
{
sRunning=true;
	cam=CameraController(0,0,0,1280.0/800);
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cerr<<"Video initialization failed: "<<SDL_GetError()<<endl;
	}

	const SDL_VideoInfo *videoInfo=SDL_GetVideoInfo();
	if(!videoInfo){
		cerr<<"Video query failed: "<<SDL_GetError()<<endl;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	if(!SDL_SetVideoMode(1280,800,32,SDL_OPENGL)){
		cerr<<"Video mode set failed: "<<SDL_GetError()<<endl;
	}
	cerr<<"HI!"<<endl;
}

void sHandleEvents()
{
	SDL_Event e;
	mousezoom=0;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				sRunning=false;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						sRunning=false;	
						break;
				}
			case SDL_MOUSEBUTTONDOWN:
				switch(e.button.button)
				{
					case SDL_BUTTON_LEFT:
						mousedown=true;
						ndcmousex=e.button.x*2.0/scwidth-1;
						ndcmousey=-e.button.y*2.0/scheight+1;
						break;
					case SDL_BUTTON_WHEELUP:
						mousezoom+=1;
						break;
					case SDL_BUTTON_WHEELDOWN:
						mousezoom-=1;
						break;
				}
				break;			
			case SDL_MOUSEBUTTONUP:
				if(e.button.button == SDL_BUTTON_LEFT)
				{	
					mousedown=false;
					cam.enddrag();
				}	
				break;
			case SDL_MOUSEMOTION:
				ndcmousex=e.motion.x*2.0/scwidth-1;
				ndcmousey=-e.motion.y*2.0/scheight+1;
				break;
			
			
		}
	}
	if(mousezoom!=0)
	{
		cam.mouseZoom(mousezoom*.05);
	}
	cam.setMouseZoomPos(ndcmousex,ndcmousey);
	if(mousedown)
	{
		cam.drag(ndcmousex,ndcmousey);
	}

}
void sSync()
{
	SDL_GL_SwapBuffers();
}
void sQuit()
{
	SDL_Quit();
}

