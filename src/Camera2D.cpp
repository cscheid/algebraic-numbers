#include "Camera2D.h"




Camera2D::Camera2D(double xpos,double ypos,double scale,double aspect) : 
pos(glm::dvec2(xpos,ypos)),scale(scale),aspect(aspect){}

glm::dmat4 Camera2D::getTransform() const
{
	double sc=exp(2.30258509*scale);
	glm::dmat4 ret=glm::dmat4();
	ret[0].x = sc;
    ret[1].y = sc;
    ret[2].z = 1;
    ret[3] = glm::vec4(-pos.x*sc,-pos.y*sc,0, 1.0f);
	return ret;
}
glm::dmat4 Camera2D::getInvTransform() const
{
	double sc=exp(-2.30258509*scale);
	glm::dmat4 ret=glm::dmat4();
	ret[0].x = sc;
    ret[1].y = sc;
    ret[2].z = 1;
    ret[3] = glm::vec4(pos.x,pos.y,0, 1.0f);
	return ret;
}
glm::dmat4 Camera2D::getNDCTransform() const
{
	double sc=exp(2.30258509*scale);
	glm::dmat4 ret=glm::dmat4();
	ret[0].x = sc/aspect;
    ret[1].y = sc;
    ret[2].z = 1;
    ret[3] = glm::vec4(-pos.x*sc/aspect,-pos.y*sc,0, 1.0f);
	return ret;
}
glm::dmat4 Camera2D::getInvNDCTransform() const
{
	double sc=exp(-2.30258509*scale);
	glm::dmat4 ret=glm::dmat4();
	ret[0].x = sc*aspect;
    ret[1].y = sc;
    ret[2].z = 1;
    ret[3] = glm::vec4(pos.x,pos.y,0, 1.0f);
	return ret;
	
}
double Camera2D::getAspect() const{return aspect;}
double Camera2D::getXPos() const{return pos.x;}
double Camera2D::getYPos() const{return pos.y;}
double Camera2D::getScale() const{return scale;}
double Camera2D::getScaleAbsolute() const{return exp(-2.30258509*scale);}

void Camera2D::setXPos(double arg){pos+=glm::vec2(arg,0);}
void Camera2D::setYPos(double arg){pos+=glm::vec2(0,arg);}
void Camera2D::setScale(double arg){scale=arg;}
void Camera2D::setAspect(double arg){aspect=arg;}
void Camera2D::addPos(glm::dvec2 arg){pos+=arg;}
void Camera2D::addScroll(double arg){scale+=arg;}