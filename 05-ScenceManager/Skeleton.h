#pragma once
#include "Enemy.h"
#include <time.h>

#define SKELETON_1_SPEEDX	0.1f
#define SKELETON_1_SPEEDY	0.00f
#define SKELETON_2_SPEEDX	0.07f
#define SKELETON_2_SPEEDY	0.2f
#define SKELETON_3_SPEEDX	0.08f
#define SKELETON_3_SPEEDY	0.2f
#define SKELETON_GRAVITY	0.0005f
#define SKELETON_WALK_DISTANCE	24

#define SKELETON_BBOX_WIDTH	16
#define SKELETON_BBOX_HEIGHT 32

#define SKELETON_STATE_WALK	1
#define SKELETON_STATE_JUMP 2
#define SKELETON_STATE_JUMPBACK 3

#define SKELETON_STOP_TIME	150

#define ANIMATION_SET_SKELETON 31
class Skeleton :
	public CEnemy
{
	float start_x;
	DWORD stop_time = 0;
public:
	Skeleton() :CEnemy() { hp = 1; };
	Skeleton(float x, float y, int n) :Skeleton() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_SKELETON));
		SetPosition(x, y);
		nx = n;
		srand(time(NULL));
		start_x = x;
		SetState(SKELETON_STATE_WALK);
	};
	bool EndWalk();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ThrowBone(int r);
	~Skeleton();
	void SetState(int s);
};

