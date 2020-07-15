#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define WEAPONUPGRADE_ANIMATION_SET	21

class WeaponUpgrade :
	public CItem
{
public:

	WeaponUpgrade(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(WEAPONUPGRADE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~WeaponUpgrade() {};
	void Destroy() override {
		CItem::Destroy(); 
		CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if (simon->weapon_level<3)
			simon->weapon_level++;
	};
};

