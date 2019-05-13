#pragma once
#include "gameNode.h"

//��ũ ����
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
	//��ũ �𷺼�
	TANKDIRECTION	_direction;
	
	//��ũ�� �����ϴ� ��ҵ�
	image*			_image;
	RECT			_rc;
	float			_x, _y;
	float			_speed;

public:
	tank();
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	void setTankPosition();

};

