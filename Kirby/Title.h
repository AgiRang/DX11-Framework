#pragma once
#include "GameNode.h"


class Title:public GameNode
{
public:
	Image * menu1;
	Image * menu2;
	Image * menu3;
	Image * menu4;
	Image* End;
	Image* Start;
	//menu overview
	Image* overview;
	//menu click
	Image* clickview;

	FRECT newMenu = RectMake(WINSIZEX*0.6, WINSIZEY/2, 200.0f, 100.0f);
	FRECT loadMenu = RectMake(WINSIZEX*0.6, WINSIZEY / 2-100.0f, 200.0f, 100.0f);
	FRECT exitMenu = RectMake(WINSIZEX*0.6, WINSIZEY / 2-200.0f, 200.0f, 100.0f);

	Title();
	~Title() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

