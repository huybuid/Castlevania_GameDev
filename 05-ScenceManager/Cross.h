#pragma once
#include "Weapon.h"

#define		CROSS_SPEED		0.02f
#define CROSS_BBOX_WIDTH	16
#define CROSS_BBOX_HEIGHT	16
class Cross :
	public CWeapon
{
public:
	Cross() { this->vx = CROSS_SPEED; };
	~Cross();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

