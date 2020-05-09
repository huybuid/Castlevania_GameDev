#pragma once
#include "GameObject.h"

#define FIREPILLAR_BBOX_WIDTH	16
#define FIREPILLAR_BBOX_HEIGHT	32


class FirePillar :
	public CGameObject
{
public:
	FirePillar() { isCollidable = false; isEnemy = false; isAttackable = true; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
};

