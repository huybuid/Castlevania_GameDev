#include "Boss.h"
#include "Simon.h"
#include "PlayScence.h"
#include "Fireball.h"
#include <time.h>
#include "HitFX.h"
#include "Orb.h"

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD tick = GetTickCount();
	if (tick - die_start > FX_TIME_LONG && die_start > 0)
	{
		die_start = 0;
		CItem *item = new Orb(ORB_SPAWN_X, ORB_SPAWN_Y);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->items.push_back(item);
	}
	if (!isActive) return;
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
	float simon_x, simon_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(simon_x, simon_y);
	if (simon_x >= BOSS_TRIGGER)
		trigger = false;
	if (trigger)
	{
		return;
	}
		if (tick - attack_start >= BOSS_TIME_ATTACK && fly_start == 0)
		{
			attack_start = GetTickCount();
			if (x < simon_x)
			{
				nx = 1;
			}
			else
			{
				nx = -1;
			}
			if (curve_start > 0)
				curve_start += BOSS_TIME_ATTACK2;
			state = BOSS_STATE_ATTACK;
			vx = vy = 0;
			Fireball *ball = new Fireball(x + BOSS_BBOX_WIDTH / 2, y + BOSS_BBOX_HEIGHT / 2, nx);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->enemies_projectiles.push_back(ball);
			return;
		}
		if (state == BOSS_STATE_ATTACK)
		{
			if (tick - attack_start > BOSS_TIME_ATTACK2)
			{
				state = BOSS_STATE_FLY;
				if (vx == 0)
					vx = BOSS_SPEED_AUTO_FLY_X / 2;
				if (vy == 0)
					vy = BOSS_SPEED_AUTO_FLY_Y / 2;
			}
		}
		if (state == BOSS_STATE_FLY)
		{
			if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)
			{
				SetFly();
			}
			if (fly_start > 0)
			{
				if (tick - fly_start > BOSS_TIME_CHECK_FLY)
				{
					SetFly();

				}
				else
				{

					if (x > start_x)
					{
						if (abs(x - BOSS_RANDOM_X1) > 2 && abs(y - BOSS_RANDOM_Y1) > 2) // 
							FlyStraight(BOSS_RANDOM_X1, BOSS_RANDOM_Y1);
						else
							vx = vy = 0;
					}
					else
					{
						if (abs(x - BOSS_RANDOM_X2) > 2 && abs(y - BOSS_RANDOM_Y2) > 2) // 
							FlyStraight(BOSS_RANDOM_X2, BOSS_RANDOM_Y2);
						else
							vx = vy = 0;
					}
					x += vx * dt * 0.3f;
					y += vy * dt * 0.3f;

				}
			}


			if (!fly_start) {
				if (type == 0)
				{
					if (curve_start > 0)
					{
						step = 1;
						float t = tick - curve_start;
						if (t < 2000)
						{
							float xa, xb, ya, yb;
							xa = getPt(x0, x1, t * 0.0005f);
							ya = getPt(y0, y1, t * 0.0005f);
							xb = getPt(x1, x2, t * 0.0005f);
							yb = getPt(y1, y2, t * 0.0005f);

							x = SIMON_STANDING_BBOX_HEIGHT / 2 + getPt(xa, xb, t * 0.0005f);
							y = getPt(ya, yb, t * 0.0005f);
							if (vy > 0)
							{
								if (abs(x - x1) < 2.0f)
									vy = -0.4f;
							}

						}
						else
						{
							curve_start = 0;
							fly_start = GetTickCount();
							step = 0;
						}
					}
				}
				else
				{

					if (step == 0)
					{
						if (abs(x - x1) > 2 && abs(y - y1) > 2) // 
						{
							FlyStraight(x1, y1);
						}
						else
						{
							step = 1;
							vy = -vy;
						}
					}
					else if (step == 1)
					{
						if (abs(x - x2) > 2 && abs(y - y2) > 2) // 
						{

							FlyStraight(x2, y2);

						}
						else
						{
							step = 2;
						}
					}
					else
					{
						step = 0;
						fly_start = GetTickCount();
					}
					float cam_x, cam_y;
					CGame::GetInstance()->GetCamPos(cam_x, cam_y);
					if ((x <= cam_x && vx < 0)
						|| (vx > 0 && x >= cam_x + SCREEN_WIDTH - BOSS_BBOX_WIDTH))
						vx = -vx;
					if ((y <= BOSS_BBOX_WIDTH && vy < 0) || (y >= SCREEN_HEIGHT - BOSS_BBOX_WIDTH && vy > 0))
						vy = -vy;
					x += vx * dt;
					y += vy * dt;
				}
			}
		}
}

void Boss::Render()
{
	int ani = (state == BOSS_STATE_IDLE) ? BOSS_ANI_IDLE : BOSS_ANI_FLY;
	if (!isActive) return;
	if (damage_start == 0)
		animation_set->at(ani)->Render(x, y, nx);
	else animation_set->at(ani)->FreezeRender(x, y, nx);
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BOSS_BBOX_WIDTH;
	bottom = top + BOSS_BBOX_HEIGHT;
}

void Boss::AutoFly(float next_x, float next_y)
{
	x0 = x;
	y0 = y;
	x2 = next_x;
	y2 = next_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(x1, y1);
	y1 += SIMON_STANDING_BBOX_HEIGHT / 2;
	if (x < next_x)
		vx = BOSS_SPEED_AUTO_FLY_X;
	else
		vx = -BOSS_SPEED_AUTO_FLY_X;
	vy = BOSS_SPEED_AUTO_FLY_Y;

}
void Boss::AutoAttack(float next_x, float next_y)
{
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(x1, y1);
	x2 = next_x;
	y2 = next_y + SIMON_STANDING_BBOX_HEIGHT / 2;
}
void Boss::FlyStraight(float next_x, float next_y)
{

	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}
	if (next_x != x && next_y != y)
		SetSpeed(FIREBALL_SPEED * nx, 1.0 * (next_y - y) / (next_x - x) * nx * FIREBALL_SPEED);

}
void Boss::FlyCurve(float next_x, float next_y)
{
	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}

	//vy += 0.001f;
}
float Boss::getPt(int n1, int n2, float perc)
{
	int diff = n2 - n1;

	return n1 + (diff * perc);
}
void Boss::SetFly()
{
	fly_start = 0;
	int _type;
	srand((unsigned)time(0));
	_type = rand() % 3;

	if (_type == 2)
		type = 1;
	else
		type = 0;
	float c_x, c_y;
	CGame::GetInstance()->GetCamPos(c_x, c_y);

	if (type == 0)
	{
		curve_start = GetTickCount();

		srand((unsigned)time(0));
		_type = rand() % 2;
		float s_x, s_y;
		if (_type == 0)
		{
			if (x < c_x + BOSS_BBOX_WIDTH * 3 / 2)
				s_x = x + BOSS_BBOX_WIDTH * 3 / 2;
			else
				s_x = x - BOSS_BBOX_WIDTH * 3 / 2;
		}
		else
		{
			if (x < c_x + BOSS_BBOX_WIDTH / 2)
				s_x = x + SCREEN_WIDTH - BOSS_BBOX_WIDTH * 3 / 2;
			else if (x > c_x + SCREEN_WIDTH - BOSS_BBOX_WIDTH)
				s_x = x - (SCREEN_WIDTH - BOSS_BBOX_WIDTH);
			else if (x < c_x + BOSS_BBOX_WIDTH * 3 / 2)
				s_x = x + BOSS_BBOX_WIDTH * 3 / 2;
			else
				s_x = x - BOSS_BBOX_WIDTH * 3 / 2;
		}
		srand((unsigned)time(0));
		_type = rand() % 2;
		if (_type == 0)
		{
			if (y < c_y + BOSS_BBOX_WIDTH * 3 / 2)
				s_y = y + BOSS_BBOX_WIDTH / 2;
			else
				s_y = y - BOSS_BBOX_WIDTH / 2;
		}
		else
		{
			if (y > c_y + SCREEN_WIDTH - BOSS_BBOX_WIDTH)
				s_y = y - BOSS_BBOX_WIDTH;
			else
				s_y = y + BOSS_BBOX_WIDTH;
		}
		AutoFly(s_x, y);
	}
	else
	{
		if (x < c_x + BOSS_BBOX_WIDTH * 2)
			AutoAttack(x + BOSS_BBOX_WIDTH / 2, y);
		else
			AutoAttack(x - BOSS_BBOX_WIDTH / 2, y);
	}
}

void Boss::Destroy()
{
	isActive = 0;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x, y, 1, true));
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x+8, y, 1, true));
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x+16, y, 1, true));
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x, y+16, 1, true));
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x+8, y+16, 1, true));
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->effects.push_back(new HitFX(x+16, y+16, 1, true));
	die_start = GetTickCount();
}

Boss::~Boss()
{
}
