#pragma once
#include "objectNode.h"
class Coin :
	public objectNode
{
private:
	int value;	// 점수
	float level;	// 이미지
public:
	Coin();
	~Coin();
	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();

	void getCoin();
};

