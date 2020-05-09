#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include <iostream>
#include <fstream>

using namespace std;

#define BG_WIDTH  32
#define BG_HEIGHT 32
#define MAP_COLUMNS 24
#define MAP_ROWS 6
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BACKGROUND_ID 5000

class Background
{
	int m, n;
	static Background * __instance;
public:
	vector<LPANIMATION> tiles;
	string path;
	void SetPath(string s)
	{
		path = s;
	}
	void Load(int texID);
	void Render(float x, float y);
	void Clear();
};