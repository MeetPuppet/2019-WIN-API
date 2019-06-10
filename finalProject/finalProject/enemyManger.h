#pragma once
#include <vector>
#include "gameNode.h"

class enemyNode;
class objectManger;
class stageNode;

class enemyManger :
	public gameNode
{
private:
	vector<enemyNode*> vEnemy;
	vector<enemyNode*> vTurtle;
	void goombaUpdate();
	void turtleUpdate();
	void goombaRender();
	objectManger* omP;
	stageNode* stage;
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
	
	void makeGoomba(POINT point);
	void makeGreenTurtle(POINT point);
	void makeGreyTurtle(POINT point);
	//죽이기는 나중에 조건을 달것
	void KillGoomba();
	void KillGreenTurtle();
	void KillGreyTurtle();

	void LinkTarget(POINT* targetPoint = NULL);

	void moveWorld(int x);
};

