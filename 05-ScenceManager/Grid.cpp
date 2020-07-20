#include "Grid.h"
#include "Brick.h"
#include "FirePillar.h"
#include "Portal.h"
#include "StairBottom.h"
#include "StairTop.h"
#include "Bat.h"
#include "Knight.h"
#include "Platform.h"

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

void CGrid::Insert(CGameObject * object, int grid_x, int grid_y)
{
	if (object == NULL)
		return;
	cells[grid_x][grid_y].push_back(object);
}

CGameObject* CGrid::GetNewObject(int object, float x, float y, float w, float h, int n, int type,  int id_item)
{
	switch (object)
	{
	case GRID_BRICK:
		return new CBrick(x, y, w, h);
	case GRID_PLATFORM:
		return new Platform(x, y, n, w, h);
	case GRID_FIREPILLAR:
		return new FirePillar(x, y, type, id_item);
	case GRID_STAIRTOP:
		return new StairTop(x,y,n);
	case GRID_STAIR_BOTTOM:
		return new StairBottom(x, y, n);
	case GRID_KNIGHT:
		return new Knight(x,y,n,w,h);
	case GRID_BAT:
		return new Bat(x, y, n);
	case GRID_PORTAL:
		return new CPortal(x, y, w, h, type);
	/*case PORTAL: return new CGate(x, y);
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
	/*if ((int)(cam_y) % height == 0 )
	{
		bottom--;
	}*/


	int left = (int)(cam_x) / GRID_CELL_WIDTH;
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
	for (int i = 0; i < GRID_ROW_MAX; i++)
		for (int j = 0; j < GRID_COLUMN_MAX; j++)
			cells[i][j].clear();
}
