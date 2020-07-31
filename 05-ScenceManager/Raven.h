#pragma once
#include "Enemy.h"

#define RAVEN_SPEED_X 0.08f
#define RAVEN_SPEED_Y 0.08f
#define RAVEN_ACCELARATION_SPEED	0.0002f

#define RAVEN_TRIGGER_X	88
#define RAVEN_TRIGGER_Y	48

#define RAVEN_STATE_IDLE	0
#define RAVEN_STATE_FLYDOWN 1
#define RAVEN_STATE_STRIKE	2

#define RAVEN_BBOX_WIDTH	16
#define RAVEN_BBOX_HEIGHT	16

#define ANIMATION_SET_RAVEN 30

#define RAVEN_IDLE_TIME		500
class Raven :
	public CEnemy
{
	float trigger_x;
public:
	Raven() :CEnemy() {
		hp = 1;
		state = RAVEN_STATE_IDLE;
	};
	Raven(float x, float y, int nx) :Raven() {
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_RAVEN));
		SetPosition(x, y);
		this->nx = nx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int s);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Raven();
};

