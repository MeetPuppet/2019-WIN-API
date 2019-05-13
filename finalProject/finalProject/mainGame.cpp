#include "stdafx.h"
#include "mainGame.h"
#include "tank.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);
	
	Tank = new tank;//객체 할당
	Tank->init();//객체 초기화
	Tank->setTankPosition();//init에서 인자를 받아서 돌려도 됨

	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();
	delete Tank;//할당 해제
	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();

	Tank->update();//객체 업데이트
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	Tank->render();//객체 출력
	
	//==================== 건들지마라 =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
