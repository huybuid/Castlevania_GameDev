#pragma once
#include "Item.h"
#include "Sprites.h"

#define HEART_BBOX_HEIGHT	16
#define HEART_BBOX_WIDTH	16

#define BIGHEART_ANIMATION_SET 5
class BigHeart :
	public CItem
{
public:
	
	BigHeart():CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(BIGHEART_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~BigHeart() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};

