#pragma once
#include "gameNode.h"
#include "playerNode.h"

class enemyManger;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
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

