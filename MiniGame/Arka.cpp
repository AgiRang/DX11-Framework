#include "stdafx.h"
#include "Arka.h"
#include <fstream>

Arka::Arka()

{
}


Arka::~Arka()
{
}

HRESULT Arka::init()
{
	vector<tagPeople> vPeople;
	
	ifstream in;

	in.open("save/����2.txt", ios::in);

	int NumHuman;

	if (in.is_open())
	{
		in >> NumHuman;
		//����� ��ŭ ����ü �����迭 �����
		vPeople.resize(NumHuman);
		for (int i = 0; i < NumHuman; i++)
		{
			in >> vPeople[i].Id;//�̸�����
			int knowNum;
			in >> knowNum;//�˰��ִ� ��� �� ����
			for (int j = 0; j < knowNum; j++)
			{
				int know;
				in >> know;//�˰��ִ� ��� ����
				vPeople[i].vecAnswer.emplace_back(know);
			}
		}
		in.clear();
		in.close();
	}

	//int b = 9;
	//int* a;
	//a = &b;
	//int& c = b;


	vPeople[0].isHuman = true;

	vector<tagPeople*> vPeopleList;
	vPeopleList.emplace_back(&vPeople[0]);
	//��������ʴٸ� ���ѹݺ�
	while (!vPeopleList.empty())
	{
		//������ �ǳ����� �޾ƿ´�
		tagPeople* backPointer = vPeopleList.back();
		//�޾ƿ� �ǳ��� ���Ϳ��� ���ش�
		vPeopleList.pop_back();
		for (int i = 0; i < backPointer->vecAnswer.size(); i++)
		{
			//�˰��ִ� ��� �̸�
			int nId = backPointer->vecAnswer[i];
			//������ Ž���ߴٸ� �ݺ��� ����ġ��
			if (vPeople[nId - 1].isHuman)continue;
			//������� Ȯ��
			vPeople[nId - 1].isHuman = true;
			//Ž���� ���Ϳ� �߰�
			vPeopleList.emplace_back(&vPeople[nId - 1]);
		}
	}
	int Count = 0;

	for (int i = 0; i < NumHuman; i++)
	{
		if (vPeople[i].isHuman)Count++;
	}
	cout << "��¥�����" << Count << endl;

	return S_OK;
}

void Arka::release()
{

}

void Arka::update()
{
}

void Arka::render()
{
}
