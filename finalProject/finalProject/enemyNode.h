#pragma once
#include "gameNode.h"

#define ENEMY_FRAME_SPEEDER 1
//상태값
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
	image* img;//이미지
	E_STATE state;
	Point p;//중점위치
	RECT rc;//충돌용 사각형
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
	//AI용 함수위치
	inline bool playerSearch(POINT* playerPoint);
public:
	enemyNode();
	~enemyNode();

	// 중점 기준 배치
	virtual HRESULT init(const char* keyName, Point point);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void FrameSeter();
	void moveChecker(bool isRight);

	//충돌 확인용
	Point getPoint() { return p; }
	RECT getRect() { return rc; }

	//좌표를 바꾸는게 맞지만 그만알아보고 싶으니 나중에 하자
	void moveX(int x) { p.x += x; }

	//플레이어 할당이 해제될 경우 동작을 막을 것
	 void AI(POINT* playerPoint = NULL);
	 POINT* getTarget() { return targetPoint; }
	 void LinkToTarget(POINT* playerPoint = NULL){
		targetPoint = playerPoint;
	}
	 void LinkToStage(stageNode* s) { stage = s; }
};
