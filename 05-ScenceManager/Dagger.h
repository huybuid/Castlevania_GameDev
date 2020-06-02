#pragma once
#include "Weapon.h"

#define DAGGER_SPEED_X 0.1f

#define DAGGER_BBOX_HEIGHT	16
#define DAGGER_BBOX_WIDTH	16
class Dagger :
	public CWeapon
{
public:
	Dagger() { this->vx = DAGGER_SPEED_X; };
	~Dagger() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

