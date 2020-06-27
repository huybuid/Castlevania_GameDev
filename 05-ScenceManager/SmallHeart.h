#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define HEART_BBOX_HEIGHT	16
#define HEART_BBOX_WIDTH	8

#define SMALLHEART_ANIMATION_SET 11
class SmallHeart :
	public CItem
{
public:

	SmallHeart() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(SMALLHEART_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~SmallHeart() {};
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->heart ++; };
};

