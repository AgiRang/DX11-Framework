#pragma once
#include "GameNode.h"

//타일 상태값은 필요에 따라 더 만들것
enum TILE_STATE
{
	TILE_NONE,
	TILE_WALL,
	TILW_TRAP

};

struct ST_TILECOST
{
	int F;			//총비용 g+h
	int G;			//시작지점에서 부터의 비용
	int H;			//도착지점 까지의 예상 비용
	int prevX;		//전에 왔던 타일 인덱스
	int prevY;		//전에 왔던 타일 인덱스
	bool isCheck;	//검사를 한적이 있는지
};

struct ST_TILE
{
	//나눠지는 이미지에서 어떤 프레임을 가지고 있을지
	int		CurrentFrameX;
	int		CurrentFrameY;

	//이미지가 여러장 필요한 경우 식별하기위한 변수

	string	ImageKey;
	int		MaxFrameX;
	int		MaxFrameY;

	int		State;
};

struct ST_PLAYER
{

	D3DXVECTOR2 pos;




};






class TileMap : public GameNode
{
private:
	//하나씩만 가지고 있을 정보값

	TILE_DESC	m_TileDesc;


	//배열로 저장할 구조체
	ST_TILE**	m_Tiles;

	//길찾기 비용 구조체는 따로 만들어 둔다(타일맵당 1개)
	ST_TILECOST** m_TileCost;

	//목적지 까지의 경로는 플레이어,몬스터 등등 다 한개씩 가지고 있다.
	vector<POINT>	m_playerWay;


	//vector<POINT>	m_EnemyWay;


	int StartIndexX; int StartIndexY; int EndIndexX; int EndIndexY;

	int	MouseIndexX = 0;
	int	MouseIndexY = 0;
	int MouseTileState = TILE_NONE;

	ST_PLAYER m_player;


	//아이소 매트릭 타일
	Circle*  m_isoTile;


public:
	TileMap();
	~TileMap() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	//타일맵 길찾기
	bool astar(vector<POINT>& way, int StartX, int StartY, int EndX, int EndY,int RangeX, int RangeY);

	//현재 타일에서 도착 지점까지 필요한 예상비용
	int FindH(int StartX, int StartY, int EndX, int EndY);
};

