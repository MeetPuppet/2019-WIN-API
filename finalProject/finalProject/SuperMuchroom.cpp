#include "stdafx.h"
#include "SuperMuchroom.h"



SuperMuchroom::SuperMuchroom()
{
}


SuperMuchroom::~SuperMuchroom()
{
}

HRESULT SuperMuchroom::init(int x, int y, int sizeX, int sizeY)
{
	objectNode::init("Mushroom", x, y, sizeX, sizeY);

	return S_OK;
}
void SuperMuchroom::update()
{
	objectNode::update();
}
void SuperMuchroom::render()
{
	objectNode::render();
}