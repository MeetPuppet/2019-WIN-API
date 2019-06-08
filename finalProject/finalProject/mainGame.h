#pragma once
#include "gameNode.h"

class enemyManger;
class objectManger;
class boss;
class Stage1;
class Mario;
class Coin;
class firanhaFlower;
class fireShot;
class mainGame : public gameNode//2D �����ӿ�ũ ��κ��� ��忡�� ���� ���ư�
{
private:
	Mario* mario;

	enemyManger* E_Manager;
	objectManger* O_Manger;
	Stage1* stage1;
	boss* bowser;
	Coin* coin;
	firanhaFlower* Firan;
	fireShot* Fire;
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	

	SWITCHER whatSet() override { return MAINGAME; }

	mainGame();
	~mainGame();
};

