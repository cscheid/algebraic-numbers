#include "CameraController.h"
#include <iostream>
#include "SDL/SDL_opengl.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CameraController::CameraController(double xpos,double ypos,double scale,double aspect)
{
	cam=Camera2D(xpos,ypos,scale,aspect);
	veldrag=.9;
	scrolldrag=.87;
	mousezoompos=dragcurr=dragstart=vel=glm::vec2(0,0);
	isDragging=false;
	scrollvel=0;
}
void CameraController::update(double timestep)
{
	cam.addPos(vel*timestep);
	vel*=veldrag;
	cam.addScroll(scrollvel*timestep);
	scrollvel*=scrolldrag;
}
void CameraController::setMouseZoomPos(double x, double y)
{
	mousezoompos=glm::dvec2(x,y);
}
void CameraController::drag(double x, double y)
{
	if(isDragging)
	{
		dragstart=dragcurr;
		dragcurr=glm::dvec2(x,y);
		//std::cout<<cam.getAspect()/cam.getScaleAbsolute()*(dragstart-dragcurr).x;
		cam.addPos(glm::dvec2(cam.getAspect()*cam.getScaleAbsolute()*(dragstart-dragcurr).x,
							(dragstart-dragcurr).y*cam.getScaleAbsolute()));
	} else {
		isDragging=true;
		dragstart=dragcurr=glm::dvec2(x,y);
	}
}
void CameraController::enddrag()
{
	if(isDragging)
	{
		isDragging=false;
		vel-=(dragcurr-dragstart)*veldrag*cam.getScaleAbsolute();
		dragcurr=dragstart=glm::dvec2(0,0);
	}
}
void CameraController::mouseZoom(double zamount)
{
	/*double factor=(1-exp(2.30258509*zamount))/cam.getScaleAbsolute();
	cam.addPos(glm::dvec2(cam.getAspect()*mousezoompos.x*factor,
						mousezoompos.y*factor));*/

	cam.addScroll(zamount);
	scrollvel+=zamount*scrolldrag;
}

void CameraController::applyCameraTransform() const {
	glLoadMatrixd(glm::value_ptr(cam.getNDCTransform()));
}
Camera2D CameraController::getCam() const{return cam;}
