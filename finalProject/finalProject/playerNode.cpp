#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"
#include "objectManger.h"
//������ �ſ� �߿���
//�׸��� �Ӽ����� �������߾��ٶ�
//�������յ� ��Ƽ����Ʈ�� ���߾� ��� ��ĥ�� ����
//Commit is Real

#define WIDTH 560  //�̹��� ���α���
#define HEIGHT 320 //�̹��� ���α���


playerNode::playerNode()//�������� �������� �𸣴� �����ص�
{
	img = NULL;

	rc = { 0,0,0,0 };
	point = Point(0.f, 0.f);

	speed = 0.f;
	jumpPower = 0.2f;

	state = PS_IDLE;
	mode = PM_SMALL;

	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

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

	state = PS_IDLE;
	mode = PM_BIG;

	speed = 0.f;
	jumpPower = 0.f;
	frameX = 0;
	frameY = 0;
	frameCount = 0.2f;

	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
	time = TIMEMANAGER->getElapsedTime();

	keySet();
}

void playerNode::render() 
{
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);
}

void playerNode::keySet()
{
	//�̰� �÷��̾� ���� ���� ��
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
