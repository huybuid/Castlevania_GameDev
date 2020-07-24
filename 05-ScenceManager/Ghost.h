#pragma once
#include "Enemy.h"

#define GHOST_SPEED_SLOW 0.06f
#define GHOST_SPEED_FAST 0.02f

#define GHOST_SWITCH_TIME	300

#define GHOST_BBOX_WIDTH	16
#define GHOST_BBOX_HEIGHT	16

#define ANIMATION_SET_GHOST	28
class Ghost :
	public CEnemy
{
	DWORD switch_time;
	int ny;
public:
	Ghost() :CEnemy() { hp = 6; switch_time = GetTickCount() - GHOST_SWITCH_TIME; };
	Ghost(float x, float y) :Ghost() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_GHOST));
		SetPosition(x, y);
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Ghost();
};

