#pragma once
#include "enemyNode.h"
class Goomba :
	public enemyNode
{
public:
	Goomba();
	~Goomba();

	// 중점 기준 배치
	HRESULT init(Point point);
	void release();
	void update();
	void render();
	void FrameSeter() override;

	//플레이어 할당이 해제될 경우 동작을 막을 것
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

