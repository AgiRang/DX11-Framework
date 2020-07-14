#include "stdafx.h"
#include "Monster.h"
#include "swordkirby.h"


Monster::Monster()
{
}


Monster::~Monster()
{
}

HRESULT Monster::init()
{
	monster3att = 	IMGMANAGER->GetImage("monster3att");
	monster3die = IMGMANAGER->GetImage("monster3die");
	monster3flip = IMGMANAGER->GetImage("monster3flip");
	monster3hit = IMGMANAGER->GetImage("monster3hit");
	monster3idle = IMGMANAGER->GetImage("monster3idle");
	monster3walk = IMGMANAGER->GetImage("monster3walk");

	gunter.pos.x = 1000.0f;
	gunter.pos.y = 115.0f;
	gunter.speed = 150.0;
	gunter.dir = D3DXVECTOR2(1.0f, 0.0f);

	FRECT gunterHitbox = RectMakeCenter(gunter.pos.x, gunter.pos.y, 100, 100);
	return S_OK;
}

void Monster::release()
{
}

void Monster::update()
{

	if (gunter_state < GATT)
		
	if (gunter_state == GIDLE) {
		//대기 상태일 때 간헐적으로 플립
		rand() % 5;
		
	}
	
	/// abs(gunter.pos.x - KIRBY->GetRefm_player().pos.x)
	
	if (abs(gunter.pos.x - KIRBY->GetRefm_player().pos.x) < 300.0f &&
		abs(gunter.pos.x - KIRBY->GetRefm_player().pos.x) > 200.0f) {

	}
	/*
	if (gunter.pos.x - 300.0f <= KIRBY->GetRefm_player().pos.x && KIRBY->GetRefm_player().pos.x <= gunter.pos.x + 300.0f) {
		if (gunter.pos.x < KIRBY->GetRefm_player().pos.x) {
			gunter_state = GRWALK;
			KIRBY->GetRefm_player().pos.x - gunter.pos.x;
			m_isLeft = false;
		}
		else if (KIRBY->GetRefm_player().pos.x < gunter.pos.x) {
			gunter_state = GLWALK;
			m_isLeft = true;
		}
	}
	if (gunter.pos.x - 50.0f <= KIRBY->GetRefm_player().pos.x <= gunter.pos.x + 50.0f) {
			gunter_state = GATT;
		}
		*/
	
	if (gunter.Hp == 0) {
		gunter_state = GDIE;
	}
}

void Monster::render()
{
	float angle;
	m_isLeft ? angle = PI : angle = 0;
		
	    monster3att ->Rotate(0.0f,angle,0.0f);
		monster3die	->Rotate(0.0f,angle,0.0f);
		monster3flip->Rotate(0.0f,angle,0.0f);
		monster3hit	->Rotate(0.0f,angle,0.0f);
		monster3idle->Rotate(0.0f,angle,0.0f);
		monster3walk->Rotate(0.0f,angle,0.0f);

		monster3att	  ->Scale(100.0f,50.0f);
		monster3die	  ->Scale(100.0f,50.0f);
		monster3flip  ->Scale(100.0f,50.0f);
		monster3hit	  ->Scale(100.0f,50.0f);
		monster3idle  ->Scale(100.0f,50.0f);
		monster3walk  ->Scale(100.0f,50.0f);

		monster3att	  ->Position(gunter.pos);
		monster3die	  ->Position(gunter.pos);
		monster3flip  ->Position(gunter.pos);
		monster3hit	  ->Position(gunter.pos);
		monster3idle  ->Position(gunter.pos);
		monster3walk  ->Position(gunter.pos);
		
		//if(gunter_state==GIDLE)

		switch (gunter_state)
		{
		case GIDLE:
			IMGMANAGER->PlayAnimation("monster3idle", ANI_LOOP, true, 0.1f);
			break;
		case GLWALK:
			IMGMANAGER->PlayAnimation("monster3walk", ANI_LOOP, true, 0.1f);
			break;
		case GRWALK:
			IMGMANAGER->PlayAnimation("monster3walk", ANI_LOOP, true, 0.1f);
			break;
		case GHIT:
			IMGMANAGER->PlayAnimation("monster3hit", ANI_LOOP, true, 0.1f);
			break;
		case GFLIP:
			IMGMANAGER->PlayAnimation("monster3flip", ANI_LOOP, true, 0.1f);
			break;
		case GDIE:
			IMGMANAGER->Render("monster3die");
			break;
		case GATT:
			IMGMANAGER->PlayAnimation("monster3att", ANI_LOOP, 1, 0.1f);
		default:
			break;
		}

		
}
