#include "stdafx.h"
#include "goal.h"



goal::goal()
{
}


goal::~goal()
{
}

HRESULT goal::init()
{
	objectNode::init("Goal",12000 - 360, 65, 80, 540);

	return S_OK;
}
void goal::update()		 
{
	objectNode::update();
}
void goal::render()		 
{
	objectNode::render();
}