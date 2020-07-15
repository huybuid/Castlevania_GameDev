#pragma once
#include "GameObject.h"

#define ITEM_SPAWN_TIME	5000
#define ITEM_GRAVITY	0.001f
#define ITEM_BBOX_HEIGHT	16
#define ITEM_BBOX_WIDTH		16

#define SMALL_HEART_INDICATOR	1
#define BIG_HEART_INDICATOR		2
#define WHIP_UPGRADE_INDICATOR	3
#define IAXE_INDICATOR			4
#define	ICROSS_INDICATOR		5
#define IDAGGER_INDICATOR		6
#define IHOLYWATER_INDICATOR	7
#define STOPWATCH_INDICATOR		8
#define MONEYPOUCH_INDICATOR	9
#define	ROSARY_INDICATOR		10
#define WEAPONUPGRADE_INDICATOR	11
#define BOTTLE_INDICATOR		12
#define ORB_INDICATOR			13

class CItem :
	public CGameObject
{
	DWORD spawn_start;

public:
	CItem() :CGameObject() { isInteractive = true; };
	CItem(float x, float y) :CItem() { SetPosition(x, y); };
	~CItem() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Destroy() { this->isActive = false; }
};

