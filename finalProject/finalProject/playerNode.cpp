#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"

#include "objectManger.h"
#include "Stage1.h"
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
	IFS = 0;
	IFF = 0;

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
	om->collisionCoin(rc);
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

//void playerNode::stateFrameUpdate()
//{
//	//X ��Ʈ
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
//	//Y ��Ʈ
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

//�����̵�
void playerNode::gravityChecker(bool isFall)
{
	//Ÿ�� �����
	RECT CollisionRC;

	//Ÿ�� ��ġ ������
	int tileIndex[2] = { 0 };
	//���߿� �˾ƺ���
	int tileX, tileY;

	//�ϴ� �÷��̾� ��ü�� �Ѱ�����
	CollisionRC = rc;

	time;//�� �ǽð��� �޾ƿ��� ���� �̹� �غ� �ص״�.
	IFS;//�̳��� �� ���ǵ��.

	//���� ������ ���⼭ �̹��� ó����

	//�� ����ָ� ���ϴٴ� �׷�������
	CollisionRC.left += 5;
	CollisionRC.top += 5;
	CollisionRC.right -= 5;
	CollisionRC.bottom -= 5;

	//���� 10*16�� ��ġ�Ѵٸ�
	//�������� 720 ,1200,800,1280���� left top�̴�
	tileX = CollisionRC.left / TILESIZE;
	//��� X�� 9
	tileY = CollisionRC.top / TILESIZE;
	//Y�� 15�� �ȴ�.c


	//��ũ���� ������ �޾����� ����� �߷�üũ�� ���Ʒ��� üũ�Ѵ�.
	if (isFall) {//�ϴ�
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		//			   (  9   +   15  *  150 ) + 1'
		//				      9 + 2250 + 1 = 2341
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		//			   (  9   + 1 +  15   *   150 ) + 150'
		//				        2260 + 150 = 2410
	}
	else {//���
		tileIndex[0] = tileX + tileY * TILEY;
		//			   (  9   +   15  *  150 ) + 1'
		//				      9 + 2250 + 1 = 2341
		tileIndex[1] = (tileX + 1) + tileY * TILEY;
		//			   (  9   + 1 ) +  15   *   150 
		//				         10 + 2250 = 2260
	}

	//�� �ΰ��� �ε����� ������ ������ �θ���.
	RECT TileRect;

	RECT temp;
	for (int i = 0; i < 2; ++i) {
		//�ش� �Ӽ��� ���� �𹫺갡 �°�
		TileRect = stage->getTile()[tileIndex[i]].rc;
		if (((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE)&&
			//�ش� Ÿ�ϰ� �浹�Ҷ�
			IntersectRect(&temp, &TileRect, &CollisionRC)) {
			
			if (isFall) {//�ϴ�
				rc.bottom = stage->getTile()[tileIndex[i]].rc.top;
				rc.top = rc.bottom - (TILESIZE - 10);

				point.y = rc.bottom - img->getFrameHeight()/2;
				if (state == PS_JUMP) {
					frameX = 0;
					state == PS_IDLE;
				}
			}
			else {//���
				rc.top = stage->getTile()[tileIndex[i]].rc.bottom;
				rc.bottom = rc.top - (TILESIZE - 10);

				point.y = rc.top + img->getFrameHeight() / 2;
				if (jumpPower > 0) {
					jumpPower = 0;
				}
			}
			return;
		}
	}
}

//�¿��̵�
void playerNode::moveChecker(bool isRight)
{

}