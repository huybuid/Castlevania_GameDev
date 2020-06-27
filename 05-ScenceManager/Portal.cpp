#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id )
{
	isActive = true;
	isCollidable = true;
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r;
	height = b;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}