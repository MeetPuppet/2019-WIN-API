#pragma once
#include "gameNode.h"
class decorator :
	public gameNode
{
public:
	decorator();
	~decorator();
	HRESULT init();
	void update();
	void render();
};

