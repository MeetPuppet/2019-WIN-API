#include "stdafx.h"
#include "fireShot.h"



fireShot::fireShot()
{
}


fireShot::~fireShot()
{
}

HRESULT fireShot::init(int x, int y,int sizeX,int sizeY,int Move)
{
	objectNode::init("fireShot", x, y, sizeX, sizeY);
	move = Move;
	return S_OK;
}
void fireShot::release()
{
}
void fireShot::update()
{
	objectNode::update();
	frameX++;
	if (frameX == 2) {
		frameX = 0;
	}
	if (move == 1) {
		p.x -= 5;
	}
	else if (move == 2) {
		p.x += 5;
	}
	// if (ÇÇ°Ý½Ã)
		// move = 0;
}
void fireShot::render()
{
	if (move) {
		objectNode::render();
	}
}
