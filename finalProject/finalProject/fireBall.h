#pragma once
#include "objectNode.h"
class fireBall :
	public objectNode
{
private:
	int move; // ÁÂ ¿ì °áÁ¤
public:
	fireBall();
	~fireBall();

	HRESULT init(int x, int y,int sizeX,int sizeY,int Move);
	void release();
	void update();
	void render();
};

