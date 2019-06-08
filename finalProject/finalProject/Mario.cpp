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
	playerNode::update();
}
void Mario::render()		   
{
	playerNode::render();

	Rectangle(getMemDC(), foot.left, foot.top, foot.right, foot.bottom);

	char str[256];
	sprintf_s(str, "x, y, speed : %f %f %f",point.x,point.y, IFF);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
}
//덥어써진 키셋
void Mario::keySet()		   
{
	int maxSpeed=0;
	float nulll = 0;;
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
		if (KEYMANAGER->isStayKeyDown('X')) {
			if (IFS < SPEE2)
				IFS += SPEE2 * time;
		}
		else {
			if (IFS > SPEED+10) {
				IFS -= SPEED * time;
			}
			else if (IFS < SPEED)
				IFS += SPEED * time;
		}
		speed = IFS * time;
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
			frameX = 0;
			state = PS_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (rc.right < 1200 && !stage->collisionTile(rc, nulll)) {
				point.x = point.x + speed;
				frameY = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (rc.left > 0 && !stage->collisionTile(rc, nulll)) {
				point.x = point.x - speed;
				frameY = 1;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && mode != PM_SMALL) {
			state = PS_SIT;
		}
		frameCount -= time;
		if (frameCount < 0) {
			IFF = ((SPEE2) - IFS);
			IFF = IFF / (SPEED * 10);
			frameCount += IFF;
			frameX += 1;
			if(frameX >= 4){
				frameX = 1;
			}
		}
		break;
	case PS_JUMP:
		if (KEYMANAGER->isStayKeyDown('X')) {
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
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			point.x = point.x + speed;
			frameY = 0;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			point.x = point.x - speed;
			frameY = 1;
		}
		jumpPower = jumpPower - JUMPSPEED *2*time;
		point.y = point.y - jumpPower;

		//바닥에 닿으면 IDLE로
		if (jumpPower < 0 && om->collisionTile(foot, point.y) ) {
			//여기서는 ox만 받아서 오브젝트 충돌
		}
		if (jumpPower < 0 && stage->collisionTile(foot, point.y)) {
			frameX = 0;
			state = PS_IDLE;
		}
		break;
	case PS_SIT:
		//클때만 먹히게
		frameX = 6;
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) {
			frameX = 0;
			state = PS_IDLE;
		}
		break;
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