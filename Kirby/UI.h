#pragma once
#include "GameNode.h"
class UI :public GameNode
{
public:

	Image * IF;
	Image * Armor;
	Image* Skill;

	UI();
	~UI()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	
};

