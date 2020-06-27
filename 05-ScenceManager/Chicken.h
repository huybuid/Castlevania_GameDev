#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define CHICKEN_ANIMATION_SET	22
class Chicken :
	public CItem
{
public:

	Chicken() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(CHICKEN_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~Chicken() {};
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->hp += 6; };
};

