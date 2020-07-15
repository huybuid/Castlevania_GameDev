#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define IHOLYWATER_ANIMATION_SET	18

class IHolyWater :
	public CItem
{
public:

	IHolyWater(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(IHOLYWATER_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~IHolyWater() {};
	void Destroy() override;
};


