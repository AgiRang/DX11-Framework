#include "stdafx.h"
#include "IsoTile.h"


IsoTile::IsoTile()
{
}


IsoTile::~IsoTile()
{
}

HRESULT IsoTile::init()
{
	m_TileDesc.TileSizeX = 100.0f;
	m_TileDesc.TileSizeY = 50.0f;
	m_TileDesc.TileMaxX = 100;
	m_TileDesc.TileMaxY = 100;

	m_TileDesc.ZeroStartPos.x = 0.0f;
	m_TileDesc.ZeroStartPos.y = 0.0f;

	m_Tiles = new ST_ISOTILE*[m_TileDesc.TileMaxX];
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		m_Tiles[i] = new ST_ISOTILE[m_TileDesc.TileMaxY];
	}
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			m_Tiles[i][j].State = ISOTILE_NONE;
			m_Tiles[i][j].pos.x = m_TileDesc.ZeroStartPos.x + (i*m_TileDesc.TileSizeX*0.5f)
				- (j*m_TileDesc.TileSizeX*0.5f);
			m_Tiles[i][j].pos.y = m_TileDesc.ZeroStartPos.y + (i*m_TileDesc.TileSizeY*0.5f)
				+ (j*m_TileDesc.TileSizeY*0.5f);

		}

	}

	m_cc = new Circle(4);
	m_cc->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);

	return S_OK;
}

void IsoTile::release()
{
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		SAFE_DELETE_ARRAY(m_Tiles[i]);
	}
}

void IsoTile::update()
{
	if (KEYMANAGER->isKeyDown('2'))
	{
		SCENEMANAGER->ChangeScene("Tile");
	}
	if (KEYMANAGER->StayKeyDown('W'))
	{
		g_ptCam.y += g_ETime * 120.0f;
	}
	if (KEYMANAGER->StayKeyDown('S'))
	{
		g_ptCam.y -= g_ETime * 120.0f;
	}
	if (KEYMANAGER->StayKeyDown('A'))
	{
		g_ptCam.x -= g_ETime * 120.0f;
	}
	if (KEYMANAGER->StayKeyDown('D'))
	{
		g_ptCam.x += g_ETime * 120.0f;
	}

	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		int idxx, idxy;
		if (PtInIsoTile(idxx, idxy, m_TileDesc, g_ptCam + g_ptMouse))
		{
			if (m_Tiles[idxx][idxy].State == ISOTILE_WALL)
			{
				m_Tiles[idxx][idxy].State = ISOTILE_NONE;
			}
			else
			{
				m_Tiles[idxx][idxy].State = ISOTILE_WALL;
			}
		}

	}



}

void IsoTile::render()
{
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			//화면 밖에 있는 타일은 출력하지않고 넘기기
			if (m_Tiles[i][j].pos.x  <0 +g_ptCam.x - m_TileDesc.TileSizeX*0.5f||
				m_Tiles[i][j].pos.x > WINSIZEX + g_ptCam.x + m_TileDesc.TileSizeX*0.5f ||
				m_Tiles[i][j].pos.y  <0 + g_ptCam.y - m_TileDesc.TileSizeY*0.5f ||
				m_Tiles[i][j].pos.y > WINSIZEY + g_ptCam.y + m_TileDesc.TileSizeY*0.5f
				)
				continue;

			m_cc->SetisFill(false);
			m_cc->Color(0.0f, 0.0f, 0.0f);
			if (m_Tiles[i][j].State == ISOTILE_WALL)
			{
				m_cc->SetisFill(true);
				m_cc->Color(1.0f, 0.0f, 0.0f);
			}
			
			m_cc->Position(m_Tiles[i][j].pos);
			m_cc->Render();
		}

	}
}
