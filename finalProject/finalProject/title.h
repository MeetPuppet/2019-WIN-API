#pragma once
#include "gameNode.h"
class title :
	public gameNode
{
private:
	int mode;
	POINT point[2];

	BYTE alpha;
	bool choose;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	title();
	~title();
};

