#pragma once
#include "Enemy.h"

#define KNIGHT_SPEED_X  0.04f
#define ANIMATION_SET_KNIGHT 25

#define KNIGHT_BBOX_WIDTH	16
#define KNIGHT_BBOX_HEIGHT	32
class Knight :
	public CEnemy
{
	float limit_l, limit_r;
public:
	Knight() :CEnemy() { hp = 6; };
	Knight(float x, float y, int nx, float l, float r) :Knight() { 
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_KNIGHT));
		SetPosition(x, y); 
		this->nx = nx; 
		this->vx = nx * KNIGHT_SPEED_X;
		limit_l = l;
		limit_r = r;
		vy = 0;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Knight();
};

