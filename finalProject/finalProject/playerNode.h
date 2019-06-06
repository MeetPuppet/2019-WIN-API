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
	//���ӳ��� 3���� �Լ��� �ݵ�� �ۼ��ؾ���
	//HRESULT�� �׳� �� ���Ҵ��� �Ǵ��ϱ� ���ؼ� ����ϴ°�
	virtual HRESULT init(image* IMG);//Ŭ���� �ʱ�ȭ�� �Ҵ�� ���൵ ������ ���ظ� �������� init�� ���⸦ ������

	virtual void update();//�� �״�� ������Ʈ�� ����ϴ� �Լ�

	virtual void render();//�׸��� �׷��ִ� �Լ�
	//�̹� ���ΰ��ӿ��� �̱���(�������� �����ϸ��)���� ���ӳ�忡�� ����������
	//gameNode::init()������ �ȿ��� ������ �ʿ�� ����

	int getX() { return point.x; }
	Point getPoint() { return point; }
	float getSpeed() { return speed; }
	void moveX(int X) 
	{ 
		point.x += X;
	}

	//������Ʈ���� ���� �Լ���
	//�׳� �и��ؼ� �θ� �������ϴ� �и��ص�

	//�÷��̾��� ���°��� ���� ������Ʈ ����
	inline void stateUpdate();
	//�ൿ���� Ű�� ��ġ�� ��
	virtual void keySet();
	//���ٸ��� ������ �������� �¿츦 �������ִ� �Լ�
	inline void stateFrameUpdate();
};

