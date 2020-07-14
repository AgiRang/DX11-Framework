#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

HRESULT Shop::init()
{
	downtown = IMGMANAGER->GetImage("downtown");
	yoshi= IMGMANAGER->GetImage("yoshi");
	toad1 = IMGMANAGER->GetImage("toad1");
	return S_OK;
}

void Shop::release()
{
}

void Shop::update()
{
}

void Shop::render()
{

	IMGMANAGER->PlayAnimation("yoshi", ANI_LOOP, 1, 0.1f);

}
