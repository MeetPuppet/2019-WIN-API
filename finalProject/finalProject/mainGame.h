#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class Stage1;
class Mario;
class Luigi;

class mainGame : public gameNode//2D 프레임워크 대부분은 노드에서 먼저 돌아감
{
private:
	Mario* mario;
	Luigi* luigi;

	enemyManger* E_Manager;
	objectManger* O_Manager;
	Stage1* stage1;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	

	SWITCHER whatSet() override { return MAINGAME; }

	mainGame();
	~mainGame();
};

