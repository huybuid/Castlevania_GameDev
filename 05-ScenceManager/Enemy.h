#pragma once
#include "GameObject.h"
class CEnemy :
	public CGameObject
{
public:
	CEnemy();
	virtual void Destroy() =0;
	~CEnemy();
};

