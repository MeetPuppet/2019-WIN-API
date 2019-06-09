#include "stdafx.h"
#include "greenTurtle.h"



greenTurtle::greenTurtle()
{
}


greenTurtle::~greenTurtle()
{
}

HRESULT greenTurtle::init(POINT point)
{
	enemyNode::init("greenTurtle", point);

	return S_OK;
}
void greenTurtle::release()
{
}
void greenTurtle::update()
{
	enemyNode::update();
}
void greenTurtle::render()
{
	enemyNode::render();
}

void greenTurtle::FrameSeter()
{
	switch (state)
	{
	case EL_PATROL:
	case EL_CHASE:
	case ER_PATROL:
	case ER_CHASE:
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
	case DEAD:
		frameX = 2;
		break;
	}
}

void greenTurtle::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}