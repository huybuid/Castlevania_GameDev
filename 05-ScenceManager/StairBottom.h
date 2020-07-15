#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH 16
#define STAIR_BBOX_HEIGHT	16
class StairBottom :
	public CGameObject
{
public:
	StairBottom() { isInteractive = true; };
	StairBottom(float x, float y, int nx):StairBottom() { SetPosition(x, y); this->nx = nx; };
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~StairBottom();
};

