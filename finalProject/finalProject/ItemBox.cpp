#include "stdafx.h"
#include "ItemBox.h"

#define FRAME_SPEED 1

ItemBox::ItemBox()
{
	itemNum = 0;
	frameXAC = 0;
	haveIn = false;
}


ItemBox::~ItemBox()
{
}

HRESULT ItemBox::init(int x, int y, int sizeX, int sizeY, int itemNuber)
{
	objectNode::init("ItemBox", x, y, sizeX, sizeY);

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
	if (img->getMaxFrameX() - 1 > frameXAC) {
		frameXAC += FRAME_SPEED * TIMEMANAGER->getElapsedTime();
		if(frameXAC < 0) frameXAC = 0;
		if (frameXAC >= 4) {
			frameX = 0;
		}
		else {
			frameX = frameXAC;
		}
	}
	else {
		frameX = 0;
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