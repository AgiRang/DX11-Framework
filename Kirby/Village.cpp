#include "stdafx.h"
#include "Village.h"
#include "Kirby/swordkirby.h"
#include "Kirby/Monster.h"

Village::Village()
{
}


Village::~Village()
{

}

HRESULT Village::init()
{
	///City1
	Sky = IMGMANAGER->GetImage("Sky");
	buildings = IMGMANAGER->GetImage("buildings");
	wall2 = IMGMANAGER->GetImage("wall2");
	wall1 = IMGMANAGER->GetImage("wall1");
	boxesncontainer = IMGMANAGER->GetImage("boxesncontainer");
	wheelsnhydrant = IMGMANAGER->GetImage("wheelsnhydrant");
	roadnborder = IMGMANAGER->GetImage("roadnborder");
	///City2
	Sky2 = IMGMANAGER->GetImage("Sky2");
	back = IMGMANAGER->GetImage("back");
	houses3 = IMGMANAGER->GetImage("houses3");
	houses1 = IMGMANAGER->GetImage("houses1");
	minishopncallbox = IMGMANAGER->GetImage("minishopncallbox");
	roadnlamps = IMGMANAGER->GetImage("roadnlamps");
	///City3
	Sky3 = IMGMANAGER->GetImage("Sky3");
	houses3_3 = IMGMANAGER->GetImage("houses3_3");
	houded3_2 = IMGMANAGER->GetImage("houded3_2");
	houses3_1 = IMGMANAGER->GetImage("houses3_1");
	road = IMGMANAGER->GetImage("road");
	crosswalk = IMGMANAGER->GetImage("crosswalk");
	///City4
	Sky4 = IMGMANAGER->GetImage("Sky4");
	houses4_2 = IMGMANAGER->GetImage("houses4_2");
	houses4_1 = IMGMANAGER->GetImage("houses4_1");
	fountainnbush = IMGMANAGER->GetImage("fountainnbush");
	houses4_0 = IMGMANAGER->GetImage("houses4_0");
	umbrellanpolicebox = IMGMANAGER->GetImage("umbrellanpolicebox");
	road4 = IMGMANAGER->GetImage("road4");
	///Downtown
	downtown = IMGMANAGER->GetImage("downtown");
	yoshi = IMGMANAGER->GetImage("yoshi");
	toad1 = IMGMANAGER->GetImage("toad1");
	sparky = IMGMANAGER->GetImage("sparky");
	
	return S_OK;
}

void Village::release()
{
}

void Village::update()
{
	
	if ( PtInRect(NextMap,KIRBY->GetRefm_player().pos)) {
	
		g_ptCam.x = WINSIZEX;
		KIRBY->GetRefm_player().pos.x += 100.0f;
		
	}

	if (PtInRect(NextMap2, KIRBY->GetRefm_player().pos)) {

		g_ptCam.x = WINSIZEX*2;
		KIRBY->GetRefm_player().pos.x += 100.0f;
	}
	if (PtInRect(PrevMap2, KIRBY->GetRefm_player().pos)) {

		g_ptCam.x = 0;
		KIRBY->GetRefm_player().pos.x -= 100.0f;
	}

	if (PtInRect(NextMap3, KIRBY->GetRefm_player().pos)) {

		g_ptCam.x = WINSIZEX*3;
		KIRBY->GetRefm_player().pos.x += 100.0f;
	}
	if (PtInRect(PrevMap3, KIRBY->GetRefm_player().pos)) {

		g_ptCam.x = WINSIZEX;
		KIRBY->GetRefm_player().pos.x -= 100.0f;
	}

	if (PtInRect(PrevMap4,KIRBY->GetRefm_player().pos)) {

		g_ptCam.x = WINSIZEX * 2;
		KIRBY->GetRefm_player().pos.x -= 100.0f;
	}
	if (KEYMANAGER->isKeyDown('F')) {
		if (PtInRect(Downtown2, KIRBY->GetRefm_player().pos)) {
			g_ptCam.y = WINSIZEY;
			KIRBY->GetRefm_player().pos.y = WINSIZEY + 200.0f;
		}
		if (PtInRect(Downtown3, KIRBY->GetRefm_player().pos)) {
			g_ptCam.y = 0;
			KIRBY->GetRefm_player().pos.y = 100.0f;
		}
		if (PtInRect(yoshibox, KIRBY->GetRefm_player().pos)) {
			//item

		}
		if (PtInRect(toad1box, KIRBY->GetRefm_player().pos)) {
			//skill

		}

	}
		if (PtInRect(bottom2, KIRBY->GetRefm_player().pos)) {
			KIRBY->GetRefm_player().gravity=0;
			
		}
	if (PtInRect(bottom,KIRBY->GetRefm_player().pos )) {
		//KIRBY->GetRefm_player().pos.y = bottom.top;
		KIRBY->GetRefm_player().pos.y -= KIRBY->GetRefm_player().Delta*g_ETime;
		KIRBY->GetRefm_player().Delta = 0;
	}
	KIRBY->update();
	GUNTER->update();
	//KIRBYMANAGER->GETKIRBY()->update();

}

void Village::render()
{
	Sky->Scale(WINSIZEX, WINSIZEY);
	Sky->Position(WINSIZEX/2, WINSIZEY/2);
	Sky->Render();

	buildings->Scale(WINSIZEX, WINSIZEY);
	buildings->Position(WINSIZEX / 2, WINSIZEY / 2);
	buildings->Render();

	wall2->Scale(WINSIZEX, WINSIZEY);
	wall2->Position(WINSIZEX / 2, WINSIZEY / 2);
	wall2->Render();

	wall1->Scale(WINSIZEX, WINSIZEY);
	wall1->Position(WINSIZEX / 2, WINSIZEY / 2);
	wall1->Render();

	boxesncontainer->Scale(WINSIZEX, WINSIZEY);
	boxesncontainer->Position(WINSIZEX / 2, WINSIZEY / 2);
	boxesncontainer->Render();

	wheelsnhydrant->Scale(WINSIZEX, WINSIZEY);
	wheelsnhydrant->Position(WINSIZEX / 2, WINSIZEY / 2);
	wheelsnhydrant->Render();

	roadnborder->Scale(WINSIZEX, WINSIZEY);
	roadnborder->Position(WINSIZEX / 2, WINSIZEY / 2);
	roadnborder->Render();
	///City2
	Sky2->Scale(WINSIZEX, WINSIZEY);
	Sky2->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	Sky2->Render();

	back->Scale(WINSIZEX, WINSIZEY);
	back->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	back->Render();

	houses3->Scale(WINSIZEX, WINSIZEY);
	houses3->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	houses3->Render();

	houses1->Scale(WINSIZEX, WINSIZEY);
	houses1->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	houses1->Render();

	minishopncallbox->Scale(WINSIZEX, WINSIZEY);
	minishopncallbox->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	minishopncallbox->Render();

	roadnlamps->Scale(WINSIZEX, WINSIZEY);
	roadnlamps->Position(WINSIZEX * 1.5, WINSIZEY / 2);
	roadnlamps->Render();
	///City3
	Sky3->Scale(WINSIZEX, WINSIZEY);
	Sky3->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	Sky3->Render();

	houses3_3->Scale(WINSIZEX, WINSIZEY);
	houses3_3->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	houses3_3->Render();

	houded3_2->Scale(WINSIZEX, WINSIZEY);
	houded3_2->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	houded3_2->Render();

	houses3_1->Scale(WINSIZEX, WINSIZEY);
	houses3_1->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	houses3_1->Render();

	road ->Scale(WINSIZEX, WINSIZEY);
	road ->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	road ->Render();

	crosswalk->Scale(WINSIZEX, WINSIZEY);
	crosswalk->Position(WINSIZEX * 2.5, WINSIZEY / 2);
	crosswalk->Render();

	///City4
	Sky4->Scale(WINSIZEX, WINSIZEY);
	Sky4->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	Sky4->Render();

	houses4_2->Scale(WINSIZEX, WINSIZEY);
	houses4_2->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	houses4_2->Render();

	houses4_1->Scale(WINSIZEX, WINSIZEY);
	houses4_1->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	houses4_1->Render();
		
	fountainnbush->Scale(WINSIZEX, WINSIZEY);
	fountainnbush->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	fountainnbush->Render();
		
	houses4_0->Scale(WINSIZEX, WINSIZEY);
	houses4_0->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	houses4_0->Render();
		
	umbrellanpolicebox->Scale(WINSIZEX, WINSIZEY);
	umbrellanpolicebox->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	umbrellanpolicebox->Render();

	road4->Scale(WINSIZEX, WINSIZEY);
	road4->Position(WINSIZEX * 3.5, WINSIZEY / 2);
	road4->Render();
	///Downtown
	downtown->Scale(WINSIZEX, WINSIZEY);
	downtown->Position(WINSIZEX * 1.5, WINSIZEY * 1.5);
	downtown->Render();

	toad1->Scale(117, 148);
	toad1->Position(WINSIZEX * 1.8, WINSIZEY+230.0f);
	toad1->Render();

	yoshi->Scale(40, 36);
	yoshi->Position(WINSIZEX * 1.3, WINSIZEY+200.0f);
	IMGMANAGER->PlayAnimation("yoshi", ANI_LOOP, 1, 0.1f);
	yoshi->Render();

	sparky->Scale(40, 36);
	sparky->Position(WINSIZEX*1.3 + 100.0f, 250);
	IMGMANAGER->PlayAnimation("sparky", ANI_LOOP, 1, 0.1f);
	sparky->Render();

	sparky->Scale(40, 36);
	sparky->Position(WINSIZEX*1.5 , WINSIZEY+200);
	IMGMANAGER->PlayAnimation("sparky", ANI_LOOP, 1, 0.1f);
	sparky->Render();

	/*Rect* rc = IMGMANAGER->Getrect();
	rc->Position(Downtown2.left + 50.0f, Downtown2.bottom + 50.0f);
	rc->Scale(100.0f, 100.0f);
	rc->Color(1.0f, 0.0f, 0.0f);
	rc->Render();

	Rect* rc2 = IMGMANAGER->Getrect();
	rc->Position(Downtown3.left + 50.0f, Downtown3.bottom + 50.0f);
	rc->Scale(100.0f, 100.0f);
	rc->Color(1.0f, 0.0f, 0.0f);
	rc->Render();
*/
	KIRBY->render();
	GUNTER->render();
}
