#pragma once
#include "objectNode.h"
class SuperMuchroom :
	public objectNode
{
public:
	SuperMuchroom();
	~SuperMuchroom();
	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();
};

