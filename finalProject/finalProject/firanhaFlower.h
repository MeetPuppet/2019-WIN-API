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

	// ���� ���� ��ġ
	HRESULT init(int x, int y);
	void release();
	void update();
	void render();
	void FrameSeter() override;

	//�÷��̾� �Ҵ��� ������ ��� ������ ���� ��
	void AI(POINT* playerPoint = NULL);

	POINT* getTarget() { return enemyNode::getTarget(); }
	void LinkToTarget(POINT* playerPoint = NULL) {
		targetPoint = playerPoint;
	}
};

