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
		moveChecker(false);
		FrameSeter();
		p.x -= speed;
		break;
	case ER_PATROL:
	case ER_CHASE:
		moveChecker(true);
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
void enemyNode::moveChecker(bool isRight)
{
	//타일 검출용
	RECT CollisionRC;
	int tileX, tileY;

	CollisionRC = rc;

	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	CollisionRC.left -= 10;
	CollisionRC.right += 10;
	CollisionRC.top += 5;
	CollisionRC.bottom -= 5;

	//예로 10*16에 위치한다면
	//시작점은 720 ,1200,800,1280으로 left top이다
	tileX = CollisionRC.left / TILESIZE;
	//고로 X는 9
	tileY = CollisionRC.top / TILESIZE;
	//Y는 15가 된다.c


	if (isRight) {//우측
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
	}
	else {//좌측
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
	}
	//이 두개의 인덱스를 가지고 수작을 부린다.

	CollisionRC = rc;
	if (isRight) {//우측
		CollisionRC.left += 10;
		CollisionRC.right += 10;
	}
	else {//좌측
		CollisionRC.left -= 10;
		CollisionRC.right -= 10;
	}
	CollisionRC.top += 10;
	CollisionRC.bottom -= 10;
	CollisionRC = rc;
	RECT TileRect;
	RECT temp = { 0,0,0,0 };
	//for (int i = 0; i < 2; ++i)
	for (int i = 0; i < 2; ++i) {
		TileRect = stage->getTile()[tileIndex[i]].rc;
		checkPos[i] = TileRect;
		TileRect.left -= stage->getEdge0()+rc.left;
		TileRect.right -= stage->getEdge0() + rc.right;
		//해당 속성의 값이 언무브가 아니고

		if (stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE )
			//해당 타일과 충돌할때
			if(IntersectRect(&temp, &TileRect, &CollisionRC)) {
			if (isRight) {//우측
				state = EL_PATROL;
			}
			else {//좌측
				state = ER_PATROL;
			}
			return;
		}
		
	}
}