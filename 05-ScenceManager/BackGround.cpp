#include "BackGround.h"
#include "Textures.h"

void Background::Load(int texID)
{
	int k;
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	ifstream inp(path.c_str());
	tiles.clear(); //clear all previous tiles
	inp >> m >> n;
	CSprites * sprites = CSprites::GetInstance();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sprites->Add(BACKGROUND_ID + i * n + j, j * BG_WIDTH, i * BG_HEIGHT, (j + 1) * BG_WIDTH, (i + 1) * BG_HEIGHT, tex);
		}
	}
	inp >> rows >> columns;
	inp >> screen_limit;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			inp >> k;
			ani = new CAnimation();
			ani->Add(BACKGROUND_ID + k);
			tiles.push_back(ani);
		}
	}
	inp.close();
}

void Background::Render(float x, float y)
{
	int n = x / BG_WIDTH;
	int m = y / BG_HEIGHT;
	for (int i = m; i < m + 6; i++)
	{
		if (i >= rows) continue;
		for (int j = n; j < n + 9; j++)
		{
			if (j >= columns) continue;
			if ((i * columns + j) < tiles.size())
				tiles[i * columns + j]->Render(j * BG_HEIGHT, i * BG_WIDTH, -1, 255);
		}
	}
}

void Background::Clear()
{
	tiles.clear();
	path.clear();
}
