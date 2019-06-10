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

class stageNode;

class enemyNode :
	public gameNode
{
protected:
	image* img;//�̹���
	E_STATE state;
	Point p;//������ġ
	RECT rc;//�浹�� �簢��
	stageNode* stage;

	float FrameCheck;
	float speed;
	float gravity;

	int frameX;
	int frameY;
	RECT checkPos[2];
	int tileIndex[2];
	float time;
	POINT* targetPoint;
	//AI�� �Լ���ġ
	inline bool playerSearch(POINT* playerPoint);
public:
	enemyNode();
	~enemyNode();

	// ���� ���� ��ġ
	virtual HRESULT init(const char* keyName, Point point);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void FrameSeter();
	void moveChecker(bool isRight);

	//�浹 Ȯ�ο�
	Point getPoint() { return p; }
	RECT getRect() { return rc; }

	//��ǥ�� �ٲٴ°� ������ �׸��˾ƺ��� ������ ���߿� ����
	void moveX(int x) { p.x += x; }

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	 void AI(POINT* playerPoint = NULL);
	 POINT* getTarget() { return targetPoint; }
	 void LinkToTarget(POINT* playerPoint = NULL){
		targetPoint = playerPoint;
	}
	 void LinkToStage(stageNode* s) { stage = s; }
};
