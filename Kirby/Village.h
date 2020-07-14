#pragma once
#include"GameNode.h"
class Village :public GameNode
{
public:
	///City1
	//Image * city1;
	Image* Sky;
	Image*buildings;
	Image*wall2;
	Image*wall1;
	Image*boxesncontainer;
	Image*wheelsnhydrant;
	Image*roadnborder;


	///City2
	//Image * city2;
	Image* Sky2;
	Image*back;
	Image*houses3;
	Image*houses1;
	Image*minishopncallbox;
	Image*roadnlamps;


	///City3
	//Image * city3;
	Image* Sky3;
	Image*houses3_3;
	Image*houded3_2;
	Image*houses3_1;
	Image*road;
	Image*crosswalk;


	///City4
	//Image * city4;
	Image* Sky4;
	Image*houses4_2;
	Image*houses4_1;
	Image*fountainnbush;
	Image*houses4_0;
	Image*umbrellanpolicebox;
	Image*road4;

	///Downtown
	//Image*downtown;

	Image* sparky;
	Image * downtown;
	Image * yoshi;
	Image* toad1;

	
	/*------------------------------*/

	FRECT bottom = RectMake(0, 0, WINSIZEX * 4, 100.0f);
	FRECT bottom2 = RectMake(0, 100.0f, WINSIZEX * 4, 110.0f);

	FRECT NextMap = RectMake(WINSIZEX - 10.0f, 0, 10, WINSIZEY);
	//FRECT PrevMap = RectMake(WINSIZEX - WINSIZEX, 0, 10, WINSIZEY); 메인메뉴? 겸 세이브?
	
	FRECT NextMap2 = RectMake(WINSIZEX*2 - 10.0f, 0, 10, WINSIZEY);
	FRECT PrevMap2 = RectMake(WINSIZEX*2 - WINSIZEX, 0, 10, WINSIZEY);

	FRECT NextMap3 = RectMake(WINSIZEX*3 - 10.0f, 0, 10, WINSIZEY);
	FRECT PrevMap3 = RectMake(WINSIZEX*3 - WINSIZEX, 0, 10, WINSIZEY);

	//FRECT NextMap4 = RectMake(WINSIZEX*4 - 10.0f, 0, 10, WINSIZEY);  사냥터 맵
	FRECT PrevMap4 = RectMake(WINSIZEX*4 - WINSIZEX, 0, 10, WINSIZEY);

	FRECT Downtown2 = RectMake(WINSIZEX*1.3 + 50.0f, 0, 100, WINSIZEY);
	FRECT Downtown3 = RectMake(WINSIZEX*1.5-50.0f, WINSIZEY, 100, WINSIZEY*2);
	FRECT yoshibox= RectMake(WINSIZEX * 1.2, WINSIZEY, WINSIZEX * 1.3, WINSIZEY * 2);
	FRECT toad1box= RectMake(WINSIZEX * 1.7, WINSIZEY, WINSIZEX *1.8, WINSIZEY * 2);

	Village();
	~Village()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

