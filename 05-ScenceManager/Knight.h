#pragma once
#include "Enemy.h"
class Knight :
	public CEnemy
{
	float limit_l, limit_r;
public:
	Knight() :CEnemy() { hp = 3; };
	Knight(float x, float y, int nx) :Knight() { SetPosition(x, y); this->nx = nx; };
	~Knight();
};

