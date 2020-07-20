#pragma once
#include "Brick.h"

#define ANIMATION_SET_PLATFORM 30
#define PLATFORM_SPEED_X	0.03f
#define STOP_TIME	300

#define PLATFORM_BBOX_WIDTH 32
#define PLATFORM_BBOX_HEIGHT 16

class Platform: public CBrick 
{
	float limit_l, limit_r;
	DWORD stop_start = 0;
public:
	Platform() :CBrick() { 
		SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLATFORM));
		vx = PLATFORM_SPEED_X;
	};
	Platform(float x, float y, float nx, float l, float r) :Platform() { SetPosition(x, y); this->nx = nx; vx *= nx; limit_l = l; limit_r = r; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void ChangeDirection();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Platform();
};

