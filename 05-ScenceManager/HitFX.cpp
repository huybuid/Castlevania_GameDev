#include "HitFX.h"


void HitFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD tick = GetTickCount();
	if (tick - fx_start > fx_time)
	{
		isActive = false;
		animation_set->at(state)->SetCurrentFrame();
	}
}

void HitFX::Render()
{
	if (!isActive) return;
	animation_set->at(state)->Render(x, y, nx);
}

HitFX::~HitFX()
{
}
