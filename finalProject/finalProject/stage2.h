#pragma once
#include "stageNode.h"
#include "tileNode.h"
class stage2 :
	public stageNode
{
public:
	stage2();
	~stage2();
	HRESULT init();
	void update();
	void release();
	void render();
};

