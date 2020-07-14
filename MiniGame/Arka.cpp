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

	in.open("save/마을2.txt", ios::in);

	int NumHuman;

	if (in.is_open())
	{
		in >> NumHuman;
		//사람수 만큼 구조체 동적배열 만들기
		vPeople.resize(NumHuman);
		for (int i = 0; i < NumHuman; i++)
		{
			in >> vPeople[i].Id;//이름저장
			int knowNum;
			in >> knowNum;//알고있는 사람 수 저장
			for (int j = 0; j < knowNum; j++)
			{
				int know;
				in >> know;//알고있는 사람 저장
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
	//비어있지않다면 무한반복
	while (!vPeopleList.empty())
	{
		//벡터의 맨끝값을 받아온다
		tagPeople* backPointer = vPeopleList.back();
		//받아온 맨끝은 벡터에서 빼준다
		vPeopleList.pop_back();
		for (int i = 0; i < backPointer->vecAnswer.size(); i++)
		{
			//알고있는 사람 이름
			int nId = backPointer->vecAnswer[i];
			//이전에 탐색했다면 반복문 지나치기
			if (vPeople[nId - 1].isHuman)continue;
			//사람임을 확인
			vPeople[nId - 1].isHuman = true;
			//탐색할 벡터에 추가
			vPeopleList.emplace_back(&vPeople[nId - 1]);
		}
	}
	int Count = 0;

	for (int i = 0; i < NumHuman; i++)
	{
		if (vPeople[i].isHuman)Count++;
	}
	cout << "진짜사람수" << Count << endl;

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
