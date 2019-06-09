#pragma once
#include "objectNode.h"
class greyShell :
	public objectNode
{
private:
	int timenum;
public:
	greyShell();
	~greyShell();

	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();
};

