#pragma once
#include "gameNode.h"
#include "playerNode.h"

class enemyManger;

class mainGame : public gameNode//2D 프레임워크 대부분은 노드에서 먼저 돌아감
{
private:
	playerNode* p;
	playerNode* q;

	enemyManger* E_Manager;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

