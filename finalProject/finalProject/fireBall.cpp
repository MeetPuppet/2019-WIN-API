#include "stdafx.h"
#include "fireBall.h"



fireBall::fireBall()
{
}


fireBall::~fireBall()
{
}

HRESULT fireBall::init(int x, int y,int sizeX,int sizeY,int Move)
{
	objectNode::init("fireBall", x, y, sizeX, sizeY);
	move = Move;
	return S_OK;
}
void fireBall::release()
{
}
void fireBall::update()
{
	objectNode::update();
	frameX++;
	if (frameX == 4) {
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
void fireBall::render()
{
	if (move) {
		objectNode::render();
	}
}
