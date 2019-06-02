#pragma once
#include <vector>
#include "gameNode.h"

class enemyNode;

class enemyManger :
	public gameNode
{
private:
	vector<enemyNode*> vEnemy;
	void goombaUpdate();
	void goombaRender();
	bool GoombaCollisionCheck(const RECT& rc);
public:
	enemyManger();
	~enemyManger();

	HRESULT init();
	void release();
	void update();
	void render();
	bool enemyCollisionCheck(RECT rc);

	void makeGoomba(POINT point);
	//죽이기는 나중에 조건을 달것
	void KillGoomba();

	void LinkTarget(POINT* targetPoint = NULL);

	void moveWorld(int x);
};

