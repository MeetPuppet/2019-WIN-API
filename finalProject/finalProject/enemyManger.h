#pragma once
#include <vector>
#include "gameNode.h"

class enemyNode;
class Goomba;
class objectManger;
class stageNode;
class playerNode;

class enemyManger :
	public gameNode
{
private:
	vector<Goomba*> vEnemy;
	vector<enemyNode*> vTurtle;

	void goombaUpdate();
	void turtleUpdate();
	void goombaRender();

	objectManger* omP;
	stageNode* stage;
	playerNode* player1;
	playerNode* player2;

	bool GoombaCollisionCheck(const RECT& rc);
public:
	enemyManger();
	~enemyManger();

	HRESULT init();
	void release();
	void update();
	void render();
	bool enemyCollisionCheck(RECT rc);

	void LinkToobjectManger(objectManger* om);
	void LinkToStage(stageNode* s) { stage = s; }
	void LinkToP1(playerNode* p1) { player1 = p1; }
	void LinkToP2(playerNode* p2) { player2 = p2; }
	
	void makeGoomba(POINT point);
	void makeGreenTurtle(POINT point);
	void makeGreyTurtle(POINT point);
	//���̱�� ���߿� ������ �ް�
	void KillGoomba();
	void KillGreenTurtle();
	void KillGreyTurtle();

	void LinkTarget(POINT* targetPoint = NULL);

	void moveWorld(int x);
};

