#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
	float width, height;
public:
	CBrick() { isCollidable = true; isEnemy = false; isActive = true; isAttackable = false; };
	CBrick(float x, float y, float w, float h) :CBrick() { width = w; height = h; this->SetPosition(x, y); };
	virtual void Render();
	void SetAttackable() { isAttackable = true; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};