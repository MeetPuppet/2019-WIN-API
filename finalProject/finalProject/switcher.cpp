#include "stdafx.h"
#include "switcher.h"


switcher::switcher()
{
}


switcher::~switcher()
{
}

HRESULT switcher::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);
	mg = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 300, 100);
	mt = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, 300, 100);

	return S_OK;
}

void switcher::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	

}

void switcher::update()				//���� �Լ�
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

void switcher::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

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

	//==================== �ǵ������� =======================

	this->getBackBuffer()->render(getHDC(), 0, 0);

}
