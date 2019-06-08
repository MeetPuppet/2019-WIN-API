#pragma once
#include "enemyNode.h"
class firanhaFlower :
	public enemyNode
{
private:
	int move;
	bool stop;
public:
	firanhaFlower();
	~firanhaFlower();

	// 중점 기준 배치
	HRESULT init(int x, int y);
	void release();
	void update();
	void render();
	void FrameSeter() override;

	//플레이어 할당이 해제될 경우 동작을 막을 것
	void AI(POINT* playerPoint = NULL);

	POINT* getTarget() { return enemyNode::getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}
};

