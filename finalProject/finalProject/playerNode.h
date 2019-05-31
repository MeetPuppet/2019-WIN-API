#pragma once
#include "gameNode.h"//게임노드를 갖다쓰니 필요

//이넘은 그냥 보기편하고 사용하는 것
enum PLAYERSTATE {
	/*아무것도 안함*/IDLE,//여기서 부터 0
	/*	 이동	 */MOVE,
	/*	 앉기	 */SIT,
	/*	 점프	 */JUMP//여기는 3으로 설정됨
};//만약 IDLE = 1 로 설정해주면 JUMP는 4가 됨
//무조건 1씩 올라감
//마우스 올려둬보면 이해가 편할 것임


//지금 당장은 게임노드라는게 어떤건지는 안중요함
//일단 이게 가장 안쪽 클래스에 위치한다는 것만 알아두면 됨
class playerNode :
	public gameNode
{
private:
	int playerNum;

	float time;//원래는 계산하는게 맞지만 꼼수를 위해서
	image* image;//이미지를 등록하여 이 포인터에 연결시킴
	int x, y;//캐릭터의 중심점 설정
	RECT rc;//이미지 그려둘 위치, 프레임 하나당의 크기로 설정하면 편함

	float speed;
	float JumpPower;//점프파워 설정(중력적용에 필요)
	bool jumpagain = FALSE;
	bool step = FALSE;
	int HP = 2;		// 1이 작은 상태, 2가 버섯, 3이 꽃, 0이 되면 사망
	PLAYERSTATE state;//상태값
	//지금은 여기까지만
	int jumpStartY;//점프가 시작된 지점(이건 그냥 설명을 위해서 만든거)
public:
	playerNode();
	~playerNode();
	//게임노드는 3개의 함수를 반드시 작성해야함
	//HRESULT는 그냥 잘 돌았는지 판단하기 위해서 사용하는것
	HRESULT init(const char* keyName, const char* fileName, int playerNumber);//클래스 초기화용 할당시 해줘도 좋지만 이해를 돕기위해 init을 쓰기를 권장함

	void update();//말 그대로 업데이트를 담당하는 함수

	void render();//그림을 그려주는 함수
	//이미 메인게임에서 싱글톤(전역으로 이해하면됨)으로 게임노드에서 돌고있으니
	//gameNode::init()같은걸 안에서 돌려줄 필요는 없음

	//업데이트에서 돌릴 함수들
	//그냥 분리해서 두면 보기편하니 분리해둠

	int getX() { return x; }

	//플레이어의 상태값에 따라서 업데이트 진행
	inline void stateUpdate();
	//키셋을 포함한 프레임 상하를 관리해주는 함수
	inline void keySet();
	inline void keySet2();
	//별다른일 없으면 프레임의 좌우를 관리해주는 함수
	inline void stateFrameUpdate();
};

