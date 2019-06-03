#pragma once
#include "objectNode.h"
class ItemBox :
	public objectNode
{
private:
	int itemNum;
	float frameXAC;
	bool haveIn;
public:
	ItemBox();
	~ItemBox();
	HRESULT init(int x, int y, int sizeX, int sizeY, int itemNuber);
	void update();
	void render();

	void frameMove();
	void active();
};
