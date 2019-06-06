#pragma once
#include "gameNode.h"


enum B_STATE {
	BL_PATROL,
	BR_PATROL,
	BL_CHASE,
	BR_CHASE,
	BL_BRESS,
	BR_BRESS,
	B_DEAD
};

class boss :
	public gameNode
{
private:
	image* Img;
	B_STATE state;
	Point p;//중점위치
	RECT rc;//충돌용 사각형
	bool JUMP;
	float FrameCheck;
	float speed;
	float gravity;

	int frameX;
	int frameY;
	int jumpnum;

	POINT* targetPoint;
	//AI용 함수위치
	//inline bool playerSearch(POINT* playerPoint);
public:
	boss();
	~boss();


	HRESULT init(int x,int y);
	void release();
	void update();
	void render();
	void FrameSeter();
	B_STATE getState();

	//플레이어 할당이 해제될 경우 동작을 막을 것
	void AI(POINT* playerPoint = NULL);

	POINT* getTarget() { return getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}

	void moveX(int X)
	{
		p.x += X;
	}
};

