#pragma once
#include "gameNode.h"
#include "playerNode.h"

class enemyManger;
class Stage1;

class mainGame : public gameNode//2D 프레임워크 대부분은 노드에서 먼저 돌아감
{
private:
	playerNode* p;
	playerNode* q;

	enemyManger* E_Manager;

	//임시
	Stage1* stage1;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

