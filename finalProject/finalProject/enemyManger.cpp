#include "stdafx.h"
#include "enemyManger.h"

#include "Goomba.h"
#include "firanhaFlower.h"
#include "greenTurtle.h"
#include "objectManger.h"
enemyManger::enemyManger()
{
	vEnemy;//든거 없음
}


enemyManger::~enemyManger()
{
}

HRESULT enemyManger::init()
{
	//싱글톤으로 이미지만 할당
	//각 클래스별로 불러서 사용할 것
	IMAGEMANAGER->addFrameImage("Goomba", "image/enemy/goomba.bmp", 240, 80,
		3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenTurtle", "image/enemy/greenTurtle.bmp", 160, 240,
		2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greyTurtle", "image/enemy/greyTurtle.bmp", 160, 240,
		2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bowser", "image/bowser/bowser.bmp", 640, 320,
		4, 2, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addFrameImage("firanhaFlower", "image/enemy/firanhaFlower.bmp", 160, 120,
		2, 1, true, RGB(255, 0, 255));
	omP = NULL;

	return S_OK;
}

void enemyManger::release()
{
}

void enemyManger::update()
{
	goombaUpdate();
}

void enemyManger::render()
{
	goombaRender();
}

void enemyManger::makeGoomba(POINT point)
{
	Goomba* newGoomba = new Goomba;
	newGoomba->init(point);
	vEnemy.emplace_back(newGoomba);
}
void enemyManger::makeGreenTurtle(POINT point)
{
	greenTurtle* newGreenTurtle = new greenTurtle;
	newGreenTurtle->init(point);
	vTurtle.emplace_back(newGreenTurtle);
}
void enemyManger::goombaUpdate()
{
	for (int i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->update();
	}
}
void enemyManger::turtleUpdate()
{
	for (int i = 0; i < vTurtle.size(); ++i) {
		vTurtle[i]->update();
	}
}

void enemyManger::LinkToobjectManger(objectManger* om)
{
	omP = om;
}
void enemyManger::KillGoomba()
{
}
void enemyManger::KillGreenTurtle()
{
	for (int i = 0; i < vTurtle.size(); ++i) {
		vTurtle.erase(vTurtle.begin() + i);
	}
	//for (int i = 0; i < vTurtle.size(); ++i) {
	//	greenShell* newGreenShell = new greenShell;
	//	newGreenShell->init(vTurtle[i]->getPoint().x, vTurtle[i]->getPoint().y, 80, 75);
	//	
	//}
	int vx = vTurtle[0]->getPoint().x;
	int vy = vTurtle[0]->getPoint().y;
	omP->setgreenShell(vx, vy);
}
void enemyManger::goombaRender()
{
	for (int i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->render();
	}
}
void enemyManger::LinkTarget(POINT* targetPoint)
{
	for (int i = 0; i < vEnemy.size(); ++i) {
		if(vEnemy[i]->getTarget() == NULL)
			vEnemy[i]->LinkToTarget(targetPoint);
	}
}

bool enemyManger::enemyCollisionCheck(RECT rc)
{
	if (GoombaCollisionCheck(rc)) {
		return true;
	}
	return false;
}
bool enemyManger::GoombaCollisionCheck(const RECT& rc)
{
	RECT temp;
	for (int i = 0; i < vEnemy.size(); ++i) {
		if (IntersectRect(&temp,&vEnemy[i]->getRect(),&rc)) {
			return true;
		}
	}
	return false;
}

void enemyManger::moveWorld(int x) {
	for (int i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->moveX(x);
	}
}