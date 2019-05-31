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

class enemyNode :
	public gameNode
{
protected:
	image* img;//이미지
	E_STATE state;
	POINT p;//중점위치
	RECT rc;//충돌용 사각형

	float FrameCheck;
	float speed;
	float gravity;

	int frameX;
	int frameY;

	POINT* targetPoint;
	//AI용 함수위치
	inline bool playerSearch(POINT* playerPoint);
public:
	enemyNode();
	~enemyNode();

	// 중점 기준 배치
	virtual HRESULT init(const char* keyName, POINT point);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void FrameSeter();

	//충돌 확인용
	POINT getPoint() { return p; }
	RECT getRect() { return rc; }

	//플레이어 할당이 해제될 경우 동작을 막을 것
	virtual void AI(POINT* playerPoint = NULL);
	virtual POINT* getTarget() { return targetPoint; }
	virtual void LinkToTarget(POINT* playerPoint = NULL){
		targetPoint = playerPoint;
	}
};
