#pragma once
#include "GameObject.h"

#define ANIMATION_SET_EFFECTS	35

#define DEATH_FX	1
#define WPNHIT_FX	0

#define FX_TIME			200
#define FX_TIME_LONG	500
class HitFX: public CGameObject
{
	DWORD fx_start = GetTickCount();
	int fx_time;
	int state;
public:
	HitFX() :CGameObject() { SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_EFFECTS)); fx_start = GetTickCount(); };
	HitFX(float x, float y, int i, bool isLong=false):HitFX() {
		SetPosition(x, y);
		state = i;
		if (isLong) fx_time = FX_TIME_LONG;
		else fx_time = FX_TIME;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	~HitFX();
};

