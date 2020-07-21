#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define MONEYPOUCH_ANIMATION_SET	13

#define MONEYPOUCH_TYPE_100		0
#define MONEYPOUCH_TYPE_400		1
#define MONEYPOUCH_TYPE_700		2

class MoneyPouch :
	public CItem
{
	int type, points;
public:

	MoneyPouch(float x, float y, int t = 0) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(MONEYPOUCH_ANIMATION_SET);
		SetAnimationSet(ani_set);
		type = t;
		switch (t)
		{
		case MONEYPOUCH_TYPE_100: points = 100;
			break;
		case MONEYPOUCH_TYPE_400: points = 400;
			break;
		case MONEYPOUCH_TYPE_700: points = 700;
			break;
		}
	};
	~MoneyPouch() {};
	void Render();
	void Destroy() override { CItem::Destroy();  };
};

