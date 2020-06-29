#include "FirePillar.h"
#include "PlayScence.h"
#include "Game.h"
#include "BigHeart.h"
#include "Chicken.h"
#include "IAxe.h"
#include "ICross.h"
#include "IDagger.h"
#include "IHolyWater.h"
#include "InvincibleBottle.h"
#include "MoneyPouch.h"
#include "Orb.h"
#include "Rosary.h"
#include "StopWatch.h"
#include "SmallHeart.h"
#include "WeaponUpgrade.h"
#include "WhipUpgrade.h"

void FirePillar::Render()
{
	if (!isActive) return;
	animation_set->at(type)->Render(x, y);
	//RenderBoundingBox();
}

void FirePillar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (type == TYPE_FIREPILLAR)
	{
		r = x + FIREPILLAR_BBOX_WIDTH;
		b = y + FIREPILLAR_BBOX_HEIGHT;
	}
	else
	{
		r = x + CANDLE_BBOX_WIDTH;
		b = y + CANDLE_BBOX_HEIGHT;
	}
}

void FirePillar::Destroy()
{
	if (item_id != 0)
	{
		CItem *item = SpawnItem(item_id);
		item->SetPosition(this->x, this->y);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items.push_back(item);
	}
	isActive = false;
}

CItem *FirePillar::SpawnItem(int i)
{
	switch (i)
	{
	case 1:
		return new SmallHeart();
		break;
	case 2:
		return new BigHeart();
	case 3:
		return new WhipUpgrade();
	case 4:
		return new IAxe();
	case 5:
		return new ICross();
	case 6:
		return new IDagger();
	case 7:
		return new IHolyWater();
	case 8:
		return new StopWatch();
	case 9:
		return new MoneyPouch();
	case 10:
		return new Rosary();
	case 11:
		return new WeaponUpgrade();
	case 12:
		return new InvincibleBottle();
	case 13:
		return new Orb();
	case 14:
		return new Chicken();
	default:
		break;
	}
}