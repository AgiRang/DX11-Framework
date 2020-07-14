#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init()
{
	IF = IMGMANAGER->GetImage("Interface");
	Armor = IMGMANAGER->GetImage("Armor");
	Skill = IMGMANAGER->GetImage("Skill");

	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
}

void UI::render()
{
	IF->Scale(200.0f, 100.0f);
	IF->Position(WINSIZEX/30, WINSIZEY/30);

	Armor->Scale(46.0f, 48.4f);
	
	

}
