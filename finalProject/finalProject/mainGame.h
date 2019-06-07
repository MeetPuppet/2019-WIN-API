#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class boss;
class Stage1;
class Mario;

class mainGame : public gameNode//2D 프레임워크 대부분은 노드에서 먼저 돌아감
{
private:
	Mario* mario;

	enemyManger* E_Manager;
	objectManger* O_Manger;
	Stage1* stage1;
	boss* bowser;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	

	SWITCHER whatSet() override { return MAINGAME; }

	mainGame();
	~mainGame();
};

