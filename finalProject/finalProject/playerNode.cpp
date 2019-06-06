#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "playerNode.h"
//순서가 매우 중요함
//그리고 속성에서 버전맞추어줄때
//문자집합도 멀티바이트로 맞추어 줘야 고칠게 없음
//Commit is Real

#define WIDTH 560  //이미지 가로길이
#define HEIGHT 320 //이미지 세로길이

#define SPEED 300
#define JUMPSPEED 6
#define FRAMETIME 0.2

playerNode::playerNode()
//<<<<<<< HEAD
{//무슨일이 벌어질지 모르니 설정해둠

//=======
{
	img = NULL;

	rc = {0,0,0,0};
	point = Point(0.f, 0.f);

	speed = 0.f;
	jumpPower = 0.f;

	state = PR_IDLE;
	mode = SMALL;

	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;
//>>>>>>> cc9efb39d31e70d729c227ddf82759a1983d0b97
}


playerNode::~playerNode()
{
}

HRESULT playerNode::init(image* IMG)
{			
	img = IMG;
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());

	return S_OK;
}

void playerNode::update() 
{
//<<<<<<< HEAD
//=======
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
//>>>>>>> cc9efb39d31e70d729c227ddf82759a1983d0b97

}

void playerNode::render() 
{
	
}
void playerNode::stateUpdate() 
{
	switch (state)
	{
	case PR_IDLE:
		break;
	case PL_IDLE:
		break;
	case PR_MOVE:
		break;
	case PL_MOVE:
		break;
	case PR_JUMP:
		break;
	case PL_JUMP:
		break;
	case PR_SIT:
		break;
	case PL_SIT:
		break;
	}
}

void playerNode::keySet()
{
	//이건 플레이어 별로 만들 것
	switch (state)
	{
	case PR_IDLE:
		break;
	case PL_IDLE:
		break;
	case PR_MOVE:
		break;
	case PL_MOVE:
		break;
	case PR_JUMP:
		break;
	case PL_JUMP:
		break;
	case PR_SIT:
		break;
	case PL_SIT:
		break;
	}
}

void playerNode::stateFrameUpdate()
{
	//X 파트
	switch (state)
	{
	case PR_IDLE:
	case PL_IDLE:
		frameX = 0;
		break;
	case PR_MOVE:
	case PL_MOVE:
		if (img->getMaxFrameX() > frameCount) {
			frameCount += TIMEMANAGER->getElapsedTime();
			if (frameCount >= 4) {
				frameX = int(1 + frameCount);
			}
			else
				frameX = int(frameCount);
		}
		else {
			frameCount = 1;
			frameX = int(frameCount);
		}
		break;
	case PR_JUMP:
	case PL_JUMP:
		break;
	case PR_SIT:
	case PL_SIT:
		break;
	}

	//Y 파트
	switch (state)
	{
	case PR_IDLE:
	case PR_MOVE:
	case PR_JUMP:
	case PR_SIT:
		frameY = 0;
		break;
	case PL_IDLE:
	case PL_MOVE:
	case PL_JUMP:
	case PL_SIT:
		frameY = 1;
		break;
	}
}