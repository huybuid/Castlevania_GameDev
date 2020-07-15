#include "IAxe.h"

void IAxe::Destroy()
{
		CItem::Destroy();
		CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		simon->SetWeapon(SIMON_WEAPON_AXE);
}
