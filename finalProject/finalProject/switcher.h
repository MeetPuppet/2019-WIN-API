#pragma once
#include "gameNode.h"


class switcher :
	public gameNode
{
private:
	RECT mg;
	RECT mt;
public:
	switcher();
	~switcher();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	SWITCHER whatSet() override { return SWITCH; }
};

