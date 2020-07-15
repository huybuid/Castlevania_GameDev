#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define MONEYPOUCH_ANIMATION_SET	13

class MoneyPouch :
	public CItem
{
public:

	MoneyPouch(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(MONEYPOUCH_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~MoneyPouch() {};
	void Destroy() override { CItem::Destroy(); };
};

