#include "IDagger.h"

void IDagger::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->weapon_indicator = SIMON_WEAPON_DAGGER;
	simon->weapon_level = 1;
}
