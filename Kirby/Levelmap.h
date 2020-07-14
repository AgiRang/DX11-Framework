#pragma once
#include "GameNode.h"

class Levelmap :public GameNode
{
public:

	Image * Levelmaps;
	Image * LevelBackgrounds1;
	Image * LevelBackgrounds2;
	Image * LevelBackgrounds3;
	Image * LevelBackgrounds4;
	Image * LevelBackgrounds5;
	Image * LevelBackgrounds6;


	Levelmap();
	~Levelmap()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

