#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define ICROSS_ANIMATION_SET	19

class ICross :
	public CItem
{
public:

	ICross(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ICROSS_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~ICross() {};
	void Destroy() override;
};


