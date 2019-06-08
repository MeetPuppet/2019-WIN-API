#include "stdafx.h"
#include "Coin.h"



Coin::Coin()
{
	value = 200;
	level = 0;
}


Coin::~Coin()
{

}

HRESULT Coin::init(int x, int y, int sizeX, int sizeY)
{
	objectNode::init("Coin", x, y, sizeX, sizeY);

	value = 200;
	level = 0;

	return S_OK;
}
void Coin::update()
{
	objectNode::update();
	level += 0.09;
	if (level >= 0 && level < 1) {
		frameX = 0;
	}
	else if (level >= 1 && level < 2) {
		frameX = 1;
	}
	else if (level >= 2 && level < 3) {
		frameX = 2;
	}
	if (level >= 3) {
		level = 0;
	}
}

void Coin::render()
{
	objectNode::render();
}
void Coin::getCoin()
{
	// p.x > x && p.x < x + sizeX ~~~~
		// score+=value;
	return;
}