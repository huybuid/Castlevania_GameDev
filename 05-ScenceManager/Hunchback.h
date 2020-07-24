#pragma once
#include "Enemy.h"

#define HUNCHBACK_STATE_IDLE 0
#define HUNCHBACK_STATE_JUMPLOW 1
#define HUNCHBACK_STATE_JUMPHIGH 2

#define HUNCHBACK_JUMPHIGH_SPEEDX 0.05f
#define HUNCHBACK_JUMPHIGH_SPEEDY 0.4f
#define HUNCHBACK_JUMPLOW_SPEEDX 0.1f
#define HUNCHBACK_JUMPLOW_SPEEDY 0.15f

#define HUNCHBACK_BBOX_WIDTH	16
#define HUNCHBACK_BBOX_HEIGHT	16

#define ANIMATION_SET_HUNCHBACK 29

class Hunchback :
	public CEnemy
{
public:
	Hunchback() :CEnemy() { hp = 1; };
	Hunchback(float x, float y) :Hunchback() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_HUNCHBACK));
		SetPosition(x, y);
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Hunchback();
};

