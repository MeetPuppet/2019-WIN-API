#include "stdafx.h"
#include "Luigi.h"

#include "objectManger.h"
#include "Stage1.h"

#define SPEED 400
#define SPEE2 800
#define JUMPSPEED 6
#define FRAMETIME 0.1


Luigi::Luigi()
{
}


Luigi::~Luigi()
{
}

HRESULT Luigi::init(Point p)
{
	IMAGEMANAGER->addFrameImage("Luigi", "image/player/Luigi.bmp", 560, 320, 7, 2, true, RGB(255, 0, 255));
	playerNode::init(IMAGEMANAGER->addFrameImage("littleLuigi", "image/player/littleluigi.bmp", 560, 160, 7, 2, true, RGB(255, 0, 255))
		, p);


	return S_OK;
}
void Luigi::update()
{
	if (state == PS_DEAD) {
		//죽을때 돌릴 부분
		time = TIMEMANAGER->getElapsedTime();
		if (time < 0 || time > 10) time = 0.16f;
		jumpPower = jumpPower - JUMPSPEED * 2 * time;
		point.y = point.y - jumpPower;
		rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());

	}
	else {
		playerNode::update();
	}
}
void Luigi::render()
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
void Luigi::keySet()
{
	switch (state)
	{
	case PS_IDLE:
		if (KEYMANAGER->isStayKeyDown('D')) {
			frameX = 1;
			frameY = 0;
			state = PS_MOVE;
		}
		else if (KEYMANAGER->isStayKeyDown('A')) {
			frameX = 1;
			frameY = 1;
			state = PS_MOVE;
		}
		else if (KEYMANAGER->isStayKeyDown('W')) {
			SOUNDMANAGER->play("11.jump");
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		else if (KEYMANAGER->isStayKeyDown('S') && mode != PM_SMALL) {
			state = PS_SIT;
		}
		break;
	case PS_MOVE:
		//gravityChecker(true);
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT)) {
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
		if (!KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('A')) {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
			frameX = 0;
			state = PS_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('S')) {
			if (mode != PM_SMALL)
				state = PS_SIT;
		}
		if (KEYMANAGER->isStayKeyDown('W')) {
			SOUNDMANAGER->play("11. jump", 1.0f);
			frameX = 5;
			jumpPower = JUMPSPEED * 2;
			state = PS_JUMP;
		}
		if (KEYMANAGER->isStayKeyDown('D') && moveChecker(true) && rc.right < 1200) {
			point.x = point.x + speed;
			frameY = 0;
		}
		else if (KEYMANAGER->isStayKeyDown('A') && moveChecker(false) && rc.left > 0) {
			point.x = point.x - speed;
			frameY = 1;
		}
		frameCount -= time;
		if (frameCount < 0) {
			IFF = ((1000) - IFS);
			IFF = IFF / (SPEED * 10);
			frameCount += IFF;
			frameX += 1;
			if (frameX >= 4) {
				frameX = 1;
			}
		}
		break;
	case PS_JUMP:
		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT)) {
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
		if (KEYMANAGER->isStayKeyDown('D') && moveChecker(true) && rc.right < 1200) {
			point.x = point.x + speed;
			frameY = 0;
		}
		else if (KEYMANAGER->isStayKeyDown('A') && moveChecker(false) && rc.left > 0) {
			point.x = point.x - speed;
			frameY = 1;
		}
		if (jumpPower > 0) {
			gravityChecker(false);
		}
		else {
			gravityChecker(true);
		}
		jumpPower = jumpPower - JUMPSPEED * 2 * time;
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
			else if (frameY == 1 && moveChecker(false)) {
				point.x = point.x - speed;
			}
		}
		else {
			IFS = 0;
			IFF = ((SPEE2)-IFS);
			IFF = IFF / (SPEED * 10);
			frameCount = IFF;
		}
		if (KEYMANAGER->isOnceKeyUp('S')) {
			frameX = 0;
			state = PS_IDLE;
		}
		break;
	}

	if (KEYMANAGER->isToggleKey('E')) {
		mode = PM_BIG;
	}

	switch (mode)
	{
	case PM_SMALL:
		img = IMAGEMANAGER->findImage("littleLuigi");
		break;
	case PM_BIG:
		img = IMAGEMANAGER->findImage("Luigi");
		break;
	case PM_FIRE:
		break;
	}
}
