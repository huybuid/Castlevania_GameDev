#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"
#include "Simon.h"

#define ORB_INVI_TIME	500
#define ORB_ANIMATION_SET	14

class Orb :
	public CItem
{
	DWORD invi_start;
public:

	Orb(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(ORB_ANIMATION_SET);
		invi_start = GetTickCount();
		SetAnimationSet(ani_set);
		isInteractive = false;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	~Orb() {};
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->hp = SIMON_MAX_HP;
	};
};

