#pragma once
#include "GameNode.h"

enum ISOTILE_STATE
{
	ISOTILE_NONE,
	ISOTILE_WALL


};

struct ST_ISOTILE
{
	int State;
	D3DXVECTOR2 pos;


};


class IsoTile :public GameNode
{
private:
	ST_ISOTILE**	m_Tiles;
	TILE_DESC		m_TileDesc;
	Circle*			m_cc;

public:
	IsoTile();
	~IsoTile() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

