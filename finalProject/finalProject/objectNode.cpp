#include "stdafx.h"
#include "objectNode.h"



objectNode::objectNode()
{
	img = NULL;
	p = Point(0, 0);
	rc = { 0,0,0,0 };
	frameX = 0;
	frameY = 0;
}


objectNode::~objectNode()
{
}

HRESULT objectNode::init(const char* key, int x, int y, int sizeX, int sizeY)
{
	img = IMAGEMANAGER->findImage(key);

	p = Point( x,y );
	
	rc = RectMakeCenter(x, y, sizeX, sizeY);

	frameX = 0;
	frameY = 0;

	return S_OK;
}
void objectNode::update()
{
	rc = RectMakeCenter(p.x, p.y, 80,80);
}
void objectNode::render()
{
	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	if (img)
		img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);
}