#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "PlayScence.h"

#define GRID_ROW_MAX	3
#define GRID_COLUMN_MAX 12
#define GRID_CELL_HEIGHT SCREEN_HEIGHT;
#define GRID_CELL_WIDTH SCREEN_WIDTH;

#define GRID_SIMON			0
#define GRID_BRICK			1
#define GRID_FIREPILLAR		2
#define GRID_STAIRTOP		3
#define GRID_STAIR_BOTTOM	4
#define GRID_PLATFORM		7

#define GRID_KNIGHT			5
#define GRID_BAT			6
#define GRID_ZOMBIE			8
#define GRID_GHOST			9
#define GRID_HUNCHBACK		10
#define GRID_RAVEN			11
#define GRID_SKELETON		12
#define GRID_BOSS			13
#define GRID_PORTAL			50

using namespace std;
class CGrid
{
	static CGrid* __instance;
	//vector<LPGAMEOBJECT> listBrick;
	vector<LPGAMEOBJECT> cells[GRID_COLUMN_MAX][GRID_ROW_MAX];
public:
	static CGrid* GetInstance();
	void Insert(int object, int grid_x, int grid_y, float x, float y, float w, float h, int n, int type, int id_item);
	void Insert(CGameObject *object, int grid_x, int grid_y);
	CGameObject* GetNewObject(int object, float x, float y, float w, float h, int n, int type, int id_item);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);
	void Clear();
	void StopTime();
};