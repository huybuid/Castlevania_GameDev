#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "PlayScence.h"

#define GRID_ROW_MAX	3
#define GRID_COLUMN_MAX 12
#define GRID_CELL_HEIGHT SCREEN_HEIGHT;
#define GRID_CELL_WIDTH SCREEN_WIDTH;

using namespace std;
class CGrid
{
	static CGrid* __instance;
	//vector<LPGAMEOBJECT> listBrick;
	vector<LPGAMEOBJECT> cells[GRID_COLUMN_MAX][GRID_ROW_MAX];
public:
	static CGrid* GetInstance();
	void Insert(int object, int grid_x, int grid_y, float x, float y, float w, float h, int n, int type, int id_item);
	CGameObject* GetNewObject(int object, float x, float y, float w, float h, int n, int type, int id_item);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);
	void Clear();

};