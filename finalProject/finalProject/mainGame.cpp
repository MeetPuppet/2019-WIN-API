#include "stdafx.h"
#include "mainGame.h"

#include "enemyManger.h"

//임시
#include "Stage1.h"

mainGame::mainGame()
{
	E_Manager = NULL;
	stage1 = NULL;
}

mainGame::~mainGame()
{

}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);
	
	p = new playerNode;//객체 할당
	q = new playerNode;//객체 할당
	p->init("mario","image/player/mario.bmp",1);//객체 초기화
	q->init("ruigi", "image/player/Luigi.bmp",2);//객체 초기화

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

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();
	delete p;//할당 해제
	delete q;

	if (E_Manager) {
		delete E_Manager;
	}
	if (stage1) {
		delete stage1;
	}
}

void mainGame::update()				//연산 함수
{
	gameNode::update();

	p->update();//객체 업데이트
	q->update();

	E_Manager->update();
	//오른쪽 마우스키 누른자리에 적 생성
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		E_Manager->makeGoomba(_ptMouse);
	}

	stage1->update();
	stage1->setMainPosition({p->getX(), 0});
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	stage1->render();
	E_Manager->render();
	p->render();//객체 출력
	q->render();
	
	//==================== 건들지마라 =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
