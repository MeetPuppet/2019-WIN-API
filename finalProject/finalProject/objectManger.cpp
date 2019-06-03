#include "stdafx.h"
#include "objectManger.h"
#include "ItemBox.h"
#include "Block.h"


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
	return S_OK;
}
void objectManger::update()
{
	for (int i = 0; i < vObject.size(); ++i) {
		vObject[i]->update();
	}
}
void objectManger::render()
{
	for (int i = 0; i < vObject.size(); ++i) {
		vObject[i]->render();
	}
}

void objectManger::setItemBox(RECT rc, int itemNum)
{
	ItemBox* box = new ItemBox;
	box->init((rc.right - rc.left) /2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top, itemNum);

	vObject.emplace_back(box);
}
void objectManger::setBlock(RECT rc, int mode, int coins)
{
	Block* box = new Block;
	box->init((rc.right - rc.left) / 2 + rc.left,
		(rc.bottom - rc.top) / 2 + rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top, mode, coins);

	vObject.emplace_back(box);
}
void objectManger::moveWorld(int x) {
	for (int i = 0; i < vObject.size(); ++i) {
		vObject[i]->moveX(x);
	}
}