#pragma once
#include "gameNode.h"
#include "enemyManger.h"
#include <vector>

class objectNode;

class objectManger :
	public gameNode
{
private:
	//Ÿ�� ����
	vector<objectNode*> vTile;
	vector<objectNode*> vCoin;
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();

	void setItemBox(RECT rc, int itemNum);
	void setBlock(RECT rc, int mode, int coins);

	vector<objectNode*> getvTile() { return vTile; }
	bool collisionTile(RECT r, float& y);
	void moveWorld(int x);
	
	//Ư���� ��찡 �ƴϸ� set@@, break@@ ���� �����
	void setCoin(RECT rc);
	void collisionCoin(RECT r);

};

