#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "playerNode.h"

#include "objectManger.h"
#include "Stage1.h"
//순서가 매우 중요함
//그리고 속성에서 버전맞추어줄때
//문자집합도 멀티바이트로 맞추어 줘야 고칠게 없음
//Commit is Real

#define WIDTH 560  //이미지 가로길이
#define HEIGHT 320 //이미지 세로길이


playerNode::playerNode()//무슨일이 벌어질지 모르니 설정해둠
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);

	speed = 0.f;
	jumpPower = 0.2f;
	IFS = 0;
	IFF = 0;

	state = PS_IDLE;
	mode = PM_SMALL;

	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

	for (int i = 0; i < 2; ++i) {
		checkPos[i] = {0,0,0,0};
	}
	om = NULL;
	stage = NULL;
}


playerNode::~playerNode()
{

}

HRESULT playerNode::init(image* IMG, Point p)
{			
	img = IMG;
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
	foot = RectMakeCenter(point.x, rc.bottom, img->getFrameWidth()+10, 20);

	point = p;

	state = PS_JUMP;
	mode = PM_SMALL;

	speed = 0.f;
	jumpPower = 0.0f;
	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
	foot = RectMakeCenter(point.x, rc.bottom, img->getFrameWidth() + 10, 20);
	time = TIMEMANAGER->getElapsedTime();
	if (time < 0 || time > 10) time = 0.16f;
	keySet();
	footCheck();
	om->collisionCoin(rc);
}

void playerNode::render() 
{
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);

}

void playerNode::keySet()
{
	//이건 플레이어 별로 만들 것
	switch (state)
	{
	case PS_IDLE:
		break;
	case PS_MOVE:
		break;
	case PS_BREAK:
		break;
	case PS_JUMP:
		break;
	case PS_SIT:
		break;
	}
}

//void playerNode::stateFrameUpdate()
//{
//	//X 파트
//	switch (state)
//	{
//	case PR_IDLE:
//	case PL_IDLE:
//		frameX = 0;
//		break;
//	case PR_MOVE:
//	case PL_MOVE:
//		if (img->getMaxFrameX() > frameCount) {
//			frameCount += TIMEMANAGER->getElapsedTime();
//			if (frameCount >= 4) {
//				frameX = int(1 + frameCount);
//			}
//			else
//				frameX = int(frameCount);
//		}
//		else {
//			frameCount = 1;
//			frameX = int(frameCount);
//		}
//		break;
//	case PR_JUMP:
//	case PL_JUMP:
//		break;
//	case PR_SIT:
//	case PL_SIT:
//		break;
//	}
//	//Y 파트
//	switch (state)
//	{
//	case PR_IDLE:
//	case PR_MOVE:
//	case PR_JUMP:
//	case PR_SIT:
//		frameY = 0;
//		break;
//	case PL_IDLE:
//	case PL_MOVE:
//	case PL_JUMP:
//	case PL_SIT:
//		frameY = 1;
//		break;
//	}
//}

//상하이동
void playerNode::gravityChecker(bool isFall)
{
	//터짐 방지용
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return;
	//타일 검출용
	RECT CollisionRC;

	//타일 위치 측정용
	//나중에 알아보자
	int tileX, tileY;

	//일단 플레이어 자체를 넘겨주자
	CollisionRC = rc;
	time;//이 실시간을 받아오는 값은 이미 준비 해뒀다.
	IFS;//이놈은 실 스피드다.

	//전에 쓰던건 여기서 이미지 처리함

	//맵환경 변화 반영
	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	//좀 깍아주면 편하다니 그렇다하자
	CollisionRC.left += 5;
	CollisionRC.top += 5;
	CollisionRC.right -= 5;
	CollisionRC.bottom -= 5;

	//예로 10*16에 위치한다면
	//시작점은 720 ,1200,800,1280으로 left top이다
	tileX = CollisionRC.left / TILESIZE;
	//고로 X는 9
	tileY = CollisionRC.top / TILESIZE;
	//Y는 15가 된다.c


	//탱크때는 방향을 받았지만 얘들은 중력체크니 위아래만 체크한다.
	if (isFall) {//하단
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		//			   (  9   +   15  *  150 ) + 150
		//				      9 + 2250 + 1 = 2341
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		//			   (  9   + 1 +  15   *   150 ) + 150'
		//				        2260 + 150 = 2410

		if (mode == PM_BIG) {
			tileIndex[0] += TILEX;
			tileIndex[1] += TILEX;
		}
	}
	else {//상단
		//tileIndex[0] = (tileX + tileY * TILEX) - TILEX;
		//tileIndex[1] = (tileX + 1 + tileY * TILEX) - TILEX;
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
	}
	//이 두개의 인덱스를 가지고 수작을 부린다.

	RECT TileRect;
	for (int i = 0; i < 2; ++i) {
		checkPos[i] = stage->getTile()[tileIndex[i]].rc;
	}
	RECT temp = { 0,0,0,0 };
	for (int i = 0; i < 2; ++i) {
		TileRect = stage->getTile()[tileIndex[i]].rc;
		TileRect.left -= stage->getEdge0();
		TileRect.right -= stage->getEdge0();
		//해당 속성의 값이 언무브가 맞고
		if (((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			//해당 타일과 충돌할때
			IntersectRect(&temp, &TileRect, &CollisionRC)) {

			if (isFall) {//하단
				frameX = 1;
				state = PS_MOVE;
				rc.bottom = stage->getTile()[tileIndex[i]].rc.top;
				rc.top = rc.bottom - (TILESIZE - 10);

				point.y = rc.bottom - img->getFrameHeight() / 2;
			}
			else {//상단
				jumpPower = -jumpPower;
				rc.top = stage->getTile()[tileIndex[i]].rc.bottom;
				rc.bottom = rc.top - (TILESIZE - 10);

				point.y = rc.top + img->getFrameHeight() / 2;
			}
			return;
		}
	}

	//어떻게하면 공중부약을 없앨 수 있을까
	////해당 속성의 값이 언무브가 맞고
	//if (((stage->getTileAttribute()[tileIndex[0]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
	//	//해당 타일과 충돌할때
	//	!IntersectRect(&temp, &TileRect, &CollisionRC)) {
	//
	//	if (isFall) {//하단
	//		frameX = 5;
	//		state = PS_JUMP;
	//	}
	//	return;
	//}

}

//좌우이동
bool playerNode::moveChecker(bool isRight)
{
	//터짐 방지용
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return true;
	//타일 검출용
	CollisionRC;
	int tileX, tileY;

	CollisionRC = rc;

	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	//그저 위치 찾아내는 부분이라 큰 의미는 없음
	//근데 아래서 다시 탐색 해볼라면 재설정 필요함
	//나도 모르겠다
	if (isRight) {//우측
		CollisionRC.left += 10;
		CollisionRC.right += 10;
	}
	else {//좌측
		CollisionRC.left -= 10;
		CollisionRC.right -= 10;
	}
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
		if (mode == PM_BIG && state != PS_SIT) {
			tileIndex[1] = (tileX + tileY * TILEX) + 1;
			tileIndex[0] = (tileX + (tileY + 1) * TILEX) + 1;
		}
	}
	else {//좌측
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		if (mode == PM_BIG && state != PS_SIT) {
			tileIndex[1] = tileX + (tileY * TILEX);
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
		}
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
	RECT TileRect;
	RECT temp = { 0,0,0,0 };
	//for (int i = 0; i < 2; ++i)
	for (int i = 0; i < 2; ++i) {
		TileRect = stage->getTile()[tileIndex[i]].rc;
		//TileRect.left -= stage->getEdge0();
		//TileRect.right -= stage->getEdge0();
		//해당 속성의 값이 언무브가 아니고
		checkPos[i] = stage->getTile()[tileIndex[i]].rc;

		if ((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) &&
			//해당 타일과 충돌할때
			IntersectRect(&temp, &TileRect, &CollisionRC)) {
			return false;
		}
		if (i == 1) {
			return true;
		}
		if (mode == PM_BIG && state != PS_SIT) {
		}
		else {
			if ((stage->getTileAttribute()[tileIndex[i]] ^ ATTR_UNMOVE) &&
				//해당 타일과 충돌할때
				IntersectRect(&temp, &TileRect, &CollisionRC)) {
				return true;
			}
			if (i == 1) {
				return false;
			}
		}
	}
}
void playerNode::footCheck()
{//터짐 방지용
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return;
	//타일 검출용
	RECT CollisionRC;

	//타일 위치 측정용
	//나중에 알아보자
	int tileX, tileY;

	//일단 플레이어 자체를 넘겨주자
	CollisionRC = rc;
	time;//이 실시간을 받아오는 값은 이미 준비 해뒀다.
	IFS;//이놈은 실 스피드다.

	//전에 쓰던건 여기서 이미지 처리함

	//맵환경 변화 반영
	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	//좀 깍아주면 편하다니 그렇다하자
	CollisionRC.left += 25;
	CollisionRC.top += 5;
	CollisionRC.right -= 25;
	CollisionRC.bottom -= 5;

	//예로 10*16에 위치한다면
	//시작점은 720 ,1200,800,1280으로 left top이다
	tileX = CollisionRC.left / TILESIZE;
	//고로 X는 9
	tileY = CollisionRC.top / TILESIZE;
	//Y는 15가 된다.c


	
	tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
	tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
	if (mode == PM_BIG) {
		tileIndex[0] += TILEX;
		tileIndex[1] += TILEX;
	}

	RECT TileRect;
	RECT temp = { 0,0,0,0 };
	for (int i = 0; i < 2; ++i) {
		TileRect = stage->getTile()[tileIndex[i]].rc;
		//해당 속성의 값이 언무브가 맞고
		if (((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			//해당 타일과 충돌할때
			IntersectRect(&temp, &TileRect, &foot)) {
			//그럼 아무것도 안함
			if (state == PS_JUMP && jumpPower < 0) {
				point.y = rc.bottom - img->getFrameHeight() / 2;
				state = PS_MOVE;
				frameX = 1;
			}
			return;
		}
	}
	if (state != PS_JUMP) {
		jumpPower = 0;
		state = PS_JUMP;
		frameX = 5;
	}
}

void playerNode::powerUp()
{
	if (mode == PM_SMALL) {
		mode = PM_BIG;
	}
}
void playerNode::jumpUp()
{
	state = PS_JUMP;
	jumpPower = 8;
}
void playerNode::powerDown()
{
	if (mode == PM_BIG) {
		mode = PM_SMALL;
		return;
	}

	frameX = 6;
	state = PS_DEAD;
}
void playerNode::dead()
{
	mode = PM_SMALL;
	frameX = 6;
	state = PS_DEAD;
}