#include "Grid.h"
#include "Brick.h"
#include "FirePillar.h"
#include "Portal.h"

CGrid* CGrid::__instance = NULL;

CGrid* CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::Insert(int object, int grid_x, int grid_y, float x, float y, float w, float h, int n, int type, int id_item)
{
	CGameObject* obj = GetNewObject(object, x, y, w, h, n, type, id_item);
	if (obj == NULL)
		return;

	obj->nx= n;
	cells[grid_x][grid_y].push_back(obj);
}

CGameObject* CGrid::GetNewObject(int object, float x, float y, float w, float h, int n, int type,  int id_item)
{
	switch (object)
	{
	case 1:
		return new CBrick(x, y, w, h);
	case 2:
		return new FirePillar(x, y, type, id_item);
	case 50:
		return new CPortal(x, y, w, h, type);
	/*case STAIR_DOWN: return new CHidenObject(x, y, type, trend, -1);
	case STAIR_UP: return new CHidenObject(x, y, type, trend, 1);
	case PORTAL: return new CGate(x, y);
	case PANTHER: return new CPanther(x, y, id_item);
	case FISHMEN: return new CFishman(x, y, id_item);
	case GHOST: return new CGhost(x, y, id_item);
	case BAT: return new CBat(x, y, id_item);
	case MONEY_5: return new CItemMoney(x, y, MONEY_5);*/
	default:
		return NULL;
	}
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y)
{
	ListObj.clear();
	//CScene* scene = CScene::GetInstance();


	int top = (int)(cam_y) / GRID_CELL_HEIGHT;
	int bottom = (int)(cam_y + SCREEN_HEIGHT) / GRID_CELL_HEIGHT;


	int left = (int)(cam_x) / GRID_CELL_WIDTH;
	if (left > 0)left--;
	int right = (int)(cam_x + SCREEN_WIDTH) / GRID_CELL_WIDTH;

	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
		{
			for (auto& k : cells[i][j])
			{
				if (k->isActive)
				{
					ListObj.push_back(k);
				}
			}
		}
	}
}

void CGrid::Clear()
{
	for (int i=0;i<GRID_ROW_MAX;i++)
		delete[] cells[i];
}
