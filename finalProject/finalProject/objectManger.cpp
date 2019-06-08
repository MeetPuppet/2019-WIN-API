#include "stdafx.h"
#include "objectManger.h"
#include "ItemBox.h"
#include "Block.h"
#include "Coin.h"

objectManger::objectManger()
{
}


objectManger::~objectManger()
{
}

HRESULT objectManger::init()
{
	IMAGEMANAGER->addFrameImage("ItemBox", "image/object/itemBox.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Block", "image/object/block.bmp", 240, 160, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Coin", "image/object/coin.bmp", 240, 70, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fireShot", "image/bowser/fireShot.bmp", 96, 18, 2, 1, true, RGB(255, 0, 255));
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
}
void objectManger::render()
{
	for (int i = 0; i < vTile.size(); ++i) {
		vTile[i]->render();
	}
	for (int i = 0; i < vCoin.size(); ++i) {
		vCoin[i]->render();
	}
}

void objectManger::setItemBox(RECT rc, int itemNum)
{
	ItemBox* box = new ItemBox;
	box->init((rc.right - rc.left) /2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top, itemNum);

	vTile.emplace_back(box);
}
void objectManger::setBlock(RECT rc, int mode, int coins)
{
	Block* box = new Block;
	box->init((rc.right - rc.left) / 2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top, mode, coins);

	vTile.emplace_back(box);
}
void objectManger::moveWorld(int x) {
	for (int i = 0; i < vTile.size(); ++i) {
		vTile[i]->moveX(x);
	}
}
bool objectManger::collisionTile(RECT r, float& y) {
	RECT temp;
	for (int i = 0; i < vTile.size(); ++i) {
		if (IntersectRect(&temp, &r, &vTile[i]->getRect())) {
			y = vTile[i]->getRect().top - (r.bottom - r.top)/2;
			return true;
		}
		return false;
	}
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
			vCoin.erase(vCoin.begin() + i);
		}
	}
}