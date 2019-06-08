#include "stdafx.h"
#include "firanhaFlower.h"



firanhaFlower::firanhaFlower()
{
}


firanhaFlower::~firanhaFlower()
{
}

HRESULT firanhaFlower::init(POINT point)
{
	enemyNode::init("firanhaFlower", point);

	move = TRUE;
	return S_OK;
}
void firanhaFlower::release()
{
}
void firanhaFlower::update()
{
	if (move) {
		p.y -= 5;
	}
	else
		p.y += 5;
	if (p.y < 300) {
		move = FALSE;
	}
	if (p.y > 600) {
		move = TRUE;
	}
}
void firanhaFlower::render()
{
	enemyNode::render();
}

void firanhaFlower::FrameSeter()
{
	switch (state)
	{
	case EL_PATROL:
	case ER_PATROL:
		if (img->getMaxFrameX() > FrameCheck) {
			FrameCheck += 1 * TIMEMANAGER->getElapsedTime();
			if (FrameCheck >= 2) {
				frameX = 1;
			}
			else
				frameX = FrameCheck;
		}
		else {
			FrameCheck = 0;
			frameX = FrameCheck;
		}
		break;
	case EL_CHASE:
	case ER_CHASE:
		break;
	case DEAD:
		frameX = 2;
		break;
	}
}

void firanhaFlower::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}