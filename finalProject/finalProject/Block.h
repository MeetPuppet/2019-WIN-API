#pragma once
#include "objectNode.h"
class Block :
	public objectNode
{
private:
	int coin;
	int mode;
public:
	Block();
	~Block();
	HRESULT init(int x, int y, int sizeX, int sizeY, int Mode, int Coin);
	void update();
	void render();

	void beatBox();
};

