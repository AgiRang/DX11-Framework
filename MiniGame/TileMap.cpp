#include "stdafx.h"
#include "TileMap.h"
#include <fstream>

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

HRESULT TileMap::init()
{
	//임의의 초기값 만들어 주기
	m_TileDesc.TileMaxX = 1000;
	m_TileDesc.TileMaxY = 1000;
	m_TileDesc.TileSizeX = 50.0f;
	m_TileDesc.TileSizeY = 50.0f;
	m_TileDesc.ZeroStartPos.x = 0.0f;
	m_TileDesc.ZeroStartPos.y = 0.0f;

	m_player.pos.x = 0.0f;
	m_player.pos.y = 0.0f;



	//m_Tiles 는 더블포인터
	m_Tiles = new ST_TILE*[m_TileDesc.TileMaxX];
	m_TileCost = new ST_TILECOST*[m_TileDesc.TileMaxX];
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		//m_Tiles[i] 는 포인터
		m_Tiles[i] = new ST_TILE[m_TileDesc.TileMaxY];
		m_TileCost[i] = new ST_TILECOST[m_TileDesc.TileMaxY];
	}

	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			m_Tiles[i][j].CurrentFrameX = GetInt(20);
			m_Tiles[i][j].CurrentFrameY = GetInt(8);
			m_Tiles[i][j].ImageKey = "TILE";
			m_Tiles[i][j].MaxFrameX = 20;
			m_Tiles[i][j].MaxFrameY = 8;
			m_Tiles[i][j].State = TILE_NONE;
		}
	}

	//테스트 아이소 용

	m_isoTile = new Circle(4);

	return S_OK;
}

void TileMap::release()
{
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		//m_TileCost[i] = new ST_TILECOST[m_TileDesc.TileMaxY];
		SAFE_DELETE_ARRAY(m_Tiles[i]);
		SAFE_DELETE_ARRAY(m_TileCost[i]);
	}
}

void TileMap::update()
{

	if (KEYMANAGER->isKeyDown('1'))
{
	SCENEMANAGER->ChangeScene("Iso");
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
	int idxx, idxy;
	int idxx2, idxy2;

	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		
		if (PtInTile(idxx, idxy, m_TileDesc,g_ptMouse+g_ptCam))
		{
			m_Tiles[idxx][idxy].State = MouseTileState;
			m_Tiles[idxx][idxy].CurrentFrameX = MouseIndexX;
			m_Tiles[idxx][idxy].CurrentFrameY = MouseIndexY;
		}
	}

	if (KEYMANAGER->isKeyDown(VK_RBUTTON))
	{
		if (PtInTile(idxx, idxy, m_TileDesc, m_player.pos))
		{
			if (PtInTile(idxx2, idxy2, m_TileDesc, g_ptMouse + g_ptCam))
			{
				astar(m_playerWay, idxx, idxy, idxx2, idxy2, 10, 10);
			}
		}
	}
	//벡터 사이즈가 0보다 크다면 움직일 길이 존재
	if (m_playerWay.size() > 0)
	{
		D3DXVECTOR2 dest;
		dest.x = m_TileDesc.ZeroStartPos.x + m_playerWay.back().x *m_TileDesc.TileSizeX;
		dest.y = m_TileDesc.ZeroStartPos.y + m_playerWay.back().y *m_TileDesc.TileSizeY;

		//m_player.pos -> dest 로 이동
		//D3DXVECTOR2 temp;
		//D3DXVec2Normalize(&temp, &(dest - m_player.pos));
		//m_player.pos += temp * g_ETime*160.0f;

		//선형 보간
		D3DXVec2Lerp(&m_player.pos, &m_player.pos, &dest, g_ETime*6.0f);



		//거리가 가까워 지면 길벡터에서 끝을 빼준다.
		if (GetDistance(m_player.pos.x, m_player.pos.y,dest.x,dest.y)<2.0f)
		{
			m_playerWay.pop_back();
		}



	}




	if (KEYMANAGER->StayKeyDown(VK_LEFT))
	{
		if (PtInTile(idxx, idxy, m_TileDesc, D3DXVECTOR2 (m_player.pos.x-25.0f, m_player.pos.y +20.0f)))
		{
			if (PtInTile(idxx2, idxy2, m_TileDesc, D3DXVECTOR2(m_player.pos.x - 25.0f, m_player.pos.y - 20.0f)))
			{
				if (m_Tiles[idxx][idxy].State != TILE_WALL&& m_Tiles[idxx2][idxy2].State != TILE_WALL)
					m_player.pos.x -= g_ETime * 160.0f;
			}
			
			
		}
		
	}
	else if (KEYMANAGER->StayKeyDown(VK_RIGHT))
	{
		if (PtInTile(idxx, idxy, m_TileDesc, D3DXVECTOR2(m_player.pos.x + 25.0f, m_player.pos.y)))
		{
			if (m_Tiles[idxx][idxy].State != TILE_WALL)
			m_player.pos.x += g_ETime * 160.0f;
		}
	}
	if (KEYMANAGER->StayKeyDown(VK_UP))
	{
		if (PtInTile(idxx, idxy, m_TileDesc, D3DXVECTOR2(m_player.pos.x, m_player.pos.y + 25.0f)))
		{
			if (m_Tiles[idxx][idxy].State != TILE_WALL)
			m_player.pos.y += g_ETime * 160.0f;
		}
	}
	else if (KEYMANAGER->StayKeyDown(VK_DOWN))
	{
		if (PtInTile(idxx, idxy, m_TileDesc, D3DXVECTOR2(m_player.pos.x , m_player.pos.y - 25.0f)))
		{
			if (m_Tiles[idxx][idxy].State != TILE_WALL)
			m_player.pos.y -= g_ETime * 160.0f;
		}
	}

}

void TileMap::render()
{
	ImGui::InputInt("indexX", &MouseIndexX);
	ImGui::InputInt("indexY", &MouseIndexY);
	ImGui::InputInt("MouseTileState", &MouseTileState);
	ImGui::SliderFloat2("ZeroPos", m_TileDesc.ZeroStartPos,-300,300);

	if (ImGui::Button("save"))
	{
		ofstream out;
		out.open("save/hi.txt", ios::out | ios::trunc);

		if (out.is_open())
		{
			out << m_TileDesc.TileMaxX << ' ' << m_TileDesc.TileMaxY << endl;
			out << m_TileDesc.TileSizeX << ' ' << m_TileDesc.TileSizeY << endl;
			out << m_TileDesc.ZeroStartPos.x << ' ' << m_TileDesc.ZeroStartPos.y << endl;

			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					out << m_Tiles[i][j].CurrentFrameX << ' ' << m_Tiles[i][j].CurrentFrameY << endl;
					out << m_Tiles[i][j].MaxFrameX << ' ' << m_Tiles[i][j].MaxFrameY << endl;
					out << m_Tiles[i][j].State << ' ' << m_Tiles[i][j].ImageKey << endl;

				}
			}
			out.flush();
			out.close();
		}
	}

	if (ImGui::Button("load"))
	{
		ifstream in;

		in.open("save/hi.txt", ios::in);
		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;

			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].CurrentFrameX >> m_Tiles[i][j].CurrentFrameY;
					in >> m_Tiles[i][j].MaxFrameX >>m_Tiles[i][j].MaxFrameY;
					in >> m_Tiles[i][j].State >> m_Tiles[i][j].ImageKey;

				}
			}

			in.clear();
			in.close();


		}


	}

	// 0,0  WINSIZEX WINSIZEY 두점 좌표의 인덱스 구하기
	PtInTile(StartIndexX, StartIndexY, m_TileDesc, D3DXVECTOR2(0.0f+g_ptCam.x, 0.0f + g_ptCam.y));
	PtInTile(EndIndexX, EndIndexY, m_TileDesc, D3DXVECTOR2(WINSIZEX + g_ptCam.x, WINSIZEY+g_ptCam.y));

	StartIndexX = max(0, StartIndexX);
	StartIndexX = min(m_TileDesc.TileMaxX-1, StartIndexX);

	StartIndexY = max(0, StartIndexY);
	StartIndexY = min(m_TileDesc.TileMaxY - 1, StartIndexY);

	EndIndexX = max(0, EndIndexX);
	EndIndexX = min(m_TileDesc.TileMaxX - 1, EndIndexX);
	
	EndIndexY = max(0, EndIndexY);
	EndIndexY = min(m_TileDesc.TileMaxY - 1, EndIndexY);

	//0번의 키값을 저장
	string prevkey = m_Tiles[0][0].ImageKey;
	Image* img = IMGMANAGER->GetImage(prevkey);
	img->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);
	img->GetRefmaxFrameX() = m_Tiles[0][0].MaxFrameX;
	img->GetRefmaxFrameY() = m_Tiles[0][0].MaxFrameY;



	for (int i = StartIndexX; i < EndIndexX+1; i++)
	{
		for (int j = StartIndexY; j < EndIndexY+1; j++)
		{
			//전에 그린 이미지와 그리려는 이미지가 키값이 다른경우
			if (prevkey != m_Tiles[i][j].ImageKey)
			{
				img = IMGMANAGER->GetImage(m_Tiles[i][j].ImageKey);
				img->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);
				img->GetRefmaxFrameX() = m_Tiles[i][j].MaxFrameX;
				img->GetRefmaxFrameY() = m_Tiles[i][j].MaxFrameY;
			}
			img->GetRefCurrentFrameX() = m_Tiles[i][j].CurrentFrameX;
			img->GetRefCurrentFrameY() = m_Tiles[i][j].CurrentFrameY;
			img->Position(m_TileDesc.ZeroStartPos.x + i * m_TileDesc.TileSizeX,
				m_TileDesc.ZeroStartPos.y + j * m_TileDesc.TileSizeY);
			int idxX, idxY;
			img->Color(0.0f, 0.0f, 0.0f);
			if (PtInTile(idxX, idxY, m_TileDesc, g_ptMouse + g_ptCam))
			{
				if(idxX==i&& idxY==j)
				img->Color(0.5f, 0.0f, 0.0f);
			}
			if (m_Tiles[i][j].State == TILE_WALL)
			{
				img->Color(0.8f, 0.0f, 0.8f);
			}


			img->Render();
		}

	}
	img = IMGMANAGER->GetImage("egg");
	img->Scale(50.0f, 50.0f);
	img->Position(m_player.pos);
	img->Render();


	//테스트 아이소 용
	m_isoTile->SetisFill(false);
	m_isoTile->Scale(100, 50);
	m_isoTile->Position(-200, 200);
	m_isoTile->Render();
}

bool TileMap::astar(vector<POINT>& way, int StartX, int StartY, int EndX, int EndY, int RangeX, int RangeY)
{
	if (StartX == EndX && StartY == EndY || m_Tiles[EndX][EndY].State == TILE_WALL)
	{
		way.clear();
		way.shrink_to_fit();
		return false;

	}




	int MinIndexX;
	int MaxIndexX;
	int MinIndexY;
	int MaxIndexY;
	//
	if (StartX < EndX)
	{
		MinIndexX = StartX - RangeX;
		MaxIndexX = EndX + RangeX;
	}
	else
	{
		MinIndexX = EndX - RangeX;
		MaxIndexX = StartX + RangeX;
	}
	if (StartY < EndY)
	{
		MinIndexY = StartY - RangeY;
		MaxIndexY = EndY + RangeY;
	}
	else
	{
		MinIndexY = EndY - RangeY;
		MaxIndexY = StartY + RangeY;
	}

	MinIndexX = max(0, MinIndexX);
	MinIndexY = max(0, MinIndexY);
	MaxIndexX = min(m_TileDesc.TileMaxX - 1, MaxIndexX);
	MaxIndexY = min(m_TileDesc.TileMaxY - 1, MaxIndexY);

	//기존 벡터에 내용 전부 삭제
	way.clear();
	way.shrink_to_fit();
	//타일비용도 전부 초기화
	for (int i = MinIndexX; i < MaxIndexX+1; i++)
	{
		for (int j = MinIndexY; j < MaxIndexY+1;j++)
		{
			m_TileCost[i][j].isCheck = false;
			m_TileCost[i][j].F = INT32_MAX;
			m_TileCost[i][j].G = INT32_MAX;
			m_TileCost[i][j].H = FindH(i, j, EndX, EndY);
			m_TileCost[i][j].prevX = INT32_MAX;
			m_TileCost[i][j].prevY = INT32_MAX;
		}

	}
	//시작지점은 g값이 0
	m_TileCost[StartX][StartY].G = 0;


	int Count = 0;

	while (1)
	{
		//타일을 다돌아도 탐색이 안끝났다면 종료
		if (Count == (MaxIndexX- MinIndexX)*(MaxIndexY- MinIndexY))
		{
			way.clear();
			way.shrink_to_fit();
			return false;
		}
		Count++;

		//타일의 g값이 갱신된 상황이라면 F값 만들어주기
		for (int i = MinIndexX; i < MaxIndexX + 1; i++)
		{
			for (int j = MinIndexY; j < MaxIndexY + 1; j++)
			{
				if (m_TileCost[i][j].G != INT32_MAX)
					m_TileCost[i][j].F = m_TileCost[i][j].G + m_TileCost[i][j].H;
			}
		}

		//f의 최소값을 구한다
		POINT MinIndex;
		int MinF = INT32_MAX;
		for (int i = MinIndexX; i < MaxIndexX + 1; i++)
		{
			for (int j = MinIndexY; j < MaxIndexY + 1; j++)
			{
				if (m_Tiles[i][j].State != TILE_WALL && !m_TileCost[i][j].isCheck)
				{
					if (m_TileCost[i][j].F < MinF)
					{
						MinIndex.x = i; MinIndex.y= j;
						MinF = m_TileCost[i][j].F;
					}
				}
			}

		}

		//탐색 했을때 F최소값타일이 도착지점이였다면 길을 찾았으니 종료
		if (MinIndex.x == EndX && MinIndex.y == EndY)break;

		//최소값 f 가 없는경우
		if (MinF == INT32_MAX)
		{
			way.clear();
			way.shrink_to_fit();
			return false;
		}


		//최소값 f 주변에 g값 갱신
		//타일 왼쪽
		if (MinIndex.x != 0)
		{
			if (m_TileCost[MinIndex.x - 1][MinIndex.y].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x - 1][MinIndex.y].G = 10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x - 1][MinIndex.y].prevX = MinIndex.x;
				m_TileCost[MinIndex.x - 1][MinIndex.y].prevY = MinIndex.y;
			}

		}
		//타일 오른쪽ㅇ
		if (MinIndex.x != m_TileDesc.TileMaxX-1)
		{
			if (m_TileCost[MinIndex.x + 1][MinIndex.y].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x + 1][MinIndex.y].G = 10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x + 1][MinIndex.y].prevX = MinIndex.x;
				m_TileCost[MinIndex.x + 1][MinIndex.y].prevY = MinIndex.y;
			}

		}
		//타일 아래쪽
		if (MinIndex.y != 0)
		{
			if (m_TileCost[MinIndex.x ][MinIndex.y - 1].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x ][MinIndex.y - 1].G = 10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x][MinIndex.y - 1].prevX = MinIndex.x;
				m_TileCost[MinIndex.x][MinIndex.y - 1].prevY = MinIndex.y;
			}

		}
		//타일 위쪽
		if (MinIndex.y != m_TileDesc.TileMaxY - 1)
		{
			if (m_TileCost[MinIndex.x][MinIndex.y + 1].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x][MinIndex.y + 1].G = 10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x][MinIndex.y + 1].prevX = MinIndex.x;
				m_TileCost[MinIndex.x][MinIndex.y + 1].prevY = MinIndex.y;
			}

		}
		//대각선 스킵

		m_TileCost[MinIndex.x][MinIndex.y].isCheck = true;

	}
	//도착지점 부터 길 찾아가기(시작지점 까지)
	POINT temp;
	temp.x = EndX;
	temp.y = EndY;
	way.emplace_back(temp);
	while (1)
	{
		POINT temp2;
		temp2.x = m_TileCost[temp.x][temp.y].prevX;
		temp2.y = m_TileCost[temp.x][temp.y].prevY;

		if (temp2.x == StartX && temp2.y == StartY)break;
		way.emplace_back(temp2);
		temp.x = temp2.x;
		temp.y = temp2.y;
	}
	return true;
}

int TileMap::FindH(int StartX, int StartY, int EndX, int EndY)
{
	return (abs(StartX- EndX) + abs(StartY - EndY))*10;
}
