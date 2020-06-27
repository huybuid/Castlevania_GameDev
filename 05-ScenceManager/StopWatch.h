#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define STOPWATCH_ANIMATION_SET	20

class StopWatch :
	public CItem
{
public:

	StopWatch() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(STOPWATCH_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~StopWatch() {};
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->weapon_indicator = SIMON_WEAPON_STOPWATCH;
	};
};

