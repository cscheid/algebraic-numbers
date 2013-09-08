#pragma once
#include "glm/glm.hpp"
#include "Camera2D.h"
class CameraController
{
	Camera2D cam;

	double veldrag;
	glm::dvec2 vel;

	bool isDragging;
	glm::dvec2 dragstart;//NDC on (-1,1)
	glm::dvec2 dragcurr;
	glm::dvec2 mousezoompos;

	double scrolldrag;
	double scrollvel;
public:
	CameraController(double xpos=0,double ypos=0,double scale=0,double aspect=1);
	void update(double timestep);
	void drag(double x, double y);
	void enddrag();
	void mouseZoom(double arg);
	void setMouseZoomPos(double x, double y);

	void applyCameraTransform() const;
	Camera2D getCam() const;
};

