#include "stdafx.h"
#include "objectNode.h"



objectNode::objectNode()
{
}


objectNode::~objectNode()
{
}

HRESULT objectNode::init(RECT rect)
{
	p = { (rect.right - rect.left) + rect.left,
		(rect.bottom - rect.top) + rect.top, };
	
	rc = rect;

	return S_OK;
}
void objectNode::update()
{
}
void objectNode::render()
{
}