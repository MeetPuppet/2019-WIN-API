#include "stdafx.h"
#include "mainGame.h"

#include "title.h"
#include "world1.h"
#include "world2.h"

mainGame::mainGame()
{
	mario = NULL;
	luigi = NULL;
	E_Manager = NULL;
	O_Manager = NULL;
	stage1 = NULL;
}

mainGame::~mainGame()
{

}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);

	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("P1world1", new world1);
	SCENEMANAGER->addScene("P2world1", new world1(2));
	SCENEMANAGER->addScene("P1world2", new world2);
	SCENEMANAGER->addScene("P2world2", new world2(2));
	SCENEMANAGER->changeScene("title");

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	//delete p;//�Ҵ� ����
	//delete q;
	SCENEMANAGER->release();
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	SCENEMANAGER->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	SCENEMANAGER->render();

	//==================== �ǵ������� =======================

	if (KEYMANAGER->isToggleKey(VK_F3)) 
		TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
