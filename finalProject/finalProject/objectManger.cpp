#include "stdafx.h"
#include "objectManger.h"

#include "superMuchroom.h"
#include "ItemBox.h"
#include "Block.h"
#include "Coin.h"
#include "goal.h"

#include "greenShell.h"
#include "greyShell.h"
#include "enemyManger.h"
#include "fireShot.h"
#include "playerNode.h"

objectManger::objectManger()
{
	emP = NULL;
	stage = NULL;
	player1 = NULL;
	player2 = NULL;
	ggoal = NULL;
}


objectManger::~objectManger()
{
}

HRESULT objectManger::init()
{
	IMAGEMANAGER->addFrameImage("Mushroom", "image/object/mushroom.bmp", 80, 80, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ItemBox", "image/object/itemBox.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Block", "image/object/block.bmp", 240, 160, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Coin", "image/object/coin.bmp", 240, 70, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fireShot", "image/bowser/fireShot.bmp", 240, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenShell", "image/object/greenShell.bmp", 160, 75, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greyShell", "image/object/greyShell.bmp", 160, 75, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Flag", "image/object/flag.bmp", 80, 80, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Goal", "image/object/goal.bmp", 80, 540, 1, 1, true, RGB(255, 0, 255));

	if (ggoal == NULL) {
		ggoal = new goal;
		ggoal->init();
	}


	return S_OK;
}
void objectManger::update()
{
	for (int i = 0; i < vTile.size(); ++i) {
		vTile[i]->update();
	}
	for (int i = 0; i < vCoin.size(); ++i) {
		vCoin[i]->update();
	}
	for (int i = 0; i < vShell.size(); ++i) {
		vShell[i]->update();
	}
	for (int i = 0; i < vFireShot.size(); ++i) {
		vFireShot[i]->update();
	}
	for (int i = 0; i < vMush.size(); ++i) {
		vMush[i]->update();
	}
	kickGreenShell();
	collisionTile();
	collisionMush();
	collisionFireShot();
	ggoal->update();
}
void objectManger::render()
{
	for (int i = 0; i < vTile.size(); ++i) {
		if(vTile[i]->getRect().right >= 0 && vTile[i]->getRect().left <= 1200)
			vTile[i]->render();
	}
	for (int i = 0; i < vCoin.size(); ++i) {
		if (vCoin[i]->getRect().right >= 0 && vCoin[i]->getRect().left <= 1200)
			vCoin[i]->render();
	}
	for (int i = 0; i < vShell.size(); ++i) {
		if (vShell[i]->getRect().right >= 0 && vShell[i]->getRect().left <= 1200)
			vShell[i]->render();
	}
	for (int i = 0; i < vFireShot.size(); ++i) {
		if (vFireShot[i]->getRect().right >= 0 && vFireShot[i]->getRect().left <= 1200)
			vFireShot[i]->render();
	}
	for (int i = 0; i < vMush.size(); ++i) {
		vMush[i]->render();
	}
	ggoal->render();
}

void objectManger::LinkToenemyManger(enemyManger* em)
{
	emP = em;
}
void objectManger::setItemBox(RECT rc, int itemNum)
{
	ItemBox* box = new ItemBox;
	box->init((rc.right - rc.left) /2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top, itemNum);
	if (player1)
		box->LinkToP1(player1);
	if (player2)
		box->LinkToP2(player2);

	vTile.emplace_back(box);
}
//void objectManger::setBlock(RECT rc, int mode, int coins)
//{
//	Block* box = new Block;
//	box->init((rc.right - rc.left) / 2 + rc.left,
//		(rc.bottom - rc.top) / 2 + rc.top,
//		rc.right - rc.left,
//		rc.bottom - rc.top, mode, coins);
//	if (player1)
//		box->LinkToP1(player1);
//	if (player2)
//		box->LinkToP2(player2);
//
//	vTile.emplace_back(box);
//}
void objectManger::setgreenShell(int vx, int vy)
{
	greenShell* Shell = new greenShell;
	Shell->init(vx, vy, 80, 75);
	if (player1)
		Shell->LinkToP1(player1);
	if (player2)
		Shell->LinkToP2(player2);
	vShell.emplace_back(Shell);
}
void objectManger::setgreyShell(int vx, int vy)
{
	//greyShell* Shell = new greyShell;
	//Shell->init(vx, vy, 80, 75);
	//vShell.emplace_back(Shell);
}
void objectManger::setFireShot(int vx, int vy,int Move)
{
	fireShot* Fire = new fireShot;
	Fire->init(vx, vy, 120, 40, Move);
	vFireShot.emplace_back(Fire);
}
void objectManger::changeToGreenShell()
{
	for (int i = 0; i < vShell.size(); ++i) {
		if (vShell[i]->getTime() > 2)
		{
			POINT p;
			p.x = vShell[i]->getPoint().x;
			p.y = vShell[i]->getPoint().y;
			emP->makeGreenTurtle(p);
			delete vShell[i];
			vShell.erase(vShell.begin() + i);
		}
	}
}
void objectManger::changeToGreyShell()
{
	for (int i = 0; i < vShell.size(); ++i) {
		POINT p;
		p.x = vShell[i]->getPoint().x;
		p.y = vShell[i]->getPoint().y;
		emP->makeGreyTurtle(p);
		delete vShell[i];
		vShell.erase(vShell.begin() + i);
	}
}
void objectManger::killGreenShell()
{
	RECT temp;
	for (int i = 0; i < vShell.size(); ++i) {
		delete vShell[i];
		vShell.erase(vShell.begin() + i);
	}
}
void objectManger::kickGreenShell()
{
	RECT temp;
	for (int i = 0; i < vShell.size(); ++i) {
		//플레이어1이 점프 상태이고 대상 범위와 충돌할때
		if (player1 && IntersectRect(&temp, &player1->getRect(), &vShell[i]->getRect())) {
			if (player1->getState() == PS_JUMP) {
				player1->jumpUp();
			}
			if (vShell[i]->getKicked() == false) {
				if (player1->getPoint().x < vShell[i]->getPoint().x) {
					vShell[i]->kicked(true);
					SOUNDMANAGER->play("12.kick");
				}
				else {
					vShell[i]->kicked(false);
					SOUNDMANAGER->play("12.kick");
				}
			}
			else {
				if (player1->getState() != PS_JUMP) {
					player1->powerDown();
				}
				player1->jumpUp();
				vShell[i]->stop();
				
			}
		}
		//플레이어2가 점프 상태이고 대상 범위와 충돌할때
		else if (player2 && IntersectRect(&temp, &player2->getRect(), &vShell[i]->getRect())) {
			if (player2->getState() == PS_JUMP) {
				player2->jumpUp();
			}
			if (vShell[i]->getKicked() == false) {
				if (player2->getPoint().x < vShell[i]->getPoint().x) {
					vShell[i]->kicked(true);
					SOUNDMANAGER->play("12.kick");
				}
				else {
					vShell[i]->kicked(false);
					SOUNDMANAGER->play("12.kick");
				}
			}
			else {
				if (player2->getState() != PS_JUMP) {
					player2->powerDown();
				}
				player2->jumpUp();
				vShell[i]->stop();

			}
		}
	}
}
void objectManger::killGreyShell()
{
	for (int i = 0; i < vShell.size(); ++i) {
		delete vShell[i];
		vShell.erase(vShell.begin() + i);
	}
}
void objectManger::moveWorld(int x) {
	for (int i = 0; i < vTile.size(); ++i) {
		vTile[i]->moveX(x);
	}
	for (int i = 0; i < vCoin.size(); ++i) {
		vCoin[i]->moveX(x);
	}
	for (int i = 0; i < vShell.size(); ++i) {
		vShell[i]->moveX(x);
	}
	for (int i = 0; i < vFireShot.size(); ++i) {
		vFireShot[i]->moveX(x);
	}
	for (int i = 0; i < vMush.size(); ++i) {
		vMush[i]->moveX(x);
	}
	ggoal->moveX(x);
}


void objectManger::setCoin(RECT rc)
{
	Coin* coin = new Coin;
	coin->init((rc.right - rc.left) / 2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top);

	vCoin.emplace_back(coin);
}
void objectManger::collisionCoin(RECT r)
{
	RECT temp;
	for (int i = 0; i < vCoin.size(); ++i) {
		if (IntersectRect(&temp, &r, &vCoin[i]->getRect())) {
			//UI에서 점수가 올라가야 한다.
			//현재 코인을 지워야 한다.
			SOUNDMANAGER->play("10.coin");
			delete vCoin[i];
			vCoin.erase(vCoin.begin() + i);
		}
	}
}
void objectManger::collisionTile()
{
	RECT temp;
	for (int i = 0; i < vTile.size(); ++i) {
		if (player1 && player1->getState() == PS_JUMP && vTile[i]->isHaveIn() &&
			IntersectRect(&temp, &vTile[i]->getRect(), &player1->getRect())) {
			if (vTile[i]->getItemNum() == 4) {
				temp = vTile[i]->getRect();
				temp.top -= 80;
				temp.bottom -= 80;
				setMush(temp);
			}
			else {
				temp = vTile[i]->getRect();
				temp.top -= 80;
				temp.bottom -= 80;
				setCoin(temp);
			}

			vTile[i]->active();
		}
		else if (player2 && player2->getState() == PS_JUMP && vTile[i]->isHaveIn() &&
			IntersectRect(&temp, &vTile[i]->getRect(), &player2->getRect())) {
			if (vTile[i]->getItemNum() == 4) {
				temp = vTile[i]->getRect();
				temp.top -= 80;
				temp.bottom -= 80;
				setMush(temp);
			}
			else {
				temp = vTile[i]->getRect();
				temp.top -= 80;
				temp.bottom -= 80;
				setCoin(temp);
			}

			vTile[i]->active();
		}
	}
}

void objectManger::setMush(RECT rc)
{
	SuperMuchroom* Mush = new SuperMuchroom;
	Mush->init((rc.right - rc.left) / 2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top);

	vMush.emplace_back(Mush);
}
void objectManger::collisionMush()
{
	RECT temp;
	for (int i = 0; i < vMush.size(); ++i) {
		if (player1 && IntersectRect(&temp, &player1->getRect(), &vMush[i]->getRect())) {
			if (player1->getMode() == PM_SMALL) {
				player1->powerUp();
				delete vMush[i];
				vMush.erase(vMush.begin() + i);
			}
			
		}
		else if (player2 && IntersectRect(&temp, &player2->getRect(), &vMush[i]->getRect())) {
			if (player2->getMode() == PM_SMALL) {
				player2->powerUp();
				delete vMush[i];
				vMush.erase(vMush.begin() + i);
			}
		}
	}
}
