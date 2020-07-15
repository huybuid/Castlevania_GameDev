#include "Bat.h"
#include "PlayScence.h"

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (state == BAT_STATE_IDLE)
	{
		CGameObject *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if ((simon->y <= this->y + BAT_TRIGGER_Y) && (simon->x <= this->x + BAT_TRIGGER_X))
		{
			SetState(BAT_STATE_FLY);
		}
	}
	if (state == BAT_STATE_FLY)
	{
		x += dx;
		if (y <= start_y + BAT_TRIGGER_Y)
			y += dy;
		else
		{
			y = start_y + BAT_TRIGGER_Y;
			vy = 0;
		}
	}
}

void Bat::Render()
{
	if (!isActive) return;
	animation_set->at(state)->Render(x, y, nx);


}

void Bat::SetState(int s)
{
	state = s;
	if (state == BAT_STATE_FLY)
	{
		vx = nx * BAT_SPEED_X;
		vy = BAT_SPEED_Y;
	}
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = x + BAT_BBOX_HEIGHT;
}



Bat::~Bat()
{
}
