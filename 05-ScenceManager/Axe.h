#pragma once
#include "Weapon.h"
#include "define.h"

#define AXE_SPEED_X 0.14f //double the speed of Simon
#define AXE_SPEED_Y	-0.35f	
#define AXE_GRAVITY 0.0012f
#define AXE_DAMAGE 3

#define AXE_BBOX_HEIGHT	16
#define AXE_BBOX_WIDTH	16
class Axe :
	public CWeapon
{
public:
	Axe() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_AXE);
		SetAnimationSet(ani_set);
		vy = AXE_SPEED_Y;
	};
	Axe(float x, float y, int nx) :Axe() { this->x = x; this->y = y; this->nx = nx; this->vx = nx * AXE_SPEED_X; };
	~Axe() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetDamage() { return AXE_DAMAGE; }
};