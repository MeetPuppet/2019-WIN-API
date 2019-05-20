#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);
	
	p = new playerNode;//��ü �Ҵ�
	p->init("mario","image/player/fireSuit.bmp");//��ü �ʱ�ȭ

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	delete p;//�Ҵ� ����
	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	p->update();//��ü ������Ʈ
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	p->render();//��ü ���
	
	//==================== �ǵ������� =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
