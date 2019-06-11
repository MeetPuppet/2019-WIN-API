#include "stdafx.h"
#include "mainGame.h"

#include "Mario.h"
#include "Luigi.h"
#include "enemyManger.h"
#include "objectManger.h"
#include "Stage1.h"

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
	
	if (mario == NULL) {
		mario = new Mario;
		mario->init(Point(WINSIZEX / 2, WINSIZEY / 2));
	}
	if(luigi == NULL) {
		luigi = new Luigi;
		luigi->init(Point(WINSIZEX / 2, WINSIZEY / 2));
	}

	if (E_Manager == NULL) {
		E_Manager = new enemyManger;
		E_Manager->init();
		if (mario) {
			E_Manager->LinkToP1(mario);
		}
		if (luigi) {
			E_Manager->LinkToP2(luigi);
		}
	}
	POINT p = { 600,600 };
	E_Manager->makeBowser(p);
	if (O_Manager == NULL) {
		O_Manager = new objectManger;
		O_Manager->init();
		if (mario) {
			O_Manager->LinkToP1(mario);
			mario->LinkToOM(O_Manager);
		}
		if (luigi) {
			O_Manager->LinkToP2(luigi);
			luigi->LinkToOM(O_Manager);
		}
	}
	if (E_Manager) {
		E_Manager->LinkToobjectManger(O_Manager);
	}
	if (O_Manager) {
		O_Manager->LinkToenemyManger(E_Manager);
	}
	if (stage1 == NULL) {
		stage1 = new Stage1;

		//������ ����
		if (O_Manager) {//init���� ���� ������
			stage1->LinkToOBJ(O_Manager);
			O_Manager->LinkToStage(stage1);
		}
		if (E_Manager){
			stage1->LinkToEnemy(E_Manager);
			E_Manager->LinkToStage(stage1);
		}

		stage1->init();

		if (mario) {
			mario->LinkToStage(stage1);
		}
		if (luigi) {
			luigi->LinkToStage(stage1);
		}
	}

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();
	//delete p;//�Ҵ� ����
	//delete q;

	if (mario) {
		delete mario;
		mario = NULL;
	}
	if (luigi) {
		delete luigi;
		luigi = NULL;
	}
	if (E_Manager) {
		delete E_Manager;
		E_Manager = NULL;
	}
	if (O_Manager) {
		delete O_Manager;
		O_Manager = NULL;
	} 
	if (stage1) {
		delete stage1;
		stage1 = NULL;
	}
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	//RECT�� �־��ָ� �浹�ߴ��� ���ߴ��� bool������ ��ȯ ���ִ� �Լ�
	//if (E_Manager->enemyCollisionCheck(RECT)) {}


	//������ ���콺Ű �����ڸ��� �� ����
	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
	//	E_Manager->makeGoomba(_ptMouse);
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
	//	E_Manager->makeGreenTurtle(_ptMouse);
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
	//	E_Manager->KillGreenTurtle();
	//}

	if (mario) {
		mario->update();
	}
	if (luigi) {
		luigi->update();
	}
	if (E_Manager) {
		E_Manager->update();
	}
	if (O_Manager) {
		O_Manager->update();
		O_Manager->changeToGreenShell();
	}
	if (stage1) {
		stage1->update();
		//stage1->setMainPosition({ p->getX(), 0 });
	}
	int moveSpeed = mario->getSpeed();
	if (mario->getX() > 800 && stage1->getEdge1() > 1200 + mario->getSpeed()
		&& (luigi && luigi->getRect().left > 0)) {
		mario->moveX(-mario->getSpeed());
		E_Manager->moveWorld(-moveSpeed);
		O_Manager->moveWorld(-moveSpeed);
		stage1->moveX(-moveSpeed);
		if (luigi)
			luigi->moveX(-moveSpeed);
	}
	else if (mario->getX() < 400 && stage1->getEdge0() < 0 - mario->getSpeed()
		&&(luigi && luigi->getRect().right < 1200)) {
		//�¿�ӵ����� ����
		mario->moveX(mario->getSpeed());
		E_Manager->moveWorld(moveSpeed);
		O_Manager->moveWorld(moveSpeed);
		stage1->moveX(moveSpeed);
		if (luigi)
			luigi->moveX(moveSpeed);
	}
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

}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================

	if (stage1) {
		stage1->render();
	}
	if (O_Manager) {
		O_Manager->render();
	}
	if (E_Manager) {
		E_Manager->render();
	}

	if (mario) {
		mario->render();
	}
	if (luigi) {
		luigi->render();
	}
	//==================== �ǵ������� =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
