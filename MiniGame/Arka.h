#pragma once
#include "GameNode.h"

struct tagPeople
{
	//�̸�
	int Id;
	//����ΰ�
	bool isHuman;
	//�˰��ִ� �����
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

