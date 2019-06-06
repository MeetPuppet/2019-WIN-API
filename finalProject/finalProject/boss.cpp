#include "stdafx.h"
#include "boss.h"

#define SPEED 70

boss::boss()
{
	Img = NULL;
	state = BL_PATROL;
	p = { 0,0 };
	rc = { 0,0,0,0 };

	FrameCheck = 0.2;
	speed = 0;
	gravity = 0;

	JUMP = TRUE;

	frameX = 0;
	frameY = 0;
	jumpnum = 0;
	targetPoint = NULL;
}


boss::~boss()
{

}

HRESULT boss::init(int x,int y)
{
	Img = IMAGEMANAGER->findImage("bowser");
	p.x = x;
	p.y = y;
	rc = RectMakeCenter(p.x, p.y, Img->getFrameWidth(), Img->getFrameHeight());

	return S_OK;
}
void boss::release()
{
}
void boss::update()
{
	rc = RectMakeCenter(p.x, p.y, Img->getFrameWidth(), Img->getFrameHeight());
	p.x += 1;
	FrameSeter();
	
	if (JUMP == TRUE) {
		p.y -= 5;
		jumpnum++;
	}
	if (JUMP == FALSE) {
		p.y += 5;
		jumpnum--;
	}
	if (jumpnum == 40) {
		JUMP = FALSE;
	}
	if (jumpnum == 0) {
		JUMP = TRUE;
	}
}
void boss::render()
{
	Img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);
}

B_STATE boss::getState()
{
	return state;
}
void boss::FrameSeter()
{
	//frameY
	switch (state)
	{
	case BL_PATROL:
	case BL_CHASE:
	case BL_BRESS:
		frameY = 0;
		break;
	case BR_PATROL:
	case BR_CHASE:
	case BR_BRESS:
		frameY = 1;
		break;
	case B_DEAD:
		break;
	}
	
	//frameX
	switch (state)
	{
	case BL_PATROL:
		break;
	case BR_PATROL:
		break;
	case BL_CHASE:
		break;
	case BR_CHASE:
		break;
	case BL_BRESS:
		break;
	case BR_BRESS:
		break;
	case B_DEAD:
		break;
	}

	if (FrameCheck < 0) {
		FrameCheck += 0.2;
		if (Img->getMaxFrameX() > frameX) {
			frameX += 1;
		}
		else {
			frameX = 0;
		}
	}
	else
	{
		if (TIMEMANAGER->getElapsedTime() < 0) {
			FrameCheck -= 0.1;
		}
		else
			FrameCheck -= TIMEMANAGER->getElapsedTime();
	}



	//switch (state)
	//{
	//case BL_PATROL:
	//case BL_CHASE:
	//case R_PATROL:
	//case ER_CHASE:
	//	if (img->getMaxFrameX() > FrameCheck) {
	//		FrameCheck += ENEMY_FRAME_SPEEDER * TIMEMANAGER->getElapsedTime();
	//		if (FrameCheck >= 2) {
	//			frameX = 1;
	//		}
	//		else
	//			frameX = FrameCheck;
	//	}
	//	else {
	//		FrameCheck = 0;
	//		frameX = FrameCheck;
	//	}
	//	break;
	//case DEAD:
	//	frameX = 2;
	//	break;
	//}
}

void boss::AI(POINT* playerPoint)
{

}