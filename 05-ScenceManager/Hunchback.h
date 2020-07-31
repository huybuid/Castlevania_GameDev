#pragma once
#include "Enemy.h"
#include <cstdlib>
#include <time.h>

#define HUNCHBACK_STATE_IDLE 0
#define HUNCHBACK_STATE_JUMP 1

#define HUNCHBACK_JUMPHIGH_SPEEDX 0.05f
#define HUNCHBACK_JUMPHIGH_SPEEDY 0.35f
#define HUNCHBACK_JUMPLOW_SPEEDX 0.1f
#define HUNCHBACK_JUMPLOW_SPEEDY 0.15f
#define HUNCHBACK_GRAVITY		0.001f

#define HUNCHBACK_BBOX_WIDTH	16
#define HUNCHBACK_BBOX_HEIGHT	16
#define HUNCHBACK_TRIGGER_DISTANCE	100

#define HUNCHBACK_STOP_TIME	100

#define ANIMATION_SET_HUNCHBACK 29

class Hunchback :
	public CEnemy
{
	int state, next_nx;
	DWORD stop_time = 0;
	float trigger;
public:
	Hunchback() :CEnemy() { hp = 1; };
	Hunchback(float x, float y, float n) :Hunchback() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_HUNCHBACK));
		SetPosition(x, y);
		nx = n;
		next_nx = 1;
		trigger = x + nx * HUNCHBACK_TRIGGER_DISTANCE;
		srand(time(NULL));
		state = HUNCHBACK_STATE_IDLE;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Hunchback();
	void SetState(int s);
};

