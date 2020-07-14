#include "stdafx.h"
#include "swordkirby.h"


swordkirby::swordkirby()
{
}


swordkirby::~swordkirby()
{
}

HRESULT swordkirby::init()
{
	pl = IMGMANAGER->GetImage("walk");
	plr = IMGMANAGER->GetImage("run");
	pls = IMGMANAGER->GetImage("sliding");

	plj = IMGMANAGER->GetImage("jump");
	plhj = IMGMANAGER->GetImage("hold jump");
	plhjup = IMGMANAGER->GetImage("hold jump keyup");

	pljs = IMGMANAGER->GetImage("jump slash");
	plrs = IMGMANAGER->GetImage("rapid slash");
	plss = IMGMANAGER->GetImage("sword spin");

	m_player.pos.x = 100.0f;
	m_player.pos.y = 150.0f;
	m_player.speed = 1000.0f;
	m_player.dir = D3DXVECTOR2(1.0f, 0.0f);
	m_player.Jumpkirby = false;
	m_player.Skilltime = 1.3f;
	///gravity state
	m_player.Jump = 150.0f;
	m_player.gravity = 200.0f;
	m_player.Delta = 0.0f;

	FRECT kirbyHitbox = RectMakeCenter(m_player.pos.x, m_player.pos.y, 100, 100);
	FRECT Swordkirby = RectMakeCenter(m_player.pos.x, m_player.pos.y, 100, 100);

	return S_OK;
}

void swordkirby::release()
{
}

void swordkirby::update()
{
	if (pl_state<JUMPSLASH)
		pl_state = STAY;
	
	m_player.Delta -= m_player.gravity*g_ETime;
	m_player.pos.y += m_player.Delta*g_ETime;
	/*------------------------------*/
//	m_player.Delta =m_player.Jump- m_player.gravity*g_ETime;
//	m_player.pos.y += m_player.Delta*g_ETime;
	cout << m_player.Delta << "," << m_player.gravity<<","<< m_player.pos.y << endl;
	
	
	
	
		

	if (KEYMANAGER->StayKeyDown(VK_RIGHT)) {
		pl_state = RWALK;
		m_player.pos += m_player.dir*m_player.speed*g_ETime;
		isLeft = false;
		
		
	}
	else if (KEYMANAGER->StayKeyDown(VK_LEFT)) {
		if (pl_state == JUMPSLASH)
		{
			IMGMANAGER->GetImage("jump slash")->GetRefCurrentFrameX() = 0;
		}
		pl_state = LWALK;
		isLeft = true;
		
		m_player.pos -= m_player.dir*m_player.speed*g_ETime;
		
	}
	if (KEYMANAGER->StayKeyDown(VK_UP)) {
		//jump

		pl_state = JUMPH;
		
		
		//m_player.Delta = 50.0f;
		
		if (KEYMANAGER->StayKeyDown(VK_RIGHT))
		{
			pl_state = JUMP;
		}
	}
		if (KEYMANAGER->isKeyUp(VK_UP)) {
			pl_state = JUMPHUP;
		}
	
		if (KEYMANAGER->isKeyDown(VK_UP))
		{
			m_player.Delta += m_player.Jump;
			if (KEYMANAGER->isKeyDown(VK_LEFT))
			{
				pl_state = JUMP;
				pl->Rotate(D3DXVECTOR3(0, 3.14f, 0));
			}
		}
		

	//if run {	
	if (KEYMANAGER->isKeyDown(VK_DOWN)) {
		//sliding
		pl_state = SLIDING;

	}

	// jump slash
	if (KEYMANAGER->isKeyDown('A')) {
		pl_state = JUMPSLASH;

	}
	// rapid slash
	if (KEYMANAGER->isKeyDown('S')) {
		pl_state = RAPIDSLASH;

	

		//IMGMANAGER->GetImage("rapid slash")->GetRefCurrentFrameX()++;


		//		str = ;
	}
	// sword spin
	if (KEYMANAGER->isKeyDown('D')) {
		pl_state = SWORDSPIN;
		m_player.gravity = 180.0f;
	

	}
	if (KEYMANAGER->isKeyDown('G')) {
		m_player.pos.y = 100.0f;
	}

}

void swordkirby::render()
{
	float angle;
	isLeft ? angle = PI : angle = 0;



	pl->Rotate(0.0f, angle, 0.0f); 
	plj->Rotate(0.0f, angle, 0.0f);
	pls->Rotate(0.0f, angle, 0.0f);
	plhj->Rotate(0.0f, angle, 0.0f);
	plhjup->Rotate(0.0f, angle, 0.0f);
	plr->Rotate(0.0f, angle, 0.0f);
	pljs->Rotate(0.0f, angle, 0.0f);
	plrs->Rotate(0.0f, angle, 0.0f);
	plss->Rotate(0.0f, angle, 0.0f);


	pl->Scale(200.0f, 200.0f);
	pl->Position(m_player.pos);
	
	pls->Scale(200.0f, 200.0f);
	pls->Position(m_player.pos);

	plj->Scale(200.0f, 200.0f);
	plj->Position(m_player.pos);

	plhj->Scale(200.0f, 200.0f);
	plhj->Position(m_player.pos);

	plhjup->Scale(200.0f, 200.0f);
	plhjup->Position(m_player.pos);

	plr->Scale(200.0f, 200.0f);
	plr->Position(m_player.pos);

	pljs->Scale(200.0f, 200.0f);
	pljs->Position(m_player.pos);

	plrs->Scale(200.0f, 200.0f);
	plrs->Position(m_player.pos);

	plss->Scale(200.0f, 200.0f);
	plss->Position(m_player.pos);

	string str;
	//if (IMGMANAGER->GetImage("walk")->GetRefCurrentFrameX() == 11)
	//{
	//	(IMGMANAGER->GetImage("walk")->GetRefCurrentFrameX() == 0);
	//}
	//IMGMANAGER->PlayAnimation("walk",ANI_LOOP, false, 0.2f);
	if (pl_state == STAY)


		pl->GetRefCurrentFrameX() = 0;
	if (pl_state < JUMP)
	{
	}
	//IMGMANAGER->PlayAnimation("walk", ANI_LOOP, true, 0.1f);
	//else if (pl_state == JUMP)
	//IMGMANAGER->PlayAnimation("jump", ANI_LOOP, true, 0.1f);
	switch (pl_state)
	{
	case STAY:
		IMGMANAGER->PlayAnimation("walk", ANI_STOP, true, 0.1f);
		break;
	case LWALK:
		IMGMANAGER->PlayAnimation("walk", ANI_LOOP, true, 0.1f);
		break;
	case RWALK:
		IMGMANAGER->PlayAnimation("walk", ANI_LOOP, true, 0.1f);
		break;
	case RUN:
		IMGMANAGER->PlayAnimation("run", ANI_LOOP, true, 0.1f);
		break;
	case SLIDING:
		IMGMANAGER->PlayAnimation("sliding", ANI_LOOP, true, 0.1f);
		break;
	case JUMP:
		IMGMANAGER->PlayAnimation("jump", ANI_LOOP, true, 0.1f);
		break;
	case JUMPH:
		IMGMANAGER->PlayAnimation("hold jump", ANI_LOOP, true, 0.1f);
		//bool
		if (IMGMANAGER->GetImage("hold jump")->GetRefCurrentFrameX() == 11)
		{
			pl_state = JUMPHUP;
		}

		break;
	case JUMPHUP:
		IMGMANAGER->Render("hold jump keyup");
		break;
	case JUMPSLASH:
		IMGMANAGER->PlayAnimation("jump slash", ANI_LOOP, true, 0.04f);
		break;

	case RAPIDSLASH:

		IMGMANAGER->PlayAnimation("rapid slash", ANI_LOOP, true, 0.04f);

		/*if (IMGMANAGER->GetImage("rapid slash")->GetRefCurrentFrameX() == 14)
		{
			pl_state = STAY;
		}
		if (IMGMANAGER->GetImage("rapid slash")->GetRefCurrentFrameX() ==20)
		{
			pl_state = STAY;
		}*/
		break;
	case SWORDSPIN:
		IMGMANAGER->PlayAnimation("sword spin",  ANI_LOOP, true, 0.04f);
		break;
	default:
		break;
	}
}
