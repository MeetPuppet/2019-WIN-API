#pragma once
#include "objectNode.h"
class SuperMuchroom :
	public objectNode
{
public:
	SuperMuchroom();
	~SuperMuchroom();
	HRESULT init(int x, int y);
	void update();
	void render();

};

