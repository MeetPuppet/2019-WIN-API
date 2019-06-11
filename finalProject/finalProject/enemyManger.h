#pragma once
#include <vector>
#include "gameNode.h"

class enemyNode;
class Goomba;
class objectManger;
class stageNode;
class playerNode;
class boss;
class enemyManger :
	public gameNode
{
private:
	vector<Goomba*> vEnemy;
	vector<enemyNode*> vTurtle;
	vector<boss*> vBoss;

	void goombaUpdate();
	void turtleUpdate();
	void bowserUpdate();
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
	void makeBowser(POINT point);
	void shootFire();
	//죽이기는 나중에 조건을 달것
	void KillGoomba();
	void KillGreenTurtle();
	void KillGreyTurtle();

	void LinkTarget(POINT* targetPoint = NULL);

	void moveWorld(int x);
};

