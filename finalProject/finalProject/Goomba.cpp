#include "stdafx.h"
#include "Goomba.h"

#define SPEED 50

Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

HRESULT Goomba::init(Point point)
{
	enemyNode::init("Goomba", point);

	return S_OK;
}
void Goomba::release()
{
}
void Goomba::update()
{
	enemyNode::update();
}
void Goomba::render()
{
	enemyNode::render();
}

void Goomba::FrameSeter()
{
	switch (state)
	{
	case EL_PATROL:
	case EL_CHASE:
	case ER_PATROL:
	case ER_CHASE:
		if (img->getMaxFrameX() > FrameCheck) {
			FrameCheck += 1 * time;
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

void Goomba::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}