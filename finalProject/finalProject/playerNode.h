#pragma once
#include "gameNode.h"

enum PLAYERSTATE {
	PS_IDLE,
	PS_MOVE,
	PS_BREAK,
	PS_JUMP,
	PS_SIT,
	PS_DEAD
};

enum PLAYERMOD {
	PM_SMALL,
	PM_BIG,
	PM_FIRE
};

class objectManger;
class stageNode;

class playerNode :
	public gameNode
{
protected:
	image* img;
	
	RECT rc;
	RECT foot;
	Point point;
	RECT CollisionRC;

	RECT checkPos[2];
	int tileIndex[2] = { 0 };

	int IFS;
	float IFF;

	float time;
	float speed;
	float jumpPower;

	PLAYERSTATE state;
	PLAYERMOD mode;

	int frameX;
	int frameY;
	float frameCount;

	objectManger* om;
	stageNode* stage;
public:
	playerNode();
	~playerNode();
	//���ӳ��� 3���� �Լ��� �ݵ�� �ۼ��ؾ���
	//HRESULT�� �׳� �� ���Ҵ��� �Ǵ��ϱ� ���ؼ� ����ϴ°�
	virtual HRESULT init(image* IMG, Point p);//Ŭ���� �ʱ�ȭ�� �Ҵ�� ���൵ ������ ���ظ� �������� init�� ���⸦ ������

	virtual void update();//�� �״�� ������Ʈ�� ����ϴ� �Լ�

	virtual void render();//�׸��� �׷��ִ� �Լ�
	//�̹� ���ΰ��ӿ��� �̱���(�������� �����ϸ��)���� ���ӳ�忡�� ����������
	//gameNode::init()������ �ȿ��� ������ �ʿ�� ����

	int getX() { return point.x; }
	Point getPoint() { return point; }
	float getSpeed() { return speed; }
	void moveX(float X) 
	{ 
		point.x += X;
	}
	void LinkToOM(objectManger* OM) { om = OM; }
	void LinkToStage(stageNode* s) { stage = s; }

	virtual void keySet();
	void gravityChecker(bool isFall);
	bool moveChecker(bool isRight);
	void footCheck();

	void powerUp();
	void jumpUp();
	void finishem();
};

