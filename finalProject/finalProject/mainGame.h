#pragma once
#include "gameNode.h"
#include "playerNode.h"

class enemyManger;
class objectManger;
class Stage1;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	playerNode* p;
	playerNode* q;

	enemyManger* E_Manager;
	objectManger* O_Manger;
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

