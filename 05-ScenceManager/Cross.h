#pragma once
#include "Weapon.h"
#include "define.h"

#define	CROSS_SPEED_X		0.15f
#define CROSS_BBOX_WIDTH	16
#define CROSS_BBOX_HEIGHT	16
class Cross :
	public CWeapon
{
	bool isChangedDirection;
public:
	Cross() { 
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_CROSS);
		SetAnimationSet(ani_set);
		isChangedDirection = false;
	};
	Cross(float x, float y, int nx):Cross() { this->x = x; this->y = y; this->nx = nx; this->vx = nx * CROSS_SPEED_X; };
	~Cross();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	bool isHitWall();
	void ChangeDirection();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

