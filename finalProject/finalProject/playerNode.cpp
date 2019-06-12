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
	//���� ������
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return;
	//Ÿ�� �����
	RECT CollisionRC;

	//Ÿ�� ��ġ ������
	//���߿� �˾ƺ���
	int tileX, tileY;

	//�ϴ� �÷��̾� ��ü�� �Ѱ�����
	CollisionRC = rc;
	time;//�� �ǽð��� �޾ƿ��� ���� �̹� �غ� �ص״�.
	IFS;//�̳��� �� ���ǵ��.

	//���� ������ ���⼭ �̹��� ó����

	//��ȯ�� ��ȭ �ݿ�
	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

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
	else {//���
		//tileIndex[0] = (tileX + tileY * TILEX) - TILEX;
		//tileIndex[1] = (tileX + 1 + tileY * TILEX) - TILEX;
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
	}
	//�� �ΰ��� �ε����� ������ ������ �θ���.

	RECT TileRect;
	for (int i = 0; i < 2; ++i) {
		checkPos[i] = stage->getTile()[tileIndex[i]].rc;
	}
	RECT temp = { 0,0,0,0 };
	for (int i = 0; i < 2; ++i) {
		TileRect = stage->getTile()[tileIndex[i]].rc;
		TileRect.left -= stage->getEdge0();
		TileRect.right -= stage->getEdge0();
		//�ش� �Ӽ��� ���� �𹫺갡 �°�
		if (((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			//�ش� Ÿ�ϰ� �浹�Ҷ�
			IntersectRect(&temp, &TileRect, &CollisionRC)) {

			if (isFall) {//�ϴ�
				frameX = 1;
				state = PS_MOVE;
				rc.bottom = stage->getTile()[tileIndex[i]].rc.top;
				rc.top = rc.bottom - (TILESIZE - 10);

				point.y = rc.bottom - img->getFrameHeight() / 2;
			}
			else {//���
				jumpPower = -jumpPower;
				rc.top = stage->getTile()[tileIndex[i]].rc.bottom;
				rc.bottom = rc.top - (TILESIZE - 10);

				point.y = rc.top + img->getFrameHeight() / 2;
			}
			return;
		}
	}

	//����ϸ� ���ߺξ��� ���� �� ������
	////�ش� �Ӽ��� ���� �𹫺갡 �°�
	//if (((stage->getTileAttribute()[tileIndex[0]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
	//	//�ش� Ÿ�ϰ� �浹�Ҷ�
	//	!IntersectRect(&temp, &TileRect, &CollisionRC)) {
	//
	//	if (isFall) {//�ϴ�
	//		frameX = 5;
	//		state = PS_JUMP;
	//	}
	//	return;
	//}

}

//�¿��̵�
bool playerNode::moveChecker(bool isRight)
{
	//���� ������
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return true;
	//Ÿ�� �����
	CollisionRC;
	int tileX, tileY;

	CollisionRC = rc;

	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	//���� ��ġ ã�Ƴ��� �κ��̶� ū �ǹ̴� ����
	//�ٵ� �Ʒ��� �ٽ� Ž�� �غ���� �缳�� �ʿ���
	//���� �𸣰ڴ�
	if (isRight) {//����
		CollisionRC.left += 10;
		CollisionRC.right += 10;
	}
	else {//����
		CollisionRC.left -= 10;
		CollisionRC.right -= 10;
	}
	CollisionRC.top += 5;
	CollisionRC.bottom -= 5;

	//���� 10*16�� ��ġ�Ѵٸ�
	//�������� 720 ,1200,800,1280���� left top�̴�
	tileX = CollisionRC.left / TILESIZE;
	//��� X�� 9
	tileY = CollisionRC.top / TILESIZE;
	//Y�� 15�� �ȴ�.c


	if (isRight) {//����
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		if (mode == PM_BIG && state != PS_SIT) {
			tileIndex[1] = (tileX + tileY * TILEX) + 1;
			tileIndex[0] = (tileX + (tileY + 1) * TILEX) + 1;
		}
	}
	else {//����
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		if (mode == PM_BIG && state != PS_SIT) {
			tileIndex[1] = tileX + (tileY * TILEX);
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
		}
	}
	//�� �ΰ��� �ε����� ������ ������ �θ���.

	CollisionRC = rc;
	if (isRight) {//����
		CollisionRC.left += 10;
		CollisionRC.right += 10;
	}
	else {//����
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
		//�ش� �Ӽ��� ���� �𹫺갡 �ƴϰ�
		checkPos[i] = stage->getTile()[tileIndex[i]].rc;

		if ((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) &&
			//�ش� Ÿ�ϰ� �浹�Ҷ�
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
				//�ش� Ÿ�ϰ� �浹�Ҷ�
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
{//���� ������
	if (point.x < 0 || point.x > 1200 ||
		point.y < 0 || point.y > 800) return;
	//Ÿ�� �����
	RECT CollisionRC;

	//Ÿ�� ��ġ ������
	//���߿� �˾ƺ���
	int tileX, tileY;

	//�ϴ� �÷��̾� ��ü�� �Ѱ�����
	CollisionRC = rc;
	time;//�� �ǽð��� �޾ƿ��� ���� �̹� �غ� �ص״�.
	IFS;//�̳��� �� ���ǵ��.

	//���� ������ ���⼭ �̹��� ó����

	//��ȯ�� ��ȭ �ݿ�
	CollisionRC.left -= stage->getEdge0();
	CollisionRC.right -= stage->getEdge0();

	//�� ����ָ� ���ϴٴ� �׷�������
	CollisionRC.left += 25;
	CollisionRC.top += 5;
	CollisionRC.right -= 25;
	CollisionRC.bottom -= 5;

	//���� 10*16�� ��ġ�Ѵٸ�
	//�������� 720 ,1200,800,1280���� left top�̴�
	tileX = CollisionRC.left / TILESIZE;
	//��� X�� 9
	tileY = CollisionRC.top / TILESIZE;
	//Y�� 15�� �ȴ�.c


	
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
		//�ش� �Ӽ��� ���� �𹫺갡 �°�
		if (((stage->getTileAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			//�ش� Ÿ�ϰ� �浹�Ҷ�
			IntersectRect(&temp, &TileRect, &foot)) {
			//�׷� �ƹ��͵� ����
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