#pragma once
#include "gameNode.h"

//탱크 방향
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
	//탱크 디렉션
	TANKDIRECTION	_direction;
	
	//탱크를 구성하는 요소들
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

