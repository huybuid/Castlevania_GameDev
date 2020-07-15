#pragma once
#include "Weapon.h"
#include "define.h"

#define	CROSS_SPEED_X		0.15f
#define CROSS_SPEED_TURNBACK 0.0005f

#define CROSS_DAMAGE 3

#define CROSS_BBOX_WIDTH	16
#define CROSS_BBOX_HEIGHT	16

#define CROSS_TURNBACK_X	128

#define CROSS_STATE_START	0
#define CROSS_STATE_TURN	1
#define CROSS_STATE_BACK	2
class Cross :
	public CWeapon
{
	float origin_x, origin_nx;
	bool isChangedDirection;
public:
	Cross() { 
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_CROSS);
		SetAnimationSet(ani_set);
		isChangedDirection = false;
	};
	Cross(float x, float y, int nx) :Cross() { origin_x = x; origin_nx = nx; SetPosition(x, y); this->nx = nx; this->vx = nx * CROSS_SPEED_X; };
	~Cross();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	bool isHitWall();
	void ChangeDirection();
	void SetState(int i) {
		state = i;
		if (state == CROSS_STATE_BACK)
		{
			nx = -origin_nx;
			vx = nx * CROSS_SPEED_X;
			isChangedDirection = true;
		}
	};
	int GetState() { return state; };
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetDamage() { return CROSS_DAMAGE; }
};

