#include "stdafx.h"
#include "Stage1.h"

#define MAX TILEX*TILEY

Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}


HRESULT Stage1::init()
{
	stageNode::init("map/save1.map");

	return S_OK;
}

void Stage1::update()
{
	stageNode::update();
}

void Stage1::release()
{
}

void Stage1::render() 
{
	stageNode::render();
}
