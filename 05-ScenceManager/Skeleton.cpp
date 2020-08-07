#include "Skeleton.h"
#include "PlayScence.h"
#include "Bone.h"

bool Skeleton::EndWalk()
{
	if (nx > 0)
	{
		if (x >= start_x + SKELETON_WALK_DISTANCE)
		{
			x = start_x + SKELETON_WALK_DISTANCE;
			return true;
		}
	}
	else
	{
		if (x <= start_x - SKELETON_WALK_DISTANCE)
		{
			x = start_x - SKELETON_WALK_DISTANCE;
			return true;
		}
	}
	return false;
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive) return;
	DWORD tick = GetTickCount();
	if (freeze_start > 0)
	{
		if (isDamaged)
		{
			if (tick - damage_start > DAMAGE_FREEZE_TIME)
			{
				isDamaged = false;
				damage_start = 0;
			}
		}
		if (tick - freeze_start > freeze_time)
		{
			freeze_start = 0;
			freeze_time = 0;
		}
		return;
	}
	if (tick - stop_time <= SKELETON_STOP_TIME) return;
	float simon_x, simon_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
	CGameObject::Update(dt);
	if (tick - stop_time > 0 && stop_time > 0)
	{
		stop_time = 0;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state == SKELETON_STATE_WALK)
	{
		x += dx;
		y += dy;
		if (EndWalk())
		{
			SetState(SKELETON_STATE_JUMP);
			int r = rand() % 1001;
			if ((r % 2 == 0) || (r % 3 == 0) || (r % 5 == 0))
				ThrowBone(r);
		}
	}
	else
	{
		vy += SKELETON_GRAVITY * dt;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0) vx = 0;
			if (ny < 0)
			{
				if (state == SKELETON_STATE_JUMP)
					SetState(SKELETON_STATE_JUMPBACK);
				else SetState(SKELETON_STATE_WALK);
				int r = rand() % 1001;
				if ((r % 2 == 0) || (r % 3 == 0) || (r % 5 == 0))
					ThrowBone(r);
			}
		}
	}
}

void Skeleton::Render()
{
	if (!isActive) return;
	if (freeze_start == 0)
		animation_set->at(0)->Render(x, y, nx);
	else animation_set->at(0)->FreezeRender(x, y, nx);
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SKELETON_BBOX_WIDTH;
	bottom = y + SKELETON_BBOX_HEIGHT;
}

void Skeleton::ThrowBone(int r)
{
	//Randomize throwing bones
	stop_time = GetTickCount();
	if (r % 2 == 0)
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->enemies_projectiles.push_back(new Bone(x, y, nx, 1));
	if (r % 3 == 0)
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->enemies_projectiles.push_back(new Bone(x, y, nx, 2));
	if (r % 5 == 0)
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->enemies_projectiles.push_back(new Bone(x, y, nx, 3));
}

Skeleton::~Skeleton()
{
}

void Skeleton::SetState(int s)
{
	state = s;
	switch (s)
	{
	case SKELETON_STATE_WALK:
		vy = 0;
		vx = nx * SKELETON_1_SPEEDX;
		break;
	case SKELETON_STATE_JUMP:
		vx = nx * SKELETON_2_SPEEDX;
		vy = -SKELETON_2_SPEEDY;
		break;
	case SKELETON_STATE_JUMPBACK:
		vx = -nx * SKELETON_3_SPEEDX;
		vy = -SKELETON_3_SPEEDY;
		break;
	}
}
