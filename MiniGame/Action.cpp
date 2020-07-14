#include "stdafx.h"
#include "Action.h"
#include "Arka.h"
#include <fstream>

Action::Action()
{
}


Action::~Action()
{
}

HRESULT Action::init()
{
	
	pl = IMGMANAGER->GetImage("player");
	pls = IMGMANAGER->GetImage("player_s");
	egg = IMGMANAGER->GetImage("egg");
	m_player.pos.x = 100.5f;
	m_player.pos.y = 100.5f;
	m_player.speed = 100.0f;


	m_player.color.r = 0.0f;
	m_player.color.g = 0.0f;
	m_player.color.b = 0.0f;
	m_player.color.a = 1.0f;

	ZeroMemory(&m_angle, sizeof(m_angle));
	ZeroMemory(&m_player.rot, sizeof(m_player.rot));

	m_bullet = new ST_BULLET[BULLETMAX];

	m_enemy = new ST_ENEMY[ENEMYMAX];

	m_enemy[0].Pos = D3DXVECTOR2(200, 500);
	m_enemy[0].Size = D3DXVECTOR2(100, 100);
	
	m_enemy[1].Pos = D3DXVECTOR2(500, 500);
	m_enemy[1].Size = D3DXVECTOR2(100, 100);

	m_enemy[2].Pos = D3DXVECTOR2(200, 500);
	m_enemy[2].Size = D3DXVECTOR2(100, 100);

	m_enemy[3].Pos = D3DXVECTOR2(500, 500);
	m_enemy[3].Size = D3DXVECTOR2(100, 100);

	m_enemy[4].Pos = D3DXVECTOR2(400, 400);
	m_enemy[4].Size = D3DXVECTOR2(100, 100);

	m_collisionBox[0].angle = 30.0f * TORADIAN;
	m_collisionBox[0].pos = D3DXVECTOR2(400.0f, 300.0f);
	m_collisionBox[0].size = D3DXVECTOR2(100.0f, 150.0f);

	m_collisionBox[1].angle = 0.0f;
	m_collisionBox[1].size = D3DXVECTOR2(150.0f, 70.0f);


	return S_OK;
}

void Action::release()
{
	SAFE_DELETE_ARRAY(m_bullet);
	SAFE_DELETE_ARRAY(m_enemy);
}

void Action::update()
{
	//save
	if (KEYMANAGER->isKeyDown('O'))
	{
		ofstream out; //쓰기용
		out.open("save/hi.save", ios::out | ios::trunc);
		char str[128];
		//경로 디렉토리가 존재하면 파일이 없어도 생성된다.
		if (out.is_open())
		{
			//sprintf_s(str, "m_enemy[0].Hp: %d", m_enemy[0].Hp);
			//out << str<< endl;
			out << "m_enemy[0].Hp:" << m_enemy[0].Hp << endl;
			out << "m_enemy[1].Hp:" << m_enemy[1].Hp << endl;
			out << "m_enemy[2].Hp:" << m_enemy[2].Hp << endl;
			out << "m_enemy[3].Hp:" << m_enemy[3].Hp << endl;
			out << "m_enemy[4].Hp:" << m_enemy[4].Hp << endl;
			//sprintf_s(str, "m_player.pos: %f,%f", m_player.pos.x, m_player.pos.y);
			out << "m_player.pos:" << m_player.pos.x << ',' << m_player.pos.y << endl;
			//out << str << endl;


			//파일 닫기
			out.flush();
			out.close();
		}

		
	}
	//load
	if (KEYMANAGER->isKeyDown('P'))
	{
		ifstream in;		//읽기용
		//읽기용으로 파일 열기
		in.open("save/hi.save", ios::in);
		
		char str[128];
		char* context;
		char* str2;

		if (in.is_open())
		{
			in.getline(str, 128);
			strtok_s(str, ":", &context);
			m_enemy[0].Hp = atoi(context);
			in.getline(str, 128);
			strtok_s(str, ":", &context);
			m_enemy[1].Hp = atoi(context);
			in.getline(str, 128);
			strtok_s(str, ":", &context);
			m_enemy[2].Hp = atoi(context);
			in.getline(str, 128);
			strtok_s(str, ":", &context);
			m_enemy[3].Hp = atoi(context);
			in.getline(str, 128);
			strtok_s(str, ":", &context);
			m_enemy[4].Hp = atoi(context);

			in.getline(str, 128);
			strtok_s(str, ":", &context);
			str2=strtok_s(NULL, ",", &context);

			m_player.pos.x = (float)atof(str2);
			m_player.pos.y = (float)atof(context);
			g_ptCam.x = m_player.pos.x - 100.5f;
			g_ptCam.y = m_player.pos.y - 100.5f;

			in.clear();
			in.close();

		}
	}





	if (KEYMANAGER->StayKeyDown('A'))
	{
		if (m_player.rot.y < PI)
		{
			m_player.rot.y += 10.0f *g_ETime;
		}
		if (m_player.rot.y > PI)m_player.rot.y = PI;

		m_player.dir = D3DXVECTOR2(-1.0f, 0.0f);
		m_player.pos += m_player.dir *m_player.speed*g_ETime;
		g_ptCam += m_player.dir *m_player.speed*g_ETime;
	}
	if (KEYMANAGER->StayKeyDown('D'))
	{
		if (m_player.rot.y > 0)
		{
			m_player.rot.y -= 10.0f *g_ETime;
		}
		if (m_player.rot.y < 0)m_player.rot.y = 0.0f;



		m_player.dir = D3DXVECTOR2(1.0f, 0.0f);
		m_player.pos += m_player.dir *m_player.speed*g_ETime;
		g_ptCam += m_player.dir *m_player.speed*g_ETime;
	}
	/*if (KEYMANAGER->isKeyDown('W'))
	{
		pl->SetCurrentFrameX(pl->GetCurrentFrameX() + 1);
	}
	if (KEYMANAGER->isKeyDown('S'))
	{
		pl->SetCurrentFrameX(pl->GetCurrentFrameX() - 1);
	}*/



	



	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (!m_bullet[i].fire)
			{
				D3DXVECTOR2 temp;
				temp = (g_ptMouse+g_ptCam) - m_player.pos;
				D3DXVec2Normalize(&m_bullet[i].dir, &temp);
				m_bullet[i].pos = m_player.pos;
				m_bullet[i].speed = 300.0f;
				m_bullet[i].fire = true;
				break;
			}
		}
	}

	//총알 날아가기

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (m_bullet[i].fire)
		{
			m_bullet[i].pos += m_bullet[i].dir *m_bullet[i].speed *g_ETime;

			//총알 적 충돌
			//렉트,서클
			for (int j = 0; j < BULLETMAX-3; j++)
			{
				FRECT TempRc = RectMakeCenter(m_enemy[j].Pos.x, m_enemy[j].Pos.y,
					m_enemy[j].Size.x, m_enemy[j].Size.y);

				FCIRCLE TempCc = CircleMake(m_bullet[i].pos.x, m_bullet[i].pos.y, 15.0f);
				if (IntersectRectCircle(TempRc, TempCc) && m_enemy[j].Hp > 0)
				{
					m_enemy[j].Hp--;
					m_bullet[i].fire = false;
				}

			}
			//서클,서클
			for (int j = BULLETMAX - 3; j < BULLETMAX; j++)
			{
				FCIRCLE TempCc2 = CircleMake(m_enemy[j].Pos.x, m_enemy[j].Pos.y, 50.0f);

				FCIRCLE TempCc = CircleMake(m_bullet[i].pos.x, m_bullet[i].pos.y, 15.0f);
				if (IntersectCircle(TempCc2, TempCc) && m_enemy[j].Hp > 0)
				{
					m_enemy[j].Hp--;
					m_bullet[i].fire = false;
				}
			}

		}
		//벽충돌조건
		if (m_bullet[i].pos.x -g_ptCam.x> WINSIZEX ||
			m_bullet[i].pos.x -g_ptCam.x<0 ||
			m_bullet[i].pos.y -g_ptCam.y>WINSIZEY ||
			m_bullet[i].pos.y -g_ptCam.y< 0
			)
		{
			m_bullet[i].fire = false;
		}
	}
	D3DXVECTOR2 pos3 = Pos2 - Pos1;

	float distance = D3DXVec2Length(&pos3);

}

void Action::render()
{
	/*for (int i = 0; i < ENEMYMAX; i++)
	{
		Mom* temp;

		

		switch (m_enemy[i].Shape)
		{
		case 0:
			temp = new Circle(20);
			temp->
			break;
		case 1:
			break;
		case 2:
			break;
		}
	}*/



	for (int i = 0; i < BULLETMAX; i++)
	{
		if (m_bullet[i].fire)
		{
			egg->Scale(30.0f, 30.0f);
			egg->Position(m_bullet[i].pos);
			egg->Rotate(0.0f,0.0f,45.0f*TORADIAN);
			egg->Render();
		}
			
	}

	ImGui::SliderFloat3("xyz", m_angle, 0, 2 * PI);

	pls->Scale(200.0f, 200.0f);
	pls->Position(m_player.pos.x-20.0f, m_player.pos.y-15.0f);
	pls->Rotate(0.8f, -m_player.rot.y,0.0f);






	pl->Scale(200.0f, 200.0f);
	pl->Position(m_player.pos);
	pl->Rotate(m_player.rot);


	ImGui::ColorEdit4("color", m_player.color);
	pl->Color(m_player.color);

	pls->PlayAnimation(ANI_LOOP, true, 0.2f);
	IMGMANAGER->PlayAnimation("player", ANI_LOOP, true, 0.2f);
	

	if (m_enemy[4].Hp > 0)
	{
		egg->Scale(m_enemy[4].Size);
		egg->Position(m_enemy[4].Pos);
		egg->Rotate(0.0f, 0.0f,0.0f);
		egg->Render();
	}
	//렉트 객체 하나로 두개 그리기
	if (m_enemy[0].Hp > 0)
	{
		IMGMANAGER->Getrect()->SetisFill(false);
		IMGMANAGER->Getrect()->Position(m_enemy[0].Pos);
		IMGMANAGER->Getrect()->Scale(m_enemy[0].Size);
		IMGMANAGER->Getrect()->Color(1, 0, 1, 0.3f);
		IMGMANAGER->RectRender();
	}
	if (m_enemy[1].Hp > 0)
	{
		IMGMANAGER->Getrect()->SetisFill(true);
		IMGMANAGER->Getrect()->Position(m_enemy[1].Pos);
		IMGMANAGER->Getrect()->Scale(m_enemy[1].Size);
		IMGMANAGER->Getrect()->Color(0, 0, 1);
		IMGMANAGER->RectRender();
	}
	//서클도 그렇게 그려주기

	if (m_enemy[2].Hp > 0)
	{
		IMGMANAGER->Getcircle()->SetisFill(true);
		IMGMANAGER->Getcircle()->Position(m_enemy[2].Pos);
		IMGMANAGER->Getcircle()->Scale(m_enemy[2].Size);
		IMGMANAGER->Getcircle()->Color(1, 1, 1,0.3f);
		IMGMANAGER->CircleRender();
	}
	if (m_enemy[3].Hp > 0)
	{
		IMGMANAGER->Getcircle()->SetisFill(false);
		IMGMANAGER->Getcircle()->Position(m_enemy[3].Pos);
		IMGMANAGER->Getcircle()->Scale(m_enemy[3].Size);
		IMGMANAGER->Getcircle()->Color(1, 1, 1);
		IMGMANAGER->CircleRender();
	}


	//충돌체
	FRECT rc1 = RectMakeCenter(g_ptMouse.x, g_ptMouse.y,
		m_collisionBox[1].size.x, m_collisionBox[1].size.y);
	FRECT rc2 = RectMakeCenter(m_collisionBox[0].pos.x, m_collisionBox[0].pos.y,
		m_collisionBox[0].size.x, m_collisionBox[0].size.y);


	//1번박스
	ImGui::SliderFloat("angle", &m_collisionBox[1].angle, 0, 2 * PI);
	IMGMANAGER->Getrect()->SetisFill(true);
	IMGMANAGER->Getrect()->Position(g_ptMouse);
	IMGMANAGER->Getrect()->Scale(m_collisionBox[1].size);
	IMGMANAGER->Getrect()->Rotate(0, 0, m_collisionBox[1].angle);
	IMGMANAGER->Getrect()->Color(0.5f, 0, 0.5f, 0.5f);
	IMGMANAGER->RectRender();

	//0번박스
	ImGui::SliderFloat("angle2", &m_collisionBox[0].angle, 0, 2 * PI);
	IMGMANAGER->Getrect()->SetisFill(true);
	IMGMANAGER->Getrect()->Position(m_collisionBox[0].pos);
	IMGMANAGER->Getrect()->Scale(m_collisionBox[0].size);
	IMGMANAGER->Getrect()->Rotate(0, 0, m_collisionBox[0].angle);
	IMGMANAGER->Getrect()->Color(0.5f, 0, 1, 0.5f);
	if (IntersectRect(rc1, rc2, m_collisionBox[1].angle, m_collisionBox[0].angle))
	{
		IMGMANAGER->Getrect()->Color(0.0f, 0, 0);
	}
	IMGMANAGER->RectRender();



}
