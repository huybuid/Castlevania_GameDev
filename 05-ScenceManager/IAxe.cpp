#include "IAxe.h"

void IAxe::Destroy()
{
		CItem::Destroy();
		CSimon *simon = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		simon->weapon_indicator = SIMON_WEAPON_AXE;
		simon->weapon_level = 1;
}
