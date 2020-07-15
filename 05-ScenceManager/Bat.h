#pragma once
#include "Enemy.h"

#define BAT_SPEED_X 0.2f
#define BAT_SPEED_Y 0.2f
#define BAT_TRIGGER_X
#define BAT_TRIGGER_Y
#define BAT_STATE_IDLE
#define BAT_STATE_FLY

class Bat :
	public CEnemy
{
public:
	Bat();
	~Bat();
};

