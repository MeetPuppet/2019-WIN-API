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

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);
	
	//p = new playerNode;//객체 할당
	//q = new playerNode;//객체 할당
	//p->init("mario","image/player/mario.bmp",1);//객체 초기화
	//q->init("ruigi", "image/player/Luigi.bmp",2);//객체 초기화

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

		//생성용 참고
		if (O_Manger)//init보다 먼저 돌릴것
			stage1->LinkToOBJ(O_Manger);

		stage1->init();
	}

	bowser = new boss;

	bowser->init(600, 300);
	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();
	//delete p;//할당 해제
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

void mainGame::update()				//연산 함수
{
	gameNode::update();

	//RECT를 넣어주면 충돌했는지 안했는지 bool값으로 반환 해주는 함수
	//if (E_Manager->enemyCollisionCheck(RECT)) {}


	//오른쪽 마우스키 누른자리에 적 생성
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
	//	//좌우속도차가 있음
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

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

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
	//==================== 건들지마라 =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
