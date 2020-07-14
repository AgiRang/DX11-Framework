#pragma once
#include "SingletonBase.h"
class KirbyManager : public SingletonBase<KirbyManager>
{
private:
	class swordkirby* KIRBY;


public:
	KirbyManager() {};
	~KirbyManager() {};
	
	swordkirby * GETKIRBY() {return KIRBY; }
	void SETKIRBY(swordkirby * p) { KIRBY = p; }
	//MAKEGETSET(swordkirby *, KIRBY);


};

