#include "FirePillar.h"
#include "PlayScence.h"
#include "Game.h"
#include "ItemList.h"

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
		if (item !=NULL)
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items.push_back(item);
	}
	isActive = false;
}

CItem *FirePillar::SpawnItem(int i)
{
	switch (i)
	{
	case ITEM_INDICATOR_SMALLHEART:
		return new SmallHeart(this->x, this->y);
	case ITEM_INDICATOR_BIGHEART:
		return new BigHeart(this->x, this->y);
	case ITEM_INDICATOR_WHIPUPGRADE:
		return new WhipUpgrade(this->x, this->y);
	case ITEM_INDICATOR_AXE:
		return new IAxe(this->x, this->y);
	case ITEM_INDICATOR_CROSS:
		return new ICross(this->x, this->y);
	case ITEM_INDICATOR_DAGGER:
		return new IDagger(this->x, this->y);
	case ITEM_INDICATOR_HOLYWATER:
		return new IHolyWater(this->x, this->y);
	case ITEM_INDICATOR_STOPWATCH:
		return new StopWatch(this->x, this->y);
	case ITEM_INDICATOR_MONEYPOUCH100:
		return new MoneyPouch(this->x, this->y, 0);
	case ITEM_INDICATOR_MONEYPOUCH400:
		return new MoneyPouch(this->x, this->y, 1);
	case ITEM_INDICATOR_MONEYPOUCH700:
		return new MoneyPouch(this->x, this->y, 2);
	case ITEM_INDICATOR_ROSARY:
		return new Rosary(this->x, this->y);
	case ITEM_INDICATOR_WPNUPGRADE:
		return new WeaponUpgrade(this->x, this->y);
	case ITEM_INDICATOR_INVISPOTION:
		return new InvincibleBottle(this->x, this->y);
	case ITEM_INDICATOR_ORB:
		return new Orb(this->x, this->y);
	case ITEM_INDICATOR_CHICKEN:
		return new Chicken(this->x, this->y);
	default:
		return NULL;
	}
}