#pragma once
#include "enemyNode.h"
class Goomba :
	public enemyNode
{
public:
	Goomba();
	~Goomba();

	// ���� ���� ��ġ
	HRESULT init(Point point);
	void release();
	void update();
	void render();
	void FrameSeter() override;

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	void AI(POINT* playerPoint = NULL);
	void makeStateDead()
	{
		frameX = 2;
		state = DEAD;
	}

	POINT* getTarget() { return enemyNode::getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}
};

