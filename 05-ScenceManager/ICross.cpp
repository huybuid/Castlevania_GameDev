#include "ICross.h"

void ICross::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->SetWeapon(SIMON_WEAPON_CROSS);
}
