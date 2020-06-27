#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define IDAGGER_ANIMATION_SET	16

class IDagger :
	public CItem
{
public:

	IDagger() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(IDAGGER_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~IDagger() {};
	void Destroy() override;
};


