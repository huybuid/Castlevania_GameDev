#pragma once
#include "Enemy.h"

#define ZOMBIE_SPEEDX	0.06f
#define ZOMBIE_GRAVITY  0.001f

#define ANIMATION_SET_ZOMBIE	27

#define ZOMBIE_BBOX_HEIGHT 31
#define ZOMBIE_BBOX_WIDTH 16

class Zombie :
	public CEnemy
{
public:
	Zombie() :CEnemy() { hp = 1; };
	Zombie(float x, float y, int nx) :Zombie() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ZOMBIE));
		SetPosition(x, y);
		this->nx = nx;
		vy = 0;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Zombie();
};

