#pragma once
#include "BackGround.h"
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Simon.h"

#define CAM_X_SETVALUE	160

class CPlayScene: public CScene
{
protected: 
	//CMario *player;					
	// A play scene has to have player, right? 
	CSimon * player;
	Background background;
	

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_BACKGROUND(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	CSimon * GetPlayer() { return player; };
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

