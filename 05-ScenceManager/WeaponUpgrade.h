#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define WEAPONUPGRADE_ANIMATION_SET	21

#define LEVEL2 0
#define LEVEL3 1

class WeaponUpgrade :
	public CItem
{
	int type;
public:

	WeaponUpgrade(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(WEAPONUPGRADE_ANIMATION_SET);
		SetAnimationSet(ani_set);
		if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->weapon_level == 2)
			type = LEVEL3;
		else type = LEVEL2;
	};
	~WeaponUpgrade() {};
	void Destroy() override {
		CItem::Destroy(); 
		CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if (simon->weapon_level<3)
			simon->weapon_level++;
	};
	void Render();
};

