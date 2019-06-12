#pragma once
#include "gameNode.h"
#include <vector>

class objectNode;
class greenShell;

class enemyManger;
class stageNode;
class playerNode;
class fireShot;
class objectManger :
	public gameNode
{
private:
	//타일 전용
	vector<objectNode*> vTile;
	vector<objectNode*> vCoin;
	vector<greenShell*> vShell;
	vector<fireShot*> vFireShot;

	enemyManger* emP;
	stageNode* stage;
	playerNode* player1;
	playerNode* player2;
public:
	objectManger();
	~objectManger();
	HRESULT init();
	void update();
	void render();

	void LinkToenemyManger(enemyManger* em);
	void LinkToStage(stageNode* s) { stage = s; }
	void LinkToP1(playerNode* p1) { player1 = p1; }
	void LinkToP2(playerNode* p2) { player2 = p2; }

	void setItemBox(RECT rc, int itemNum);
	void setBlock(RECT rc, int mode, int coins);

	void setFireShot(int vx, int vy, int Move);
	void setgreenShell(int vx, int vy);
	void changeToGreenShell();
	void killGreenShell();
	void kickGreenShell();

	void setgreyShell(int vx, int vy);
	void changeToGreyShell();
	void killGreyShell();


	vector<objectNode*> getvTile() { return vTile; }
	void collisionTile();
	void moveWorld(int x);
	
	//특수한 경우가 아니면 set@@, break@@ 으로 만들기
	void setCoin(RECT rc);
	void collisionCoin(RECT r);

};

