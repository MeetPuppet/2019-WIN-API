#include "stdafx.h"
#include "enemyNode.h"

#define SPEED 50

enemyNode::enemyNode()
{
	img = NULL;
	p = { 0,0 };
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
HRESULT enemyNode::init(const char* keyName,POINT point)
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
	speed = SPEED * TIMEMANAGER->getElapsedTime();
	
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
	//충돌 확인용
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);

	//스프라이트 애니메이션 체크용
	//char str[256];
	//sprintf_s(str, "enemy frameX : %f", FrameCheck);
	//TextOut(getMemDC(), 0, 60, str, strlen(str));
}
void enemyNode::FrameSeter()
{
	if (img->getMaxFrameX() > FrameCheck) {
		FrameCheck += ENEMY_FRAME_SPEEDER * TIMEMANAGER->getElapsedTime();
	}
	else {
		FrameCheck = 0;
	}
	frameX = FrameCheck;
}


void enemyNode::AI(POINT* playerPoint)
{
	if (playerSearch(playerPoint)) {
		if (playerPoint->x > p.x) {
			state = ER_CHASE;
		}
		else {
			state = EL_CHASE;
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