#include "stdafx.h"
#include "enemyManger.h"

#include "Goomba.h"


enemyManger::enemyManger()
{
	vGoomba;//��� ����
}


enemyManger::~enemyManger()
{
}

HRESULT enemyManger::init()
{
	//�̱������� �̹����� �Ҵ�
	//�� Ŭ�������� �ҷ��� ����� ��
	IMAGEMANAGER->addFrameImage("Goomba", "image/enemy/goomba.bmp", 240, 80,
		3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenTurtle", "image/enemy/greenTurtle.bmp", 160, 240,
		2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greyTurtle", "image/enemy/greyTurtle.bmp", 160, 240,
		2, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void enemyManger::release()
{
}

void enemyManger::update()
{
	goombaUpdate();
}

void enemyManger::render()
{
	goombaRender();
}

void enemyManger::makeGoomba(POINT point)
{
	Goomba* newGoomba = new Goomba;
	newGoomba->init(point);
	vGoomba.emplace_back(newGoomba);
}
void enemyManger::goombaUpdate()
{
	for (int i = 0; i < vGoomba.size(); ++i) {
		vGoomba[i]->update();
	}
}
void enemyManger::KillGoomba()
{
}
void enemyManger::goombaRender()
{
	for (int i = 0; i < vGoomba.size(); ++i) {
		vGoomba[i]->render();
	}
}

void enemyManger::LinkTarget(POINT* targetPoint)
{
	for (int i = 0; i < vGoomba.size(); ++i) {
		if(vGoomba[i]->getTarget() == NULL)
			vGoomba[i]->LinkToTarget(targetPoint);
	}
}