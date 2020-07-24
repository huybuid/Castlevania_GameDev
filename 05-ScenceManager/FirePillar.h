#pragma once
#include "Enemy.h"
#include "Item.h"
#include "define.h"

#define FIREPILLAR_BBOX_WIDTH	16
#define FIREPILLAR_BBOX_HEIGHT	32

#define CANDLE_BBOX_WIDTH		8
#define CANDLE_BBOX_HEIGHT		16

#define HIDDENBRICK_WIDTH		16
#define HIDDENBRICK_HEIGHT		16

#define TYPE_CANDLE			0
#define TYPE_FIREPILLAR		1
#define TYPE_HIDDENBRICK	2


class FirePillar :
	public CEnemy
{
	float width, height;
	int type, item_id;
public:
	FirePillar():CEnemy() { hp = 1; isEnemy = false; this->animation_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_FIREPILLAR); };
	FirePillar(float x, float y, int t, int id) :FirePillar() { type = t; item_id = id; this->x = x; this->y = y; if (t == TYPE_HIDDENBRICK) isCollidable = true; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
	~FirePillar() {};
	CItem* SpawnItem(int n);
};

