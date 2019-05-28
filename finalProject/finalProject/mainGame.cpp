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
	q = new playerNode;//��ü �Ҵ�
	p->init("mario","image/player/mario.bmp",1);//��ü �ʱ�ȭ
	q->init("ruigi", "image/player/Luigi.bmp",2);//��ü �ʱ�ȭ
	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	delete p;//�Ҵ� ����
	delete q;
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	p->update();//��ü ������Ʈ
	q->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	p->render();//��ü ���
	q->render();
	
	//==================== �ǵ������� =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
