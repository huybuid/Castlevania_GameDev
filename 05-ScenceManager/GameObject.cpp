#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Item.h"

CGameObject::CGameObject()
{
	isActive = true;
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!coObjects->at(i)->isActive || !coObjects->at(i)->isCollidable) continue; //if object is not active or can't be colided, continue
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::CalcPotentialInteractions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &inEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!coObjects->at(i)->isActive || !coObjects->at(i)->isInteractive) continue; //if object is not active or can't be colided, continue
		LPCOLLISIONEVENT e;
		bool b = isAABB(coObjects->at(i));
		if (b)
		{
			e = AABB(coObjects->at(i));
		}
		else
		{
			e = SweptAABBEx(coObjects->at(i));
		}
		if (e->t > 0 && e->t <= 1.0f)
			inEvents.push_back(e);
		else
			delete e;
	}

	std::sort(inEvents.begin(), inEvents.end(), CCollisionEvent::compare);
}

void CGameObject::CollisionsWithEnemies(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &inEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!coObjects->at(i)->isActive || !coObjects->at(i)->isEnemy) continue; //if object is not active or can't be colided, continue
		LPCOLLISIONEVENT e;
		bool b = isAABB(coObjects->at(i));
		if (b)
		{
			e = AABB(coObjects->at(i));
		}
		else
		{
			e = SweptAABBEx(coObjects->at(i));
		}
		if (e->t > 0 && e->t <= 1.0f)
			inEvents.push_back(e);
		else
			delete e;
	}

	std::sort(inEvents.begin(), inEvents.end(), CCollisionEvent::compare);
}

/*void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny, float &rdx, float &rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}*/

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny, float &rdx, float &rdy) //To see which object collides with current object first
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}

LPCOLLISIONEVENT CGameObject::AABB(LPGAMEOBJECT obj)
{
	float tt, tl, tb, tr;
	this->GetBoundingBox(tl, tt, tr, tb);
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	float time = -1;
	int nx, ny;
	if (tl >= r || l >= tr || tt >= b || t >= tb)
	{
		nx = 0;
		ny = 0;
	}
	else
	{
		time = 0.00000001f;
		if (tl < l)
			nx = -1;
		else
			nx = 1;
		if (tb < b)
			ny = -1;
		else
			ny = 1;
	}
	return new CCollisionEvent(time,nx,ny,0,0,obj);
}

bool CGameObject::isAABB(LPGAMEOBJECT obj)
{
	float tt, tl, tb, tr;
	this->GetBoundingBox(tl, tt, tr, tb);
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);
	if (tl >= r || l >= tr)
		return false;

	// If one rectangle is above other 
	if (tt >= b || t >= tb)
		return false;
	return true;
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 100);
}


CGameObject::~CGameObject()
{
}