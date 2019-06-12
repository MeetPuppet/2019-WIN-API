#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class Stage1;
class Mario;
class Luigi;

class world1 :
	public gameNode
{
private:
	int players;
	float musictime;
	BYTE alpha;
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
	world1();
	world1(int getPlayer);
	~world1();
};

