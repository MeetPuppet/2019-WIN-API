#pragma once
#include "objectNode.h"
class Coin :
	public objectNode
{
private:
	int value;	// ����
	float level;	// �̹���
public:
	Coin();
	~Coin();
	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();

	void getCoin();
};

