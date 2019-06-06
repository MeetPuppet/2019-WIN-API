#include "stdafx.h"
#include "mainGame.h"

#include "enemyManger.h"
#include "objectManger.h"
#include "Stage1.h"
#include "boss.h"

mainGame::mainGame()
{
	E_Manager = NULL;
	O_Manger = NULL;
	stage1 = NULL;
	bowser = NULL;
}

mainGame::~mainGame()
{

}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);
	
	//p = new playerNode;//��ü �Ҵ�
	//q = new playerNode;//��ü �Ҵ�
	//p->init("mario","image/player/mario.bmp",1);//��ü �ʱ�ȭ
	//q->init("ruigi", "image/player/Luigi.bmp",2);//��ü �ʱ�ȭ

	if (E_Manager == NULL) {
		E_Manager = new enemyManger;
		E_Manager->init();
	}
	if (O_Manger == NULL) {
		O_Manger = new objectManger;
		O_Manger->init();
	}
	if (stage1 == NULL) {
		stage1 = new Stage1;

		//������ ����
		if (O_Manger)//init���� ���� ������
			stage1->LinkToOBJ(O_Manger);

		stage1->init();
	}

	bowser = new boss;

	bowser->init(600, 300);
	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	//delete p;//�Ҵ� ����
	//delete q;

	if (E_Manager) {
		delete E_Manager;
	}
	if (O_Manger) {
		delete O_Manger;
	}
	if (stage1) {
		delete stage1;
	}
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	//RECT�� �־��ָ� �浹�ߴ��� ���ߴ��� bool������ ��ȯ ���ִ� �Լ�
	//if (E_Manager->enemyCollisionCheck(RECT)) {}


	//������ ���콺Ű �����ڸ��� �� ����
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		E_Manager->makeGoomba(_ptMouse);
	}


	if (E_Manager) {
		E_Manager->update();
	}
	if (O_Manger) {
		O_Manger->update();
	}
	if (stage1) {
		stage1->update();
		//stage1->setMainPosition({ p->getX(), 0 });
	}

	//int moveSpeed = p->getSpeed();
	//if (p->getX() > 800 && stage1->getEdge1()>1200+p->getSpeed()) {
	//	p->moveX(-moveSpeed);
	//	q->moveX(-moveSpeed);
	//	E_Manager->moveWorld(-moveSpeed);
	//	O_Manger->moveWorld(-moveSpeed);
	//	stage1->moveX(-moveSpeed);
	//	bowser->moveX(-moveSpeed);
	//}
	//else if (p->getX() < 400 && stage1->getEdge0() < 0 - p->getSpeed()) {
	//	//�¿�ӵ����� ����
	//	moveSpeed += 1;
	//	p->moveX(moveSpeed);
	//	q->moveX(moveSpeed);
	//	E_Manager->moveWorld(moveSpeed);
	//	O_Manger->moveWorld(moveSpeed);
	//	stage1->moveX(moveSpeed);
	//	bowser->moveX(moveSpeed);
	//}
	//
	//if (q->getX() > 800 && stage1->getEdge1() > 1200 + q->getSpeed()) {
	//	p->moveX(-moveSpeed);
	//	q->moveX(-moveSpeed);
	//	E_Manager->moveWorld(-moveSpeed);
	//	O_Manger->moveWorld(-moveSpeed);
	//	stage1->moveX(-moveSpeed);
	//	bowser->moveX(-moveSpeed);
	//}
	//else if (q->getX() < 400 && stage1->getEdge0() < 0 - q->getSpeed()) {
	//	
	//	p->moveX(moveSpeed);
	//	q->moveX(moveSpeed);
	//	E_Manager->moveWorld(moveSpeed);
	//	O_Manger->moveWorld(moveSpeed);
	//	stage1->moveX(moveSpeed);
	//	bowser->moveX(moveSpeed);
	//}

	bowser->update();
}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	if (stage1) {
		stage1->render();
	}
	if (O_Manger) {
		O_Manger->render();
	}
	if (E_Manager) {
		E_Manager->render();
	}

	

	bowser->render();
	//==================== �ǵ������� =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
