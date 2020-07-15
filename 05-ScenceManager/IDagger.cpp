#include "IDagger.h"

void IDagger::Destroy()
{
	CItem::Destroy();
	CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	simon->SetWeapon(SIMON_WEAPON_DAGGER);
}
