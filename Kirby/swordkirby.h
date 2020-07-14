#pragma once
#include "GameNode.h"


enum Pl_state
{
	STAY,
	LWALK,
	RWALK,
	RUN,
	SLIDING,

	JUMP = 10,
	JUMPH,
	JUMPHUP,

	JUMPSLASH,
	RAPIDSLASH,
	SWORDSPIN,

};

struct Kir
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir;
	D3DXVECTOR2 rot;
	float speed;
	bool	Jumpkirby;
	float	gravity;
	float Jump;
	float Delta;

	float Skilltime; //continue att
	
};



struct MonsterY
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir;
	D3DXVECTOR2 rot;
	float speed;
	int armor;
	int Hp;
};

struct MonsterZ
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir;
	D3DXVECTOR2 rot;
	float speed;
	int armor;
	int Hp;
};


class swordkirby :public GameNode
{

private:
	float prevkeytime;


	Kir m_player;
	Image* pl;
	Image* pls;
	Image* plj;
	Image* plhj;
	Image* plhjup;
	Image* plr;
	Image* pljs;
	Image* plrs;
	Image* plss;

	bool isLeft;
	
	
	//FRECT KirbyHitbox = RectMake(m_player.)
	//FRECT SwordHitbox = RectMake()

	Pl_state pl_state = STAY;
public:
	swordkirby();
	~swordkirby() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	MAKEREFGET(Kir ,m_player);
};

