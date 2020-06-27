#include "IHolyWater.h"

void IHolyWater::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->weapon_indicator = SIMON_WEAPON_HOLYWATER;
	simon->weapon_level = 1;
}
