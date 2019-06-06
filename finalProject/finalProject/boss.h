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
	float speed;
	float gravity;

	int frameX;
	int frameY;
	int jumpnum;

	POINT* targetPoint;
	//AI�� �Լ���ġ
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

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
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

