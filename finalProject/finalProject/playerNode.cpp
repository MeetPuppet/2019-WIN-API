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
{//�������� �������� �𸣴� �����ص�
	image = NULL;
	x = y = 0;
	rc = { 0,0,0,0 };
	speed = 0;
	JumpPower = 0;
	state = IDLE;
	time = 0;

	jumpStartY = 0;
}


playerNode::~playerNode()
{
}

HRESULT playerNode::init()
{			


	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());

}

void playerNode::render() 
{
	
}
void playerNode::stateUpdate() {
	
}

void playerNode::keySet()
{
	
}

void playerNode::stateFrameUpdate()
{
	
}