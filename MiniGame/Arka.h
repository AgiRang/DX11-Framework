#pragma once
#include "GameNode.h"

struct tagPeople
{
	//이름
	int Id;
	//사람인가
	bool isHuman;
	//알고있는 사람들
	vector<int> vecAnswer;
	tagPeople() :isHuman(false) {}
};




class Arka : public GameNode
{
private:



public:
	Arka();
	~Arka() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

