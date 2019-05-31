#include "stdafx.h"
#include "Goomba.h"

#define SPEED 50

Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

HRESULT Goomba::init(POINT point)
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
	if (img->getMaxFrameX() > FrameCheck) {
		FrameCheck += ENEMY_FRAME_SPEEDER * TIMEMANAGER->getElapsedTime();
		if (FrameCheck >= 2) {
			frameX = 1;
		}
		else
			frameX = FrameCheck;
	}
	else{
		FrameCheck = 0;
		frameX = FrameCheck;
	}
}

void Goomba::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}