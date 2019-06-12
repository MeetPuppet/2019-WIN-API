#pragma once
#include "objectNode.h"

class goal :
	public objectNode
{
private:
	bool isPlay;
public:
	goal();
	~goal();
	HRESULT init();
	void update();
	void render();
};

