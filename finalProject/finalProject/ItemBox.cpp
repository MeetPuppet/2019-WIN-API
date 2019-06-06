#include "stdafx.h"
#include "ItemBox.h"

#define FRAME_SPEED 0.2

ItemBox::ItemBox()
{
	itemNum = 0;
	frameXAC = 0.2f;
	haveIn = false;
}


ItemBox::~ItemBox()
{
}

HRESULT ItemBox::init(int x, int y, int sizeX, int sizeY, int itemNuber)
{
	objectNode::init("ItemBox", x, y, sizeX, sizeY);
	frameXAC = 0;

	itemNum = itemNuber;
	haveIn = true;

	return S_OK;
}
void ItemBox::update()
{
	objectNode::update();
	if (haveIn) {
		frameMove();
	}
	else {
		frameX = 4;
	}
}
void ItemBox::render()
{
	objectNode::render();
}
void ItemBox::frameMove()
{
	if (TIMEMANAGER->getElapsedTime() > 0 && TIMEMANAGER->getElapsedTime() < 1) {
		frameXAC -= TIMEMANAGER->getElapsedTime();
	}
	else {
		frameXAC -= 0.01;
	}

	if (frameXAC < 0) {
		if (img->getMaxFrameX() - 1 > frameX) {
			frameXAC = 0.3;
			frameX += 1;
		}
		else {
			frameX = 0;
		}
	}
}

void ItemBox::active()
{
	switch (itemNum)
	{
	case 2://강화아이템
		//버섯뽑기
		break;
	case 4://코인
		//이펙트돌리고 점수주기
		break;
	}

	//프레임 바꾸기
	haveIn = false;
}