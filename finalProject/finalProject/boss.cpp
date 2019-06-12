#include "stdafx.h"
#include "boss.h"
#include "objectManger.h"
#include "Stage1.h"

#define SPEED 70
#define JUMPSPEED 6
boss::boss()
{
	Img = NULL;
	state = BL_PATROL;
	p = { 0,0 };
	rc = { 0,0,0,0 };

	FrameCheck = 0.2;
	jumpPower = 0;
	time = 0;

	JUMP = TRUE;

	frameX = 0;
	frameY = 0;
	jumpnum = 2 * JUMPSPEED;
	frameNum = 0;
	targetPoint = NULL;
	movenum = FALSE;
	FireNum = 0;
}	


boss::~boss()
{

}

HRESULT boss::init(int x,int y,int g1,int g2)
{
	Img = IMAGEMANAGER->findImage("bowser");
	p.x = x;
	p.y = y;
	oldpx = x;
	oldpy = y;
	groundx1 = g1;
	groundx2 = g2;
	rc = RectMakeCenter(p.x, p.y, Img->getFrameWidth(), Img->getFrameHeight());

	return S_OK;
}
void boss::release()
{
}
void boss::update()
{
	time = TIMEMANAGER->getElapsedTime();
	if (time < 0) time = 0.016;
	rc = RectMakeCenter(p.x, p.y, Img->getFrameWidth(), Img->getFrameHeight());
	//if (state == BL_BRESS || state == BL_CHASE || state == BL_PATROL) {
	if (state != B_DEAD) {
		if (movenum == TRUE) {
			p.x -= 3;
		}
		else if (movenum == FALSE) {
			p.x += 3;
		}
		FrameSeter();
		FireNum += 1;
		//if (JUMP == TRUE) {
		//	p.y -= 5 * cos((3.1415926535 / 180) * jumpnum);
		//	jumpnum += 3;
		//}
		//if (JUMP == FALSE) {
		//	p.y += 5 * sin((3.1415926535 / 180) * jumpnum);
		//	jumpnum -= 3;
		//}
		//if (jumpnum == 90) {
		//	JUMP = FALSE;
		//}
		//if (jumpnum == 0) {
		//	JUMP = TRUE;
		//}
		jumpnum -= JUMPSPEED * 2 * 0.02;
		p.y -= jumpnum;
		if (jumpnum < 0 && p.y > WINSIZEY * 3 / 4) {
			jumpnum = JUMPSPEED * 2;
		}

		if (p.x < oldpx - groundx1) {
			movenum = FALSE;
			//if (state == BL_PATROL) {
			//	state = BR_PATROL;
			//}
			//if (state == BL_CHASE) {
			//	state = BR_CHASE;
			//}
			//if (state == BL_BRESS) {
			//	state = BR_BRESS;
			//}
		}
		if (p.x > oldpx + groundx2) {
			movenum = TRUE;
			//if (state == BR_PATROL) {
			//	state = BL_PATROL;
			//}
			//if (state == BR_CHASE) {
			//	state = BL_CHASE;
			//}
			//if (state == BR_BRESS) {
			//	state = BL_BRESS;
			//}
		}
	}
	else {
		jumpPower = jumpPower - JUMPSPEED * 2 * time;
		p.y = p.y - jumpPower;
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
Point boss::getPoint()
{
	return p;
}
int boss::getFireNum()
{
	return FireNum;
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
	
	switch (state)
	{
	case BL_BRESS:
		break;
	case BR_BRESS:
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