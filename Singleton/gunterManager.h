#pragma once
#include "SingletonBase.h"
class Monster;
class gunterManager : public SingletonBase<gunterManager>
{
private:
	Monster* GUNTER;


public:
	gunterManager() {};
	~gunterManager() {};

	Monster * GETGUNTER() { return GUNTER; }
	void SETGUNTER(Monster * p) { GUNTER = p; }
	//MAKEGETSET(swordkirby *, KIRBY);


};

