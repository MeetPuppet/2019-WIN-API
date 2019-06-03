#pragma once
#include "stageNode.h"
#include "tileNode.h"
class Stage1 :
	public stageNode
{
private:
public:
	Stage1();
	~Stage1();

	HRESULT init();
	void update();
	void release();
	void render();


};

