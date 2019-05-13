#include "stdafx.h"
#include "mainGame.h"
#include "tank.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);
	
	Tank = new tank;//��ü �Ҵ�
	Tank->init();//��ü �ʱ�ȭ
	Tank->setTankPosition();//init���� ���ڸ� �޾Ƽ� ������ ��

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	delete Tank;//�Ҵ� ����
	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	Tank->update();//��ü ������Ʈ
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	Tank->render();//��ü ���
	
	//==================== �ǵ������� =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
