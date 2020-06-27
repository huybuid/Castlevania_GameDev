#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"
#include "Simon.h"

#define WHIPUPGRADE_ANIMATION_SET	15

class WhipUpgrade :
	public CItem
{
public:

	WhipUpgrade() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(WHIPUPGRADE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~WhipUpgrade() {};
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->level++; };
};
