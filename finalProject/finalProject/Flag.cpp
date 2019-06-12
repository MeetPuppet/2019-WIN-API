#include "stdafx.h"
#include "Flag.h"



Flag::Flag()
{
}


Flag::~Flag()
{
}

HRESULT Flag::init(int x, int y)
{
	objectNode::init("Flag", x, y, 80, 80);

	return S_OK;
}
void Flag::update()								 
{
	objectNode::update();
}
void Flag::render()								 
{
	objectNode::render();
}