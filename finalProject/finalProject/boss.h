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
	Point p;//������ġ
	RECT rc;//�浹�� �簢��
	bool JUMP;
	float FrameCheck;
	float jumpPower;
	float time;

	int frameX;
	int frameY;
	int oldpx, oldpy;
	int groundx1, groundx2;
	float jumpnum;
	int frameNum;
	bool movenum;
	int FireNum;

	POINT* targetPoint;
	//AI�� �Լ���ġ
	//inline bool playerSearch(POINT* playerPoint);
public:
	boss();
	~boss();


	HRESULT init(int x, int y, int g1, int g2);
	void release();
	void update();
	void render();
	void FrameSeter();
	B_STATE getState();
	Point getPoint();
	RECT getRect() { return rc; }
	void Dead()
	{
		jumpPower = 3;
		state = B_DEAD;
	}


	int getFireNum();
	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	void AI(POINT* playerPoint = NULL);

	POINT* getTarget() { return getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}

	void moveX(float X)
	{
		p.x += X;
		oldpx += X;
	}
};

