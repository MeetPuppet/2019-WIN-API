#pragma once
#include "objectNode.h"
class greenShell :
	public objectNode
{
public:
	greenShell();
	~greenShell();

	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();

};

