#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id, float x, float y, int nx, int state ):CPortal(l,t,r,b,scene_id)
{
	this->simon_nx = nx;
	this->simon_x = x;
	this->simon_y = y;
	this->simon_state = state;
}

CPortal::CPortal(float l, float t, float r, float b, int scene_id)
{
	isActive = true;
	isInteractive = true;
	this->scene_id = scene_id;
	this->x = l;
	this->y = t;
	width = r;
	height = b;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}