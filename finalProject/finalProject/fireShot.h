#pragma once
#include "objectNode.h"
class fireShot :
	public objectNode
{
private:
	int move; // ÁÂ ¿ì °áÁ¤
public:
	fireShot();
	~fireShot();

	HRESULT init(int x, int y,int sizeX,int sizeY,int Move);
	void release();
	void update();
	void render();
};

