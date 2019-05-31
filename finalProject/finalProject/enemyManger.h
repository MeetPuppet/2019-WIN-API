#pragma once
#include <vector>
#include "gameNode.h"

class Goomba;

class enemyManger :
	public gameNode
{
private:
	vector<Goomba*> vGoomba;
	void goombaUpdate();
	void goombaRender();
public:
	enemyManger();
	~enemyManger();

	HRESULT init();
	void release();
	void update();
	void render();

	void makeGoomba(POINT point);
	//���̱�� ���߿� ������ �ް�
	void KillGoomba();

	void LinkTarget(POINT* targetPoint = NULL);
};

