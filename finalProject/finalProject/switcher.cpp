#include "stdafx.h"
#include "switcher.h"


switcher::switcher()
{
}


switcher::~switcher()
{
}

HRESULT switcher::init()			//초기화 함수
{
	gameNode::init(true);
	mg = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 300, 100);
	mt = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, 300, 100);

	return S_OK;
}

void switcher::release()			//메모리 해제 함수
{
	gameNode::release();
	

}

void switcher::update()				//연산 함수
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (PtInRect(&mg, _ptMouse)) {
			switchCheck = MAINGAME;
		}
		if (PtInRect(&mt, _ptMouse)) {
			switchCheck = MAPTOOL;
		}
	}

}

void switcher::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	Rectangle(getMemDC(), mg.left, mg.top, mg.right, mg.bottom);
	char str1[256];
	sprintf(str1, "MAIN GAME");
	TextOut(getMemDC(), (mg.right - mg.left)/2 + mg.left - 40,
		(mg.bottom - mg.top) / 2 + mg.top, str1, strlen(str1));


	Rectangle(getMemDC(), mt.left, mt.top, mt.right, mt.bottom);
	char str2[256];
	sprintf(str2, "MAP TOOL");
	TextOut(getMemDC(), (mt.right - mt.left) / 2 + mt.left-36,
		(mt.bottom - mt.top) / 2 + mt.top, str2, strlen(str2));

	//==================== 건들지마라 =======================

	this->getBackBuffer()->render(getHDC(), 0, 0);

}
