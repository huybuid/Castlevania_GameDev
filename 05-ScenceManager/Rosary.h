#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define ROSARY_ANIMATION_SET	24

class Rosary :
	public CItem
{
public:

	Rosary(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ROSARY_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~Rosary() {};
	void Destroy() override;
};


