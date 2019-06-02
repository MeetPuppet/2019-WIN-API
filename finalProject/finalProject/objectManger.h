#pragma once
#include "gameNode.h"
class objectManger :
	public gameNode
{
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();
};

