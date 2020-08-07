#pragma once
#include "BackGround.h"
#include "Game.h"
#include "Item.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"

#define CAM_X_SETVALUE	160
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 240

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	CSimon * player;
	Background background;
	
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_BACKGROUND(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	vector<LPGAMEOBJECT> weapons;
	vector<LPGAMEOBJECT> enemies_projectiles;
	vector<LPGAMEOBJECT> effects;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	CSimon * GetPlayer() { return player; };
	void SetPlayer(CSimon *s) 
	{ if (s!=NULL) 
		player = new CSimon(s); 
	};
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

