#pragma once
#include "GameNode.h"

class MainGame :public GameNode
{
private:

public:
	Image *menu2;

	MainGame();
	~MainGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

};

