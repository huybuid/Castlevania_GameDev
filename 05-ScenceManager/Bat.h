#pragma once
#include "Enemy.h"

#define BAT_SPEED_X 0.08f
#define BAT_SPEED_Y 0.05f

#define BAT_TRIGGER_X	88
#define BAT_TRIGGER_Y	48

#define BAT_STATE_IDLE	0
#define BAT_STATE_FLY	1

#define BAT_BBOX_WIDTH	16
#define BAT_BBOX_HEIGHT 16

#define ANIMATION_SET_BAT 26

class Bat :
	public CEnemy
{
	int state;
	float start_y;
public:
	Bat() :CEnemy() {
		hp = 1;
		state = BAT_STATE_IDLE;
	};
	Bat(float x, float y, int nx) :Bat() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BAT));
		SetPosition(x, y);
		this->nx = nx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int s);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Bat();
};

