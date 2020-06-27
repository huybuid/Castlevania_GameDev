#pragma once
#include "GameObject.h"
#include "Item.h"
#include "define.h"

#define FIREPILLAR_BBOX_WIDTH	16
#define FIREPILLAR_BBOX_HEIGHT	32

#define CANDLE_BBOX_WIDTH		8
#define CANDLE_BBOX_HEIGHT		16

#define TYPE_FIREPILLAR		1
#define TYPE_CANDLE			0


class FirePillar :
	public CGameObject
{
	CItem *item = NULL;
	float width, height;
	int type, item_id;
public:
	FirePillar() { isCollidable = false; isEnemy = false; isAttackable = true; this->animation_set = CAnimationSets::GetInstance()->Get(ANIMATION_SET_FIREPILLAR); };
	FirePillar(float x, float y, int t, int id) :FirePillar() { type = t; item_id = id; this->x = x; this->y = y; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Destroy();
	void SetItem(CItem *i) { item = i; };
	~FirePillar() { if (item!=NULL)	delete item; };
	CItem* SpawnItem(int n);
};

