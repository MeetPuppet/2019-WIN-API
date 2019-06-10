#pragma once
#include "gameNode.h"
#include <vector>

class objectNode;
class greenShell;
class enemyManger;
class stageNode;

class objectManger :
	public gameNode
{
private:
	//Ÿ�� ����
	vector<objectNode*> vTile;
	vector<objectNode*> vCoin;
	vector<greenShell*> vShell;

	enemyManger* emP;
	stageNode* stage;
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();

	void LinkToenemyManger(enemyManger* em);
	void LinkToStage(stageNode* s) { stage = s; }

	void setItemBox(RECT rc, int itemNum);
	void setBlock(RECT rc, int mode, int coins);
	void setgreenShell(int vx, int vy);
	void setgreyShell(int vx, int vy);
	void changeToGreenTurtle();
	void changeToGreyTurtle();
	void killGreenTurtle();
	void killGreyTurtle();

	vector<objectNode*> getvTile() { return vTile; }
	bool collisionTile(RECT r, float& y);
	void moveWorld(int x);
	
	//Ư���� ��찡 �ƴϸ� set@@, break@@ ���� �����
	void setCoin(RECT rc);
	void collisionCoin(RECT r);

};

