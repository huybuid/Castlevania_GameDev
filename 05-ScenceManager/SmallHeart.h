#pragma once
#include "Item.h"
#include "PlayScence.h"
#include "Game.h"

#define SMALLHEART_BBOX_HEIGHT	16
#define SMALLHEART_BBOX_WIDTH	8

#define SMALLHEART_SPEED_X 0.03f
#define SMALLHEART_GRAVITY	0.02f

#define SMALLHEART_ANIMATION_SET 11
class SmallHeart :
	public CItem
{
	float limit_left, limit_right;
public:

	SmallHeart(float x, float y) :CItem(x,y) {
		LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(SMALLHEART_ANIMATION_SET);
		SetAnimationSet(ani_set);
		limit_left = x - 16;
		limit_right = x + 16;
		vx = SMALLHEART_SPEED_X;
		vy = SMALLHEART_GRAVITY;
	};
	~SmallHeart() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Destroy() override { CItem::Destroy(); ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->heart ++; };
};

