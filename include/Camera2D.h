#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Camera2D
{
	glm::dvec2 pos;
	double scale;
	double aspect;
public:
	Camera2D(double xpos=0,double ypos=0,double scale=0,double aspect=1);
	glm::dmat4 getTransform() const;
	glm::dmat4 getInvTransform() const;
	glm::dmat4 getNDCTransform() const;
	glm::dmat4 getInvNDCTransform() const;
	double getAspect() const;
	double getXPos() const;
	double getYPos() const;
	double getScale() const;
	double getScaleAbsolute() const;//returns exp(-2.30258509*scale)

	void setXPos(double arg);
	void setYPos(double arg);
	void addPos(glm::dvec2 arg);
	void addScroll(double arg);
	void setScale(double arg);
	void setAspect(double arg);

};

