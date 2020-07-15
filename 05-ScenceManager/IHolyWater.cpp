#include "IHolyWater.h"

void IHolyWater::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->SetWeapon(SIMON_WEAPON_HOLYWATER);
}
