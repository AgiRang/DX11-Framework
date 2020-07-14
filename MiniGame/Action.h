#pragma once
#include "GameNode.h"
class Arka;
#define BULLETMAX 5
#define ENEMYMAX 5

struct ST_PLAYER2
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir;
	D3DXVECTOR3 rot;
	float speed;
	D3DXCOLOR color;
};

struct ST_BULLET
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir;
	float speed;
	bool fire;
	ST_BULLET():fire(false)
	{
	}
	~ST_BULLET()
	{
	}
};

struct ST_ENEMY
{
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Size;
	int Hp;
	int Shape;

	ST_ENEMY() : Hp(3)
	{

	}
};

struct ST_COLLISION
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float angle;
};




class Action :public GameNode
{
private:
	ST_PLAYER2 m_player;
	ST_BULLET* m_bullet;
	ST_ENEMY* m_enemy;
	Image* pl;
	Image* egg;
	Image* pls;
	D3DXVECTOR3 m_angle;
	D3DXVECTOR2 Pos1;
	D3DXVECTOR2 Pos2;

	ST_COLLISION m_collisionBox[2];


public:
	Action();
	~Action() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

