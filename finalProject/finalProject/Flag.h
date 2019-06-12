#pragma once
#include "objectNode.h"
class Flag :
	public objectNode
{
public:
	Flag();
	~Flag();
	HRESULT init(int x, int y);
	void update();
	void render();
};

