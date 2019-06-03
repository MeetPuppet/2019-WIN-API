#pragma once
#include "gameNode.h"
#include <vector>

class objectNode;

class objectManger :
	public gameNode
{
private:
	vector<objectNode*> vObject;
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();

	void setItemBox(RECT rc, int itemNum);
	void setBlock(RECT rc, int mode, int coins);

	void moveWorld(int x);
	
	//특수한 경우가 아니면 set@@, break@@ 으로 만들기
};

