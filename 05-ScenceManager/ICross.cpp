#include "ICross.h"

void ICross::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->weapon_indicator = SIMON_WEAPON_CROSS;
	simon->weapon_level = 1;
}
