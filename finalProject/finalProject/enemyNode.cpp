#include "stdafx.h"
#include "enemyNode.h"

#include "Stage1.h"

#define SPEED 50

enemyNode::enemyNode()
{
	img = NULL;
	p(0,0);
	speed = 0;
	gravity = 0;
	FrameCheck = 0;
	state = EL_PATROL;
	targetPoint = NULL;

	frameX=0;
	frameY=0;
}


enemyNode::~enemyNode()
{
	release();
}
HRESULT enemyNode::init(const char* keyName, Point point)
{
	img = IMAGEMANAGER->findImage(keyName);

	FrameCheck = img->getFrameX();
	p = point;

	rc = RectMakeCenter(p.x, p.y, img->getFrameWidth(), img->getFrameHeight());

	return S_OK;
}
void enemyNode::release()
{
}
void enemyNode::update() 
{
	AI(targetPoint);
	time = TIMEMANAGER->getElapsedTime();
	if (time < 0 || time > 10) 
		time = 0.016;
	speed = SPEED * time;
	
	switch (state)
	{
	case EL_PATROL:
	case EL_CHASE:
		FrameSeter();
		p.x -= speed;
		break;
	case ER_PATROL:
	case ER_CHASE:
		FrameSeter();
		p.x += speed;
		break;
	case DEAD:

		break;
	}


	//충돌할 위치 지속적으로 최신화
	rc = RectMakeCenter(p.x, p.y, img->getFrameWidth(), img->getFrameHeight());
}
void enemyNode::render() 
{
	if (KEYMANAGER->isToggleKey(VK_F3)) {
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		for (int i = 0; i < 2; ++i) {
			Rectangle(getMemDC(), checkPos[i].left, checkPos[i].top, checkPos[i].right, checkPos[i].bottom);
		}
		
	}
	//충돌 확인용
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);

	//스프라이트 애니메이션 체크용
	//char str[256];
	//sprintf_s(str, "enemy POINT : %.0f, %.0f,%.2f", p.x,p.y, speed);
	//TextOut(getMemDC(), 0, 60, str, strlen(str));
}
void enemyNode::FrameSeter()
{
	if (state == DEAD) return;
	if (img->getMaxFrameX() > FrameCheck) {
		FrameCheck += ENEMY_FRAME_SPEEDER * time;
	}
	else {
		FrameCheck = 0;
	}
	frameX = FrameCheck;

	switch (state)
	{
	case EL_PATROL:
	case EL_CHASE:
		frameY = 0;
		break;
	case ER_PATROL:
	case ER_CHASE:
		frameY = 1;
		break;
	case DEAD:

		break;
	}
}


void enemyNode::AI(POINT* playerPoint)
{
	if (state == DEAD) return;
	if (playerSearch(playerPoint)) {
		if (playerPoint->x > p.x) {
			state = ER_CHASE;
		}
		else {
			state = EL_CHASE;
		}
	}
	else {
		if (frameY == 1) {
			state = ER_PATROL;
		}
		else {
			state = EL_PATROL;
		}
	}
}
//최하단부 AI 판단용 함수
inline bool enemyNode::playerSearch(POINT* playerPoint)
{
	if (playerPoint == NULL) return false;
	//플레이어와 거리판단
	float distance = getDistance(playerPoint->x, playerPoint->y, p.x, p.y);

	//플레이어와의 거리가 200 이하있때 참
	if (distance < 200) {
		return true;
	}
	return false;
}