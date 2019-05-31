#pragma once
#include "gameNode.h"

#define ENEMY_FRAME_SPEEDER 1
//���°�
enum E_STATE {
	EL_PATROL,
	ER_PATROL,
	EL_CHASE,
	ER_CHASE,
	DEAD
};

class enemyNode :
	public gameNode
{
protected:
	image* img;//�̹���
	E_STATE state;
	POINT p;//������ġ
	RECT rc;//�浹�� �簢��

	float FrameCheck;
	float speed;
	float gravity;

	int frameX;
	int frameY;

	POINT* targetPoint;
	//AI�� �Լ���ġ
	inline bool playerSearch(POINT* playerPoint);
public:
	enemyNode();
	~enemyNode();

	// ���� ���� ��ġ
	virtual HRESULT init(const char* keyName, POINT point);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void FrameSeter();

	//�浹 Ȯ�ο�
	POINT getPoint() { return p; }
	RECT getRect() { return rc; }

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	virtual void AI(POINT* playerPoint = NULL);
	virtual POINT* getTarget() { return targetPoint; }
	virtual void LinkToTarget(POINT* playerPoint = NULL){
		targetPoint = playerPoint;
	}
};
