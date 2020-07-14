#include "stdafx.h"
#include "MainGame.h"
#include "MiniGame/IsoTile.h"
#include "MiniGame/TileMap.h"
#include "MiniGame/Loading.h"
#include "Kirby/Title.h"
#include "Kirby/swordkirby.h"
#include "Kirby/Shop.h"
#include "Kirby/Village.h"
#include "Kirby/Levelmap.h"
#include "Kirby/UI.h"
#include "Kirby/Monster.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//싱글톤 해제

	SCENEMANAGER->ReleaseAll();
	SCENEMANAGER->ReleaseSingleton();
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
	CAMMANAGER->ReleaseSingleton();
	IMGMANAGER->DeleteAll();
	IMGMANAGER->ReleaseSingleton();
	WRITEMANAGER->ReleaseSingleton();
}

HRESULT MainGame::init()
{
	//윈도우가 시작되서 지금까지 흐른 시간을 1/1000초 단위로
	//DWORD형을 리턴하는 함수다
	srand(GetTickCount());
	////////////////////////////////////////////////////
	
	IMGMANAGER->AddImage("TILE", _T("tilemap.bmp"), 2, 2, "PS");
	IMGMANAGER->AddImage("egg", _T("알.bmp"), "PS2");
	/// main title
	IMGMANAGER->AddImage("menu1", _T("menu1.png"),1,1);
	IMGMANAGER->AddImage("menu2", _T("menu2.png"),4,1,"PS");
	IMGMANAGER->AddImage("menu3", _T("menu3.png"),1,1);
	IMGMANAGER->AddImage("menu4", _T("menu4.png"), 1, 1);
	IMGMANAGER->AddImage("End", _T("End.png"), 46, 1);
	IMGMANAGER->AddImage("Start", _T("Start.png"), 1, 1);
	/// loading
	IMGMANAGER->AddImage("loading", _T("loading_bar.png"), 1, 1);

	///player move
	IMGMANAGER->AddImage("walk", _T("walk.png"), 11, 1, "PS");
	IMGMANAGER->AddImage("run", _T("run.png"), 8, 1, "PS");
	IMGMANAGER->AddImage("sliding", _T("sliding.png"), 3, 1, "PS");
	///player jump
	IMGMANAGER->AddImage("hold jump keyup", _T("hold jump keyup.png"), 5, 1, "PS");
	IMGMANAGER->AddImage("hold jump", _T("hold jump.png"), 11, 1, "PS");
	IMGMANAGER->AddImage("jump", _T("jump.png"), 11, 1, "PS");
	///player att
	IMGMANAGER->AddImage("jump slash", _T("jump slash.png"), 42, 1, "PS");
	IMGMANAGER->AddImage("rapid slash", _T("rapid slash.png"), 46, 1, "PS");
	IMGMANAGER->AddImage("sword spin", _T("sword spin.png"), 9, 1, "PS");

	///monster 1,2,3
	IMGMANAGER->AddImage("monster1", _T("monster1.png"), 10, 2, "PS3");
	IMGMANAGER->AddImage("monster2", _T("monster2.png"), 10, 2, "PS3");
	IMGMANAGER->AddImage("monster3", _T("monster3.png"), 15, 7, "PS3");

	IMGMANAGER->AddImage("monster3att", _T("monster3att.png"), 6, 1, "PS");
	IMGMANAGER->AddImage("monster3die", _T("monster3die.png"), 1, 1, "PS");
	IMGMANAGER->AddImage("monster3flip", _T("monster3flip.png"), 18, 1, "PS");
	IMGMANAGER->AddImage("monster3hit", _T("monster3hit.png"), 2, 1, "PS");
	IMGMANAGER->AddImage("monster3idle", _T("monster3idle.png"), 9, 1, "PS");
	IMGMANAGER->AddImage("monster3walk", _T("monster3walk.png"), 12, 1, "PS");



	/// ----------------------MAP--------------------------- ///
	IMGMANAGER->AddImage("sparky", _T("sparky.png"), 3, 1,"PS");
	/*------------------------City 1--------------------------*/
	IMGMANAGER->AddImage("Sky", _T("Sky.png"), 1, 1);
	IMGMANAGER->AddImage("buildings", _T("buildings.png"), 1, 1);
	IMGMANAGER->AddImage("wall2", _T("wall2.png"), 1, 1);
	IMGMANAGER->AddImage("wall1", _T("wall1.png"), 1, 1);
	IMGMANAGER->AddImage("boxesncontainer", _T("boxesncontainer.png"), 1, 1);
	IMGMANAGER->AddImage("wheelsnhydrant", _T("wheelsnhydrant.png"), 1, 1);
	IMGMANAGER->AddImage("roadnborder", _T("roadnborder.png"), 1, 1);
	IMGMANAGER->AddImage("City1", _T("City1.png"), 1, 1);
	/*------------------------City 2--------------------------*/
	IMGMANAGER->AddImage("Sky2", _T("Sky2.png"), 1, 1);
	IMGMANAGER->AddImage("back", _T("back.png"), 1, 1);
	IMGMANAGER->AddImage("houses3", _T("houses3.png"), 1, 1);
	IMGMANAGER->AddImage("houses1", _T("houses1.png"), 1, 1);
	IMGMANAGER->AddImage("minishopncallbox", _T("minishopncallbox.png"), 1, 1);
	IMGMANAGER->AddImage("roadnlamps", _T("roadnlamps.png"), 1, 1);
	IMGMANAGER->AddImage("City2", _T("City2.png"), 1, 1);
	/*------------------------City 3--------------------------*/
	IMGMANAGER->AddImage("Sky3", _T("Sky3.png"), 1, 1);
	IMGMANAGER->AddImage("houses3_3", _T("houses3_3.png"), 1, 1);
	IMGMANAGER->AddImage("houded3_2", _T("houded3_2.png"), 1, 1);
	IMGMANAGER->AddImage("houses3_1", _T("houses3_1.png"), 1, 1);
	IMGMANAGER->AddImage("road", _T("road.png"), 1, 1);
	IMGMANAGER->AddImage("crosswalk", _T("crosswalk.png"), 1, 1);
	IMGMANAGER->AddImage("City3", _T("City3.png"), 1, 1);
	/*------------------------City 4--------------------------*/
	IMGMANAGER->AddImage("Sky4", _T("Sky4.png"), 1, 1);
	IMGMANAGER->AddImage("houses4_2", _T("houses4_2.png"), 1, 1);
	IMGMANAGER->AddImage("houses4_1", _T("houses4_1.png"), 1, 1);
	IMGMANAGER->AddImage("fountainnbush", _T("fountainnbush.png"), 1, 1);
	IMGMANAGER->AddImage("houses4_0", _T("houses4_0.png"), 1, 1);
	IMGMANAGER->AddImage("umbrellanpolicebox", _T("umbrellanpolicebox.png"), 1, 1);
	IMGMANAGER->AddImage("road4", _T("road4.png"), 1, 1);
	IMGMANAGER->AddImage("City4", _T("City4.png"), 1, 1);
	/*-------------------------Downtown----------------------*/
	IMGMANAGER->AddImage("downtown", _T("downtown.png"), 1, 1);
	IMGMANAGER->AddImage("toad1", _T("toad1.png"), 1, 1);
	IMGMANAGER->AddImage("yoshi", _T("yoshi.png"), 7, 1);
	/*--------------------------LevelMap---------------------*/
	IMGMANAGER->AddImage("Levelmaps", _T("Levelmaps.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds1", _T("LevelBackgrounds1.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds2", _T("LevelBackgrounds2.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds3", _T("LevelBackgrounds3.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds4", _T("LevelBackgrounds4.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds5", _T("LevelBackgrounds5.png"), 1, 1);
	IMGMANAGER->AddImage("LevelBackgrounds6", _T("LevelBackgrounds6.png"), 1, 1);

	////////////////////////////////////////////////////////////////
	///UI
	// armor
	IMGMANAGER->AddImage("Armor", _T("Armor.png"), 1, 4,"PS");
	//UI
	IMGMANAGER->AddImage("Interface", _T("Interface.png"), 1, 1, "PS");
	//Skill
	IMGMANAGER->AddImage("Skill", _T("Skill.png"), 8, 1, "PS");
	
	/////////////////////////////////////////////////////////////////////



	//GameNode* p;
	//
	//p = new IsoTile;
	//SCENEMANAGER->AddScene("Iso", p);
	SCENEMANAGER->AddScene("Iso", new IsoTile);
	SCENEMANAGER->AddScene("Tile", new TileMap);
	SCENEMANAGER->AddScene("Loading", new Loading);
	SCENEMANAGER->AddScene("Title", new Title);
	SCENEMANAGER->AddScene("Village", new Village);
	//
	SCENEMANAGER->ChangeScene("Title");
	IMGMANAGER->GetImage("menu2")->Scale(48.0f, 38.0f);

	KIRBYMANAGER->SETKIRBY(new swordkirby);
	gunterMANAGER->SETGUNTER(new Monster);

	//delete KIRBYMANAGER->GETKIRBY();
	//KIRBYMANAGER->SETKIRBY(new beamkirby);


	KIRBY->init();
	GUNTER->init();
	////////////////////////////////////////////////////
	ImGui::Create(g_hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();
	return S_OK;
}

void MainGame::release()
{
	////////////////////////////////////////////////////
	




	////////////////////////////////////////////////////
	ImGui::Delete();
}

void MainGame::update()
{
	////////////////////////////////////////////////////
	
	
	//if (KEYMANAGER->isKeyDown('1'))
	//{
	//	SCENEMANAGER->ChangeScene("Iso");
	//}
	//
	//
	//
	//if (KEYMANAGER->isKeyDown('2'))
	//{
	//	SCENEMANAGER->ChangeScene("Tile");
	//}
	
	
	
	
	
	
	SCENEMANAGER->CurrentSceneUpdate();

	////////////////////////////////////////////////////
	SOUNDMANAGER->Update();
	ImGui::Update();
}

void MainGame::render()
{
	D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)background);
	CAMMANAGER->SetBuffers();
	WRITEMANAGER->GetDc()->BeginDraw();
	TIMEMANAGER->render();
	////////////////////////////////////////////////////




	/*menu2->Scale(48.0f, 38.0f);
	menu2->Position(g_ptMouse.x, g_ptMouse.y);
	IMGMANAGER->PlayAnimation("menu2", ANI_LOOP, 1, 0.2f);
	menu2->Render();*/

	SCENEMANAGER->CurrentSceneRender();
	IMGMANAGER->GetImage("menu2")->Position(g_ptMouse+g_ptCam);
	IMGMANAGER->PlayAnimation("menu2", ANI_LOOP, 1, 0.2f);
	////////////////////////////////////////////////////
#ifdef _DEBUG
	ImGui::Render();
#endif
	
	WRITEMANAGER->GetDc()->EndDraw();
	SwapChain->Present(0, 0);

}
