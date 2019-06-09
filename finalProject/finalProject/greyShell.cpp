#include "stdafx.h"
#include "greyShell.h"



greyShell::greyShell()
{
}


greyShell::~greyShell()
{
}

HRESULT greyShell::init(int x, int y, int sizeX, int sizeY)
{
	objectNode::init("greyShell", x, y, sizeX, sizeY);
	timenum = 0;
	return S_OK;
}
void greyShell::update()
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

void greyShell::render()
{
	objectNode::render();
}