#pragma once
#include "Enemy.h"

#define BOSS_BBOX_WIDTH  48
#define BOSS_BBOX_HEIGHT 24
#define BOSS_TRIGGER	640.0f

#define BOSS_ANI_IDLE	0
#define BOSS_ANI_FLY	1

#define BOSS_STATE_IDLE				1
#define BOSS_STATE_FLY				2
#define BOSS_STATE_ATTACK			3

#define BOSS_TIME_ATTACK	10000
#define BOSS_TIME_CHECK_FLY 3000
#define BOSS_TIME_HURT		500
#define BOSS_TIME_ATTACK2 300

#define BOSS_RANDOM_X1 620
#define BOSS_RANDOM_Y1 64
#define BOSS_RANDOM_X2 684
#define BOSS_RANDOM_Y2 32

#define BOSS_SPEED_AUTO_FLY_X 0.1f
#define BOSS_SPEED_AUTO_FLY_Y 0.08f

#define BOSS_TIME_CURVE 2000

#define TIME_RATE 0.00005f

#define ORB_SPAWN_X		632
#define ORB_SPAWN_Y		80

#define ANIMATION_SET_BOSS	33

class Boss :
	public CEnemy
{
	DWORD attack_start;
	DWORD fly_start;
	DWORD curve_start;
	DWORD die_start;
	float x0;
	float y0;
	float x1;
	float y1;
	float x2;
	float y2;
	int step;
	int type;
	float start_x;
	float start_y;
	bool trigger;
public:
	Boss() :CEnemy() { hp = 24; SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BOSS)); trigger = true; }
	Boss(float x, float y) :Boss()
	{
		SetState(BOSS_STATE_IDLE);
		SetPosition(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void AutoFly(float next_x, float next_y);
	void AutoAttack(float next_x, float next_y);
	void FlyStraight(float next_x, float next_y);
	void FlyCurve(float next_x, float next_y);
	float getPt(int n1, int n2, float perc);
	void SetFly();
	void Destroy();
	~Boss();
};

