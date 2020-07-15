#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define INVINCIBLEBOTTLE_ANIMATION_SET	23

class InvincibleBottle :
	public CItem
{
public:

	InvincibleBottle(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(INVINCIBLEBOTTLE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~InvincibleBottle() {};
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->StartUntouchable(); };
};

