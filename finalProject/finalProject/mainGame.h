#pragma once
#include "gameNode.h"

class tank;

class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	tank* Tank;

public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

