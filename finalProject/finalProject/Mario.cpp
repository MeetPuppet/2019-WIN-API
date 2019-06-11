#include "stdafx.h"
#include "Mario.h"

#include "objectManger.h"
#include "Stage1.h"

#define SPEED 400
#define SPEE2 800
#define JUMPSPEED 6
#define FRAMETIME 0.1

Mario::Mario()
{
}


Mario::~Mario()
{
}

HRESULT Mario::init(Point p)
{
	IMAGEMANAGER->addFrameImage("Mario", "image/player/mario.bmp", 560, 320, 7, 2, true, RGB(255, 0, 255));
	playerNode::init(IMAGEMANAGER->addFrameImage("littleMario", "image/player/littlemario.bmp", 560, 160, 7, 2, true, RGB(255, 0, 255))
		,p);


	return S_OK;
}
void Mario::update()		   
{    
	if (state == PS_DEAD) {
		//죽을때 돌릴 부분
	}
	else {
		playerNode::update();
	}
}
void Mario::render()		   
{
	if (KEYMANAGER->isToggleKey(VK_F3)) {
		Rectangle(getMemDC(), foot.left, foot.top, foot.right, foot.bottom);
		for (int i = 0; i < 2; ++i) {
			Rectangle(getMemDC(), checkPos[i].left, checkPos[i].top, checkPos[i].right, checkPos[i].bottom);
		}
		Rectangle(getMemDC(), CollisionRC.left, CollisionRC.top, CollisionRC.right, CollisionRC.bottom);
		char str[256];
		sprintf_s(str, "rc, y : %d %d %f", rc.left, rc.top, point.y);
		TextOut(getMemDC(), 0, 60, str, strlen(str));
		for (int i = 0; i < 2; ++i) {
			sprintf_s(str, "%d", i);
			TextOut(getMemDC(), checkPos[i].left + 10, checkPos[i].top + 10, str, strlen(str));
			sprintf_s(str, "rc : %d %d %d %d", checkPos[i].left, checkPos[i].top, checkPos[i].right, checkPos[i].bottom);
			TextOut(getMemDC(), 0, 80 + (i * 20), str, strlen(str));
			sprintf_s(str, "tileIndex : %d", tileIndex[i]);
			TextOut(getMemDC(), 200, 80 + (i * 20), str, strlen(str));
		}
	}
	playerNode::render();


	
}
//덥어써진 키셋
void Mario::keySet()		   
{
	switch (state)
	{
	case PS_IDLE:
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			frameX = 1;
			frameY = 0;
			state = PS_MOVE;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			frameX = 1;
			frameY = 1;
			state = PS_MOVE;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && mode != PM_SMALL) {
			state = PS_SIT;
		}
		break;
	case PS_MOVE:
		//gravityChecker(true);
		if (KEYMANAGER->isStayKeyDown(VK_RSHIFT)) {
			if (IFS < SPEE2)
				IFS += SPEE2 * time;
		}
		else {
			if (IFS > SPEED) {
				IFS -= SPEED * time;
			}
			else if (IFS < SPEED)
				IFS += SPEED * time;
		}
		speed = IFS * time; 
		if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
			frameX = 0;
			state = PS_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			if (mode != PM_SMALL)
				state = PS_SIT;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && moveChecker(true) && rc.right < 1200) {
			{
				point.x = point.x + speed;
				frameY = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && moveChecker(false) && rc.left > 0) {
			{
				point.x = point.x - speed;
				frameY = 1;
			}
		}
		frameCount -= time;
		if (frameCount < 0) {
			IFF = ((1000) - IFS);
			IFF = IFF / (SPEED * 10);
			frameCount += IFF;
			frameX += 1;
			if(frameX >= 4){
				frameX = 1;
			}
		}
		break;
	case PS_JUMP:
		if (KEYMANAGER->isStayKeyDown(VK_RSHIFT)) {
			if (IFS < SPEE2)
				IFS += SPEE2 * time;
		}
		else {
			if (IFS > SPEED + 10) {
				IFS -= SPEED * time;
			}
			else if (IFS < SPEED)
				IFS += SPEED * time;
		}
		speed = IFS * time;
		frameX = 5;
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && moveChecker(true) && rc.right < 1200) {
			{
				point.x = point.x + speed;
				frameY = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && moveChecker(false) && rc.left > 0) {
			{
				point.x = point.x - speed;
				frameY = 1;
			}
		}
		if (jumpPower > 0) {
			gravityChecker(false);
		}
		else {
			gravityChecker(true);
		}
		jumpPower = jumpPower - JUMPSPEED *2*time;
		point.y = point.y - jumpPower;

		//바닥에 닿으면 IDLE로
		//if (jumpPower < 0 && om->collisionTile(foot, point.y) ) {
		//	//여기서는 ox만 받아서 오브젝트 충돌
		//}
		//if (jumpPower < 0 && stage->collisionTile(foot, point.y)) {
		//	frameX = 0;
		//	state = PS_IDLE;
		//}
		break;
	case PS_SIT:
		//클때만 먹히게
		frameX = 6; 
		if (IFS > 0) {
			IFS -= SPEED * time;
			speed = IFS * time;
			if (frameY == 0 && moveChecker(true)) {
				point.x = point.x + speed;
			}
			else if(frameY == 1 && moveChecker(false)) {
				point.x = point.x - speed;
			}
		}
		else {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) {
			frameX = 0;
			state = PS_IDLE;
		}
		break;
	}

	if (KEYMANAGER->isOnceKeyDown('Q')) {
		if (mode == PM_SMALL) {
			mode = PM_BIG;
		}
		else {
			mode = PM_SMALL;
		}
	}
	switch (mode)
	{
	case PM_SMALL:
		img = IMAGEMANAGER->findImage("littleMario");
		break;
	case PM_BIG:
		img = IMAGEMANAGER->findImage("Mario");
		break;
	case PM_FIRE:
		break;
	}
}
