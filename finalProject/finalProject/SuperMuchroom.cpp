#include "stdafx.h"
#include "SuperMuchroom.h"



SuperMuchroom::SuperMuchroom()
{
}


SuperMuchroom::~SuperMuchroom()
{
}

HRESULT SuperMuchroom::init(int x, int y)
{
	objectNode::init("Mushroom", x, y, 80, 80);

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