#include "stdafx.h"
#include "Mario.h"

#include "objectManger.h"
#include "Stage1.h"

#define SPEED 400
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

	char str[256];
	sprintf_s(str, "x, y, speed : %f %f %f",point.x,point.y, speed);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
}
//´þ¾î½áÁø Å°¼Â
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
		speed = SPEED * time;
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (rc.right < 1200) {
				point.x = point.x + speed;
				frameY = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (rc.left > 0) {
				point.x = point.x - speed;
				frameY = 1;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && mode != PM_SMALL) {
			state = PS_SIT;
		}
		else {
			frameX = 0;
			state = PS_IDLE;
		}
		frameCount -= time;
		if (frameCount < 0) {
			frameCount += FRAMETIME;
			frameX += 1;
			if(frameX >= 4){
				frameX = 1;
			}
		}
		break;
	case PS_JUMP:
		speed = SPEED * time;
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

		//¹Ù´Ú¿¡ ´êÀ¸¸é IDLE·Î
		if (om->collisionTile(rc, point.y) && jumpPower < 0) {
			frameX = 0;
			state = PS_IDLE;
		}
		if (stage->collisionTile(rc, point.y) && jumpPower < 0) {
			frameX = 0;
			state = PS_IDLE;
		}
		break;
	case PS_SIT:
		//Å¬¶§¸¸ ¸ÔÈ÷°Ô
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