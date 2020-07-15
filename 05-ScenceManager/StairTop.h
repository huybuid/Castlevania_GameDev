#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH 16
#define STAIR_BBOX_HEIGHT	16

class StairTop :
	public CGameObject
{

public:
	StairTop() { isInteractive = true; isActive = true; };
	StairTop(float x, float y, int nx):StairTop() { SetPosition(x, y); this->nx = nx; };
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~StairTop();
};

