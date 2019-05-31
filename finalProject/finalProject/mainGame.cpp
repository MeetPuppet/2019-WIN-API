#include "stdafx.h"
#include "mainGame.h"

#include "enemyManger.h"

//�ӽ�
#include "Stage1.h"

mainGame::mainGame()
{
	E_Manager = NULL;
	stage1 = NULL;
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

	if (E_Manager == NULL) {
		E_Manager = new enemyManger;
		E_Manager->init();
	}
	if (stage1 == NULL) {
		stage1 = new Stage1;
		stage1->init();
	}
	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	delete p;//�Ҵ� ����
	delete q;

	if (E_Manager) {
		delete E_Manager;
	}
	if (stage1) {
		delete stage1;
	}
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	p->update();//��ü ������Ʈ
	q->update();

	E_Manager->update();
	//������ ���콺Ű �����ڸ��� �� ����
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		E_Manager->makeGoomba(_ptMouse);
	}

	stage1->update();
	stage1->setMainPosition({p->getX(), 0});
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	stage1->render();
	E_Manager->render();
	p->render();//��ü ���
	q->render();
	
	//==================== �ǵ������� =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
