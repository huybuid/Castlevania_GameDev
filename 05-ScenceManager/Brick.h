#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
public:
	CBrick() { isCollidable = true; isEnemy = false; isActive = true; isAttackable = false; };
	virtual void Render();
	void SetAttackable() { isAttackable = true; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};