#include "Rosary.h"
#include "Grid.h"
#include "Boss.h"
#include "Enemy.h"
#include "FirePillar.h"

void Rosary::Destroy()
{
	CItem::Destroy();
	vector <LPGAMEOBJECT> grid;
	float cam_x, cam_y=0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	CGrid::GetInstance()->GetListObject(grid, cam_x,cam_y);
	for (size_t i = 0; i < grid.size(); i++)
	{
		if (grid[i]->x >= cam_x && grid[i]->x<= cam_x + SCREEN_WIDTH && dynamic_cast<CEnemy *>(grid[i]))
		{
			//Rosary doesn't work on Boss!
			if (!dynamic_cast<Boss *>(grid[i]) && !dynamic_cast<FirePillar *>(grid[i]))
				dynamic_cast<CEnemy *>(grid[i])->Destroy();
		}
	}
}
