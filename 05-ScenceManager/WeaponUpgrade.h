#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define WEAPONUPGRADE_ANIMATION_SET	21

class WeaponUpgrade :
	public CItem
{
public:

	WeaponUpgrade() :CItem() {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(WEAPONUPGRADE_ANIMATION_SET);
		SetAnimationSet(ani_set);
	};
	~WeaponUpgrade() {};
	void Destroy() override {
		CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->weapon_level++;
	};
};

