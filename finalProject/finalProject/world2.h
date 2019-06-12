#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class stage2;
class Mario;
class Luigi;

class world2 :
	public gameNode
{
	int players;
	float musictime;
	BYTE alpha;
	Mario* mario;
	Luigi* luigi;

	enemyManger* E_Manager;
	objectManger* O_Manager;
	stage2* stage1;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	world2();
	world2(int getPlayer);
	~world2();
};

