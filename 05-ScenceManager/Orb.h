#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define ORB_ANIMATION_SET	14

class Orb :
	public CItem
{
public:

	Orb() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ORB_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~Orb() {};
	void Destroy() override { CItem::Destroy(); };
};

