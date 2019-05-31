#pragma once
#include "gameNode.h"
#include "playerNode.h"

class enemyManger;
class Stage1;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	playerNode* p;
	playerNode* q;

	enemyManger* E_Manager;

	//�ӽ�
	Stage1* stage1;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

