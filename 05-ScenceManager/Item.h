#pragma once
#include "GameObject.h"

#define ITEM_SPAWN_TIME	5000
#define ITEM_GRAVITY	0.001f
#define ITEM_BBOX_HEIGHT	16
#define ITEM_BBOX_WIDTH		16

class CItem :
	public CGameObject
{
	DWORD spawn_start;

public:
	CItem() :CGameObject() { isInteractive = true; };
	~CItem() {};
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Destroy() { this->isActive = false; }
};

