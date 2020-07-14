#pragma once
#include"GameNode.h"


enum gunter_state
{
	GIDLE,
	GLWALK,
	GRWALK,
	GHIT,
	GFLIP,
	GDIE,
	GATT,

};

	struct MonsterX
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 dir;
		D3DXVECTOR2 rot;
		float speed;
		int armor;
		int Hp;
	};
class Monster :public GameNode
{

public:
	MonsterX gunter;
	Image * monster3att;
	Image * monster3die;
	Image * monster3flip;
	Image * monster3hit;
	Image * monster3idle;
	Image * monster3walk;

	bool m_isLeft;

	gunter_state gunter_state = GIDLE;

	Monster();
	~Monster()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	MAKEREFGET(MonsterX, gunter);
};

