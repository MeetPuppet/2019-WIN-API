#include "stdafx.h"
#include "Block.h"



Block::Block()
{
	mode = 0;
	coin = 0;
}


Block::~Block()
{
}

HRESULT Block::init(int x, int y, int sizeX, int sizeY, int Mode, int Coin)
{
	objectNode::init("Block", x, y, sizeX, sizeY);

	mode = Mode;
	if (Mode == 0) {
		coin = Coin;
	}

	return S_OK;
}
void Block::update()
{
	objectNode::update();
	if (mode == 0) {
		frameX = 0;
	}
	else if(mode == 1){
		frameX = 1;
	}
	else if (mode == 3) {
		if (coin <= 0) {
			frameX = 2;
		}
		else {
			frameX = 0;
		}
	}
}
void Block::render()
{
	objectNode::render();
}
void Block::beatBox()
{
	if (mode == 3 && coin > 0) {
		//Á¡¼öÁÜ
		--coin;
	}
	else if (mode == 0) {
		//ºÎ¼ÅÁü
	}
	return;
}