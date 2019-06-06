#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"
//������ �ſ� �߿���
//�׸��� �Ӽ����� �������߾��ٶ�
//�������յ� ��Ƽ����Ʈ�� ���߾� ��� ��ĥ�� ����
//Commit is Real

#define WIDTH 560  //�̹��� ���α���
#define HEIGHT 320 //�̹��� ���α���

#define SPEED 300
#define JUMPSPEED 6
#define FRAMETIME 0.2

playerNode::playerNode()
//<<<<<<< HEAD
{//�������� �������� �𸣴� �����ص�

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
	//�̰� �÷��̾� ���� ���� ��
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
	//X ��Ʈ
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

	//Y ��Ʈ
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