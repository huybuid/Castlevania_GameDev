#pragma once
#include "Weapon.h"
#include "define.h"

#define HOLYWATER_SPEED_X 0.15f
#define HOLYWATER_SPEED_Y -0.05f
#define HOLYWATER_GRAVITY	0.0005f

#define HOLYWATER_STATE_BOTTLE	0
#define HOLYWATER_STATE_BURN	1

#define HOLYWATER_BBOX_X_BOTTLE	8
#define HOLYWATER_BBOX_X_BURN	16
#define HOLYWATER_BBOX_Y		16

#define HOLYWATER_BURN_TIME		600

class HolyWater :
	public CWeapon
{
	DWORD burn_time;
	int state;
public:
	HolyWater() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_HOLYWATER);
		SetAnimationSet(ani_set);
		SetState(HOLYWATER_STATE_BOTTLE);
	};
	HolyWater(float x, float y, int nx) :HolyWater() { this->x = x; this->y = y; this->nx = nx; this->vx = nx * HOLYWATER_SPEED_X; this->vy = HOLYWATER_SPEED_Y; };
	~HolyWater() {  };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	void SetState(int i) { 
		state = i; 
		if (i == HOLYWATER_STATE_BURN)
			x -= 8;
	};
	int GetState() { return state; };
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

