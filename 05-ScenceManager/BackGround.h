#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include <iostream>
#include <fstream>

using namespace std;

#define BG_WIDTH  32
#define BG_HEIGHT 32
#define BACKGROUND_ID 5000

class Background
{
	int m, n;
	int rows, columns;
public:
	vector<LPANIMATION> tiles;
	string path;
	float screen_limit;
	void SetPath(string s)
	{
		path = s;
	}
	void Load(int texID);
	void Render(float x, float y);
	void Clear();
};