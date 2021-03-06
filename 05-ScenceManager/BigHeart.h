#pragma once
#include "Item.h"
#include "Sprites.h"
#include "PlayScence.h"
#include "Game.h"

#define HEART_BBOX_HEIGHT	16
#define HEART_BBOX_WIDTH	16

#define BIGHEART_ANIMATION_SET 12
class BigHeart :
	public CItem
{
public:
	
	BigHeart(float x, float y):CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(BIGHEART_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~BigHeart() {};
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->heart += 5; };
};

