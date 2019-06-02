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
	
	//Ư���� ��찡 �ƴϸ� set@@, break@@ ���� �����
};

