#pragma once
#include "gameNode.h"

enum PLAYERSTATE {
	PR_IDLE,
	PL_IDLE,

	PR_MOVE,
	PL_MOVE,

	PR_JUMP,
	PL_JUMP,

	PR_SIT,
	PL_SIT
};

enum PLAYERMOD {
	SMALL,
	BIG,
	FIRE
};


class playerNode :
	public gameNode
{
private:
	image* img;
	
	RECT rc;
	Point point;

	float speed;
	float jumpPower;

	PLAYERSTATE state;
	PLAYERMOD mode;

	int frameX;
	int frameY;
	float frameCount;
public:
	playerNode();
	~playerNode();
	//게임노드는 3개의 함수를 반드시 작성해야함
	//HRESULT는 그냥 잘 돌았는지 판단하기 위해서 사용하는것
	virtual HRESULT init(image* IMG);//클래스 초기화용 할당시 해줘도 좋지만 이해를 돕기위해 init을 쓰기를 권장함

	virtual void update();//말 그대로 업데이트를 담당하는 함수

	virtual void render();//그림을 그려주는 함수
	//이미 메인게임에서 싱글톤(전역으로 이해하면됨)으로 게임노드에서 돌고있으니
	//gameNode::init()같은걸 안에서 돌려줄 필요는 없음

	int getX() { return point.x; }
	Point getPoint() { return point; }
	float getSpeed() { return speed; }
	void moveX(int X) 
	{ 
		point.x += X;
	}

	//업데이트에서 돌릴 함수들
	//그냥 분리해서 두면 보기편하니 분리해둠

	//플레이어의 상태값에 따라서 업데이트 진행
	inline void stateUpdate();
	//행동값당 키를 배치할 것
	virtual void keySet();
	//별다른일 없으면 프레임의 좌우를 관리해주는 함수
	inline void stateFrameUpdate();
};

