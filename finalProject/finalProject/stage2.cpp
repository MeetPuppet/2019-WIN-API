#include "stdafx.h"
#include "stage2.h"



stage2::stage2()
{
}


stage2::~stage2()
{
}

HRESULT stage2::init()
{
	stageNode::init("map/save2.map");

	return S_OK;
}

void stage2::update()
{
	stageNode::update();
}

void stage2::release()
{
}

void stage2::render()
{
	stageNode::render();
}
