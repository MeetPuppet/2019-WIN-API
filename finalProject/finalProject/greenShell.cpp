#include "stdafx.h"
#include "greenShell.h"



greenShell::greenShell()
{
}


greenShell::~greenShell()
{
}


HRESULT greenShell::init(int x, int y, int sizeX, int sizeY)
{
	objectNode::init("greenShell", x, y, sizeX, sizeY);
	timenum = 0;
	return S_OK;
}
void greenShell::update()
{
	objectNode::update();
	timenum++;
	if (timenum > 100) {
		if (frameX == 0) {
			frameX = 1;
		}
		else
			frameX = 0;
	}
	if (timenum > 500) {

	}
}

void greenShell::render()
{
	objectNode::render();
}