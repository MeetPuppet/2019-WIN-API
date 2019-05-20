#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);
	
	p = new playerNode;//객체 할당
	p->init("mario","image/player/fireSuit.bmp");//객체 초기화

	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();
	delete p;//할당 해제
	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();

	p->update();//객체 업데이트
}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	p->render();//객체 출력
	
	//==================== 건들지마라 =======================
	
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
