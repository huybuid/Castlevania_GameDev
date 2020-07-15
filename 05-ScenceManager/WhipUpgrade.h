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

	WhipUpgrade(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(WHIPUPGRADE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~WhipUpgrade() {};
	void Destroy() override 
	{ 
		CItem::Destroy();
		CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if (simon->level < 2)
			simon->level++;
	};
};
