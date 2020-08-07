#pragma once
#include "Enemy.h"
#include "PlayScence.h"
#include "Boss.h"

#define FIREBALL_SPEED	0.09f
#define ANIMATION_SET_FIREBALL 34

#define FIREBALL_BBOX_WIDTH	8
#define FIREBALL_BBOX_HEIGHT 8

class Fireball :
	public CEnemy
{
public:
	Fireball() :CEnemy() { hp = 1; 	SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_FIREBALL)); }
	Fireball(float x, float y, int n) :Fireball() {
		SetPosition(x, y);
		float simon_x, simon_y;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
		if (simon_x == x)
		{
			SetSpeed(0, -FIREBALL_SPEED * nx);
		}
		else if (simon_y == y)
		{
			SetSpeed(-FIREBALL_SPEED * nx, 0);

		}
		else
		{
			SetSpeed(FIREBALL_SPEED * nx,
				1.0 * (simon_y - y - BOSS_BBOX_WIDTH / 2) / (simon_x - x - BOSS_BBOX_HEIGHT / 2) * nx * FIREBALL_SPEED);
		}
		nx = n;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Fireball();
	bool isOutOfScreen(int obj_width, int obj_height);
};

