#include "stdafx.h"
#include "firanhaFlower.h"


int changenum;
int stopnum;
firanhaFlower::firanhaFlower()
{
}


firanhaFlower::~firanhaFlower()
{
}

HRESULT firanhaFlower::init(int x, int y)
{
	Point p;
	p.x = x;
	p.y = y;
	enemyNode::init("firanhaFlower", p);

	move = 1;
	state = EL_PATROL;
	frameX = 0;
	changenum = 0;
	stopnum = 0;
	stop = FALSE;
	return S_OK;
}
void firanhaFlower::release()
{
}
void firanhaFlower::update()
{
	if (stop == FALSE) {
		if (move == 1) {
			p.y -= 3;
			changenum++;
		}
		else if (move == 0) {
			p.y += 3;
			changenum++;
		}
		else if (move == 2) {
			changenum++;
			stopnum++;
		}

		if (changenum % 5 == 0) {
			if (frameX == 0) {
				frameX = 1;
			}
			else
				frameX = 0;
		}
		if (p.y < 300) {
			move = 2;
		}
		if (p.y > 600) {
			move = 1;
		}
		if (stopnum == 30 && move == 2) {
			move = 0;
			stopnum = 0;
		}
	}

	// if mariox > p.x && mariox < p.x + 160 
		// state = CHASE
	rc = RectMakeCenter(p.x, p.y, img->getFrameWidth(), img->getFrameHeight());
}
void firanhaFlower::render()
{
	enemyNode::render();
}

void firanhaFlower::FrameSeter()
{
	switch (state)
	{
	case EL_PATROL:
	case ER_PATROL:
		if (img->getMaxFrameX() > FrameCheck) {
			FrameCheck += 1 * TIMEMANAGER->getElapsedTime();
			if (FrameCheck >= 2) {
				frameX = 1;
			}
			else
				frameX = FrameCheck;
		}
		else {
			FrameCheck = 0;
			frameX = FrameCheck;
		}
		break;
	case EL_CHASE:
	case ER_CHASE:		// �÷��̾ �����ϸ� CHASE�� ��ȯ�ǰ� �������� ����
						// if (pipe.y < p.y )
		stop = TRUE;	// �� ������ �ٱ����� ���� ���Դٸ� ������ �ʾƾ� ��
		break;
	case DEAD:
		frameX = 2;
		break;
	}
}

void firanhaFlower::AI(POINT* playerPoint)
{
	enemyNode::AI(playerPoint);
}