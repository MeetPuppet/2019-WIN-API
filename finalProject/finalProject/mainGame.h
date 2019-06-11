#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class Stage1;
class Mario;
class Luigi;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
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

