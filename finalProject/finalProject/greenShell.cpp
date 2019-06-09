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

	return S_OK;
}
void greenShell::update()
{
	objectNode::update();
}

void greenShell::render()
{
	objectNode::render();
}