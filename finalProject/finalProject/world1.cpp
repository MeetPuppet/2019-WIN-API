#include "stdafx.h"
#include "world1.h"

#include "Mario.h"
#include "Luigi.h"
#include "enemyManger.h"
#include "objectManger.h"
#include "Stage1.h"


world1::world1()
{
	mario = NULL;
	luigi = NULL;
	E_Manager = NULL;
	O_Manager = NULL;
	stage1 = NULL;
	alpha = 0;
	players = 1;
	musictime = 0;
}
world1::world1(int getPlayer)
{
	mario = NULL;
	luigi = NULL;
	E_Manager = NULL;
	O_Manager = NULL;
	stage1 = NULL;
	alpha = 0;
	players = 1;
	players = getPlayer;
}


world1::~world1()
{
}

HRESULT world1::init()			//초기화 함수
{

	if (mario == NULL) {
		mario = new Mario;
		mario->init(Point(WINSIZEX / 2-100, WINSIZEY / 2));
	}
	if (luigi == NULL && players == 2) {
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

		//생성용 참고
		if (O_Manager) {//init보다 먼저 돌릴것
			stage1->LinkToOBJ(O_Manager);
			O_Manager->LinkToStage(stage1);
		}
		if (E_Manager) {
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
	SOUNDMANAGER->play("01.world1");

	return S_OK;
}

void world1::release()			//메모리 해제 함수
{
	//delete p;//할당 해제
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

void world1::update()				//연산 함수
{
	if (mario && mario->getPoint().x > 1100 && !luigi) {
		//클리어
		SOUNDMANAGER->stop("01.world1");
		if (!SOUNDMANAGER->isPlaySound("02.comple1"))
			SOUNDMANAGER->play("02.comple1");
		float time = TIMEMANAGER->getElapsedTime();
		if (time < 0) time = 0.016;
		musictime += time;
		if (alpha < 250) {
			alpha += 150 * time;
		}
		else if (musictime > 9.f) {
			SOUNDMANAGER->stop("02.comple1");
			SCENEMANAGER->changeScene("P1world2");
		}
	}
	else if (mario && luigi 
		&& luigi->getPoint().x > 1100
		&& mario->getPoint().x > 1100) {
		//클리어
		SOUNDMANAGER->stop("01.world1");
		if (!SOUNDMANAGER->isPlaySound("02.comple1"))
		SOUNDMANAGER->play("02.comple1");
		float time = TIMEMANAGER->getElapsedTime();
		if (time < 0) time = 0.016;
		musictime += time;
		if (alpha < 250) {
			alpha += 150 * time;
		}
		else if (musictime > 9.f) {
			SOUNDMANAGER->stop("02.comple1");
			SCENEMANAGER->changeScene("P2world2");
		}
	}
	else if (mario == NULL && luigi == NULL) {
		SOUNDMANAGER->stop("01.world1");
		SOUNDMANAGER->stop("05.dead");
		if(!SOUNDMANAGER->isPlaySound("06.gameOver"))
			SOUNDMANAGER->play("06.gameOver");
		float time = TIMEMANAGER->getElapsedTime();
		if (time < 0) time = 0.016;
		musictime += time;
		if (alpha < 250) {
			alpha += 150 * time;
		}
		else if (musictime > 7.f) {
			SOUNDMANAGER->stop("06.gameOver");
			SCENEMANAGER->changeScene("title");
		}
	}
	else {

		if (mario && mario->getPoint().y > 880) {
			mario->dead();
		}
		if (luigi && luigi->getPoint().y > 880) {
			mario->dead();
			luigi->dead();
		}

		if (SOUNDMANAGER->isPlaySound("05.dead")) {
			SOUNDMANAGER->pause("01.world1");
		}
		else if (((luigi&&luigi->getState() != PS_DEAD) ||
			(mario&&mario->getState() != PS_DEAD)) &&
			SOUNDMANAGER->isPauseSound("01.world1")) {
			SOUNDMANAGER->resume("01.world1");
		}
		if (mario && mario->getPoint().y < 880) {
			mario->update();
			if (luigi && luigi->getState() == PS_DEAD) {
				mario->dead();
			}
		}
		else if (mario && mario->getPoint().y > 880
			&& mario->getState() == PS_DEAD) {
			delete mario;
			mario = NULL;
			E_Manager->LinkToP1(mario);
			O_Manager->LinkToP1(mario);
		}
		if (luigi&& luigi->getPoint().y < 880) {
			luigi->update();
			if (mario && mario->getState() == PS_DEAD) {
				mario->dead();
			}
		}
		else if (luigi && luigi->getPoint().y > 880
			&& luigi->getState() == PS_DEAD) {
			if (luigi) {
				delete luigi;
				luigi = NULL;
				E_Manager->LinkToP2(luigi);
				O_Manager->LinkToP2(luigi);
			}
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
		if (mario) {
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
			else if (mario->getX() > 800 && stage1->getEdge1() > 1200 + mario->getSpeed()
				&& !luigi) {
				mario->moveX(-mario->getSpeed());
				E_Manager->moveWorld(-moveSpeed);
				O_Manager->moveWorld(-moveSpeed);
				stage1->moveX(-moveSpeed);
			}
			if (mario->getX() < 400 && stage1->getEdge0() < 0 - mario->getSpeed()
				&& (luigi && luigi->getRect().right < 1200)) {
				//좌우속도차가 있음
				mario->moveX(mario->getSpeed());
				E_Manager->moveWorld(moveSpeed);
				O_Manager->moveWorld(moveSpeed);
				stage1->moveX(moveSpeed);
				if (luigi)
					luigi->moveX(moveSpeed);
			}
			else if (mario->getX() < 400 && stage1->getEdge0() < 0 - mario->getSpeed()
				&& !luigi) {
				mario->moveX(mario->getSpeed());
				E_Manager->moveWorld(moveSpeed);
				O_Manager->moveWorld(moveSpeed);
				stage1->moveX(moveSpeed);
			}
		}
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

void world1::render()		//그려주는 함수(a.k.a WM_PAINT)
{
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

	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), alpha);
	
}
