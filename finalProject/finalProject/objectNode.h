#pragma once
#include "gameNode.h"
class objectNode :
	public gameNode
{
private:
	POINT p;
	RECT rc;
public:
	objectNode();
	~objectNode();
	HRESULT init(RECT rect);
	void update();
	void render();


};

