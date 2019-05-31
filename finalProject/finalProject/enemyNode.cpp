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


	//�浹�� ��ġ ���������� �ֽ�ȭ
	rc = RectMakeCenter(p.x, p.y, img->getFrameWidth(), img->getFrameHeight());
}
void enemyNode::render() 
{
	//�浹 Ȯ�ο�
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	img->frameRender(getMemDC(), rc.left, rc.top, frameX, frameY);

	//��������Ʈ �ִϸ��̼� üũ��
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
//���ϴܺ� AI �Ǵܿ� �Լ�
inline bool enemyNode::playerSearch(POINT* playerPoint)
{
	if (playerPoint == NULL) return false;
	//�÷��̾�� �Ÿ��Ǵ�
	float distance = getDistance(playerPoint->x, playerPoint->y, p.x, p.y);

	//�÷��̾���� �Ÿ��� 200 �����ֶ� ��
	if (distance < 200) {
		return true;
	}
	return false;
}