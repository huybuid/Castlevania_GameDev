#pragma once
#include "Weapon.h"
#include "define.h"

#define DAGGER_SPEED_X 0.2f
#define DAGGER_DAMAGE 2
#define DAGGER_BBOX_HEIGHT	16
#define DAGGER_BBOX_WIDTH	16
class Dagger :
	public CWeapon
{
public:
	Dagger() { 
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_DAGGER);
		SetAnimationSet(ani_set);
	};
	Dagger(float x, float y, int nx) :Dagger() { this->x = x; this->y = y; this->nx = nx; this->vx = nx * DAGGER_SPEED_X; };
	~Dagger() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetDamage() { return DAGGER_DAMAGE; }
};

