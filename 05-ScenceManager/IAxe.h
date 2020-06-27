#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define IAXE_ANIMATION_SET	17

class IAxe :
	public CItem
{
public:

	IAxe() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(IAXE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~IAxe() {};
	void Destroy() override;
};

