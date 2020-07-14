#include "stdafx.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
}

HRESULT Title::init()
{

	menu4 = IMGMANAGER->GetImage("menu4");
	menu1 = IMGMANAGER->GetImage("menu1");
	menu2 = IMGMANAGER->GetImage("menu2");
	menu3 = IMGMANAGER->GetImage("menu3");

	End = IMGMANAGER->GetImage("End");
	Start = IMGMANAGER->GetImage("Start");
	
	return S_OK;
}

void Title::release()
{
}

void Title::update()
{

	if (PtInRect(exitMenu, g_ptMouse))
	{
		//마우스 오버


		//마우스 클릭
		if (KEYMANAGER->isKeyDown(VK_LBUTTON)) {
			


			PostQuitMessage(0);

		}



	}
	if (PtInRect(newMenu, g_ptMouse))
	{

		if (KEYMANAGER->isKeyDown(VK_LBUTTON)) {
			SCENEMANAGER->ChangeScene("Village");
		}
	}
	if (PtInRect(loadMenu, g_ptMouse))
	{


		if (KEYMANAGER->isKeyDown(VK_LBUTTON)) {
			//??????
		}

	}


	//if(PtInRect(exitMenu,))
	
}

void Title::render()
{
	menu4->Scale(WINSIZEX, WINSIZEY);
	menu4->Position(WINSIZEX/2, WINSIZEY/2);
	menu4->Render();

	Start->Scale(200.0f, 100.0f);
	Start->Position(newMenu.left + 100.0f, newMenu.bottom + 50.0f);
	Start->Render();

	
	Rect* rc = IMGMANAGER->Getrect();
	/*rc->Position(newMenu.left + 100.0f, newMenu.bottom + 50.0f);
	rc->Scale(200.0f, 100.0f);
	rc->Color(1.0f, 0.0f, 0.0f);
	rc->Render();*/

	

	rc->Position(exitMenu.left + 100.0f, exitMenu.bottom + 50.0f);
	rc->Scale(200.0f, 100.0f);
	rc->Color(1.0f, 0.0f, 0.0f);
	rc->Render();
	//rc->(newMenu.left+100.0f, newMenu.bottom + 50.0f)


	/*menu1->Scale(307.0f, 246.0f);
	menu1->Position(400.0f, 400.0f);
	menu1->Render();*///superstar
	/*menu3->Scale(174.0f, 176.0f);
	menu3->Position(380.0f, 400.0f);
	menu3->Render();*///kirby

	
	
	

	

}
