#pragma once
#include "GameNode.h"
class Shop :public GameNode
{
public:

	Image * downtown;
	Image * yoshi;
	Image* toad1;

	Shop();
	~Shop()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	
};

