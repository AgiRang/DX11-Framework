#pragma once
#include "GameNode.h"

//Ÿ�� ���°��� �ʿ信 ���� �� �����
enum TILE_STATE
{
	TILE_NONE,
	TILE_WALL,
	TILW_TRAP

};

struct ST_TILECOST
{
	int F;			//�Ѻ�� g+h
	int G;			//������������ ������ ���
	int H;			//�������� ������ ���� ���
	int prevX;		//���� �Դ� Ÿ�� �ε���
	int prevY;		//���� �Դ� Ÿ�� �ε���
	bool isCheck;	//�˻縦 ������ �ִ���
};

struct ST_TILE
{
	//�������� �̹������� � �������� ������ ������
	int		CurrentFrameX;
	int		CurrentFrameY;

	//�̹����� ������ �ʿ��� ��� �ĺ��ϱ����� ����

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
	//�ϳ����� ������ ���� ������

	TILE_DESC	m_TileDesc;


	//�迭�� ������ ����ü
	ST_TILE**	m_Tiles;

	//��ã�� ��� ����ü�� ���� ����� �д�(Ÿ�ϸʴ� 1��)
	ST_TILECOST** m_TileCost;

	//������ ������ ��δ� �÷��̾�,���� ��� �� �Ѱ��� ������ �ִ�.
	vector<POINT>	m_playerWay;


	//vector<POINT>	m_EnemyWay;


	int StartIndexX; int StartIndexY; int EndIndexX; int EndIndexY;

	int	MouseIndexX = 0;
	int	MouseIndexY = 0;
	int MouseTileState = TILE_NONE;

	ST_PLAYER m_player;


	//���̼� ��Ʈ�� Ÿ��
	Circle*  m_isoTile;


public:
	TileMap();
	~TileMap() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	//Ÿ�ϸ� ��ã��
	bool astar(vector<POINT>& way, int StartX, int StartY, int EndX, int EndY,int RangeX, int RangeY);

	//���� Ÿ�Ͽ��� ���� �������� �ʿ��� ������
	int FindH(int StartX, int StartY, int EndX, int EndY);
};

