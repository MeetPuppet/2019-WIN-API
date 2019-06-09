#pragma once
#include "gameNode.h"
#include <vector>

class objectNode;
class enemyManger;

class objectManger :
	public gameNode
{
private:
	//타일 전용
	vector<objectNode*> vTile;
	vector<objectNode*> vCoin;
	vector<objectNode*> vShell;
	enemyManger* emP;
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();

	void setItemBox(RECT rc, int itemNum);
	void setBlock(RECT rc, int mode, int coins);
	void setgreenShell(int vx, int vy);
	void setgreyShell(int vx, int vy);
	void LinkToenemyManger(enemyManger* em);
	void changeToGreenTurtle();
	void changeToGreyTurtle();

	vector<objectNode*> getvTile() { return vTile; }
	bool collisionTile(RECT r, float& y);
	void moveWorld(int x);
	
	//특수한 경우가 아니면 set@@, break@@ 으로 만들기
	void setCoin(RECT rc);
	void collisionCoin(RECT r);

};

