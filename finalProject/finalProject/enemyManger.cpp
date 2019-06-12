#include "stdafx.h"
#include "enemyManger.h"

#include "Goomba.h"
#include "greenTurtle.h"
#include "objectManger.h"
#include "boss.h"
#include "playerNode.h"

enemyManger::enemyManger()
{
	vEnemy;//든거 없음
	omP = NULL;
	player1 = NULL;
	player2 = NULL;
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

	return S_OK;
}

void enemyManger::release()
{
}

void enemyManger::update()
{
	goombaUpdate();
	turtleUpdate();
	bowserUpdate();
	KillBowser();
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
void enemyManger::makeGreyTurtle(POINT point)
{
	//greyTurtle* newGreyTurtle = new greyTurtle;
	//newGreyTurtle->init(point);
	//vTurtle.emplace_back(newGreyTurtle);
}
void enemyManger::makeBowser(POINT point)
{
	boss* newBoss = new boss;
	newBoss->init(point.x, point.y, 400, 400);
	vBoss.emplace_back(newBoss);
	//newGreenTurtle->init(point);
	//newGreenTurtle->LinkToStage(stage);
	//vTurtle.emplace_back(newGreenTurtle);
}
void enemyManger::goombaUpdate()
{
	for (int i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->update();
	}
	KillGoomba();
}
void enemyManger::turtleUpdate()
{
	for (int i = 0; i < vTurtle.size(); ++i) {
		vTurtle[i]->update();
	}
	KillGreenTurtle();
}
void enemyManger::bowserUpdate()
{
	for (int i = 0; i < vBoss.size(); ++i) {
		vBoss[i]->update();
		if ((vBoss[i]->getFireNum()) % 50 == 0) {
			int FireLocate;
			if (vBoss[i]->getState() == BL_PATROL ||
				vBoss[i]->getState() == BL_CHASE ||
				vBoss[i]->getState() == BL_BRESS)
			{
				FireLocate = 1;
			}
			else
				FireLocate = 2;
			omP->setFireShot(vBoss[i]->getPoint().x, vBoss[i]->getPoint().y, FireLocate);
		}
	}
}
void enemyManger::LinkToobjectManger(objectManger* om)
{
	omP = om;
}
void enemyManger::shootFire()
{
	
}
void enemyManger::KillGoomba()
{
	RECT temp;
	for (int i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy[i]->getState() != DEAD && player1 && player1->getState() != PS_DEAD &&
			IntersectRect(&temp, &player1->getRect(), &vEnemy[i]->getRect())) {
			if (player1->getState() == PS_JUMP) {
				player1->jumpUp();
				vEnemy[i]->makeStateDead();
				SOUNDMANAGER->play("12.kick");
				//delete vEnemy[i];
				//vEnemy.erase(vEnemy.begin() + i);
			}
			else {
				player1->powerDown();
				if (player1->getState() != PS_DEAD)
					player1->jumpUp();
				SOUNDMANAGER->play("12.kick");
			}
		}
		else if (vEnemy[i]->getState() != DEAD && player2 && player2->getState() != PS_DEAD &&
			IntersectRect(&temp, &player2->getRect(), &vEnemy[i]->getRect())) {
			if (player2->getState() == PS_JUMP) {
				player2->jumpUp();
				vEnemy[i]->makeStateDead();
				SOUNDMANAGER->play("12.kick");
				//delete vEnemy[i];
				//vEnemy.erase(vEnemy.begin() + i);
			}
			else {
				player2->powerDown();
				if (player2->getState() != PS_DEAD)
					player2->jumpUp();
				SOUNDMANAGER->play("12.kick");
			}
		}
	}
}
void enemyManger::KillGreenTurtle()
{
	RECT temp;
	for (int i = 0; i < vTurtle.size(); ++i) {
		if (player1 && player1->getState() != PS_DEAD &&
			IntersectRect(&temp, &player1->getFoot(), &vTurtle[i]->getRect())) {
			if (player1->getState() == PS_JUMP) {
				//사운드
				SOUNDMANAGER->play("12.kick");
				player1->jumpUp();
				int vx = vTurtle[i]->getPoint().x;
				int vy = vTurtle[i]->getPoint().y;
				omP->setgreenShell(vx, vy);
				delete vTurtle[i];
				vTurtle.erase(vTurtle.begin() + i);
			}
			else {
				player1->powerDown();
				if(player1->getState() != PS_DEAD)
					player1->jumpUp();
			}
		}
		else if (player2 && player2->getState() != PS_DEAD &&
			IntersectRect(&temp, &player2->getFoot(), &vTurtle[i]->getRect())) {
			if (player2->getState() == PS_JUMP) {
				//사운드
				SOUNDMANAGER->play("12.kick");
				player2->jumpUp();
				int vx = vTurtle[i]->getPoint().x;
				int vy = vTurtle[i]->getPoint().y;
				omP->setgreenShell(vx, vy);
				delete vTurtle[i];
				vTurtle.erase(vTurtle.begin() + i);
			}
			else {
				player2->powerDown();
				if (player2->getState() != PS_DEAD)
					player2->jumpUp();
			}
		}
	}
}
void enemyManger::KillGreyTurtle()
{
	for (int i = 0; i < vTurtle.size(); ++i) {
		int vx = vTurtle[i]->getPoint().x;
		int vy = vTurtle[i]->getPoint().y;
		omP->setgreyShell(vx, vy);
		delete vTurtle[i];
		vTurtle.erase(vTurtle.begin() + i);
	}
}
void enemyManger::goombaRender()
{	
	for (int i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy[i]->getRect().right >= 0 && vEnemy[i]->getRect().left <= 1200)
		vEnemy[i]->render();
	}
	for (int i = 0; i < vTurtle.size(); ++i) {
		if (vTurtle[i]->getRect().right >= 0 && vTurtle[i]->getRect().left <= 1200)
		vTurtle[i]->render();
	}
	for (int i = 0; i < vBoss.size(); ++i) {
			vBoss[i]->render();
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
	for (int i = 0; i < vTurtle.size(); ++i) {
		vTurtle[i]->moveX(x);
	}
	for (int i = 0; i < vBoss.size(); ++i) {
		vBoss[i]->moveX(x);
	}
}

void enemyManger::KillBowser()
{
	RECT temp;
	for (int i = 0; i < vBoss.size(); ++i) {
		if (vBoss[i]->getPoint().y > 960) {
			delete vBoss[i];
			vBoss.clear();
		}
		if (player1 && player1->getState() != PS_DEAD && vBoss[i]->getState() != B_DEAD &&
			IntersectRect(&temp, &player1->getFoot(), &vBoss[i]->getRect())) {
			if (player1->getState() == PS_JUMP) {
				//사운드
				SOUNDMANAGER->play("12.kick");
				player1->jumpUp();
				//쿠파 죽음
				vBoss[i]->Dead();
			}
			else {
				player1->powerDown();
				if (player1->getState() != PS_DEAD)
					player1->jumpUp();
			}
		}
		else if (player2 && player2->getState() != PS_DEAD && vBoss[i]->getState() != B_DEAD &&
			IntersectRect(&temp, &player2->getFoot(), &vBoss[i]->getRect())) {
			if (player2->getState() == PS_JUMP) {
				//사운드
				SOUNDMANAGER->play("12.kick");
				player2->jumpUp();
				vBoss[i]->Dead();

			}
			else {
				player2->powerDown();
				if (player2->getState() != PS_DEAD)
					player2->jumpUp();
			}
		}
	}
}