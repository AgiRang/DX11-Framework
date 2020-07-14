#pragma once
#include "GameNode.h"

//��Ƽ �������� �ʿ��� stl
#include <thread>
#include <mutex>

static mutex mtx;

class Loading : public GameNode
{
public:
	Loading();
	~Loading()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	static int LoadingNum;


	static void func1()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "������ 1 �۵���" << endl;
		}


	}

	static void func2(int a)
	{
		for (int i = 0; i < a; i++)
		{
			cout << "������ 2 �۵���" << endl;
		}
	}
	static void func3(int a,int b)
	{
		for (int i = 0; i < a; i++)
		{
			Rect* rc = new Rect();
			cout << b<<"�����忡�� ����" << endl;
			SAFE_DELETE(rc);
			LoadingNum++;
			cout << "�ε�:"<< LoadingNum << endl;
			//������ ������ �ƴ� UNITMANAGER->add(rc)
		}
	}
	static void func4(int a, int b)
	{
		D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
		CAMMANAGER->SetBuffers();
		Rect* Rc = IMGMANAGER->Getrect();
		Rc->Position(400.0f, 300.0f);
		Rc->Color(1.0f, 0.0f,0.0f);

		for (int i = 0; i < a; i++)
		{
			Rect* rc = new Rect();
			LoadingNum++;

			if (LoadingNum % 10 == 0)
			{
				mtx.lock();
				
				DeviceContext->ClearRenderTargetView(RTV, (float *)background);
				//////////////////
				//Sleep(100);
				Rc->Scale((float)LoadingNum/500.f*WINSIZEX, 100.0f);
				Rc->Render();
				/////////////
				SwapChain->Present(0, 0);
				mtx.unlock();
			}

			SAFE_DELETE(rc);
		}
	}
};

