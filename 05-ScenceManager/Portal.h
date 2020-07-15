#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 


	int width;
	int height; 
public:
	float simon_x, simon_y;
	int simon_nx, simon_state;
	CPortal(float l, float t, float r, float b, int scene_id, float x, float y, int nx, int state);
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id;  }
};