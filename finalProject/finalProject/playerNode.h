#pragma once
#include "gameNode.h"//���ӳ�带 ���پ��� �ʿ�

//�̳��� �׳� �������ϰ� ����ϴ� ��
enum PLAYERSTATE {
	/*�ƹ��͵� ����*/IDLE,//���⼭ ���� 0
	/*	 �̵�	 */MOVE,
	/*	 �ɱ�	 */SIT,
	/*	 ����	 */JUMP//����� 3���� ������
};//���� IDLE = 1 �� �������ָ� JUMP�� 4�� ��
//������ 1�� �ö�
//���콺 �÷��ֺ��� ���ذ� ���� ����


//���� ������ ���ӳ���°� ������� ���߿���
//�ϴ� �̰� ���� ���� Ŭ������ ��ġ�Ѵٴ� �͸� �˾Ƶθ� ��
class playerNode :
	public gameNode
{
private:
	int playerNum;

	float time;//������ ����ϴ°� ������ �ļ��� ���ؼ�
	image* image;//�̹����� ����Ͽ� �� �����Ϳ� �����Ŵ
	int x, y;//ĳ������ �߽��� ����
	RECT rc;//�̹��� �׷��� ��ġ, ������ �ϳ����� ũ��� �����ϸ� ����

	float speed;
	float JumpPower;//�����Ŀ� ����(�߷����뿡 �ʿ�)
	bool jumpagain = FALSE;
	bool step = FALSE;
	int HP = 2;		// 1�� ���� ����, 2�� ����, 3�� ��, 0�� �Ǹ� ���
	PLAYERSTATE state;//���°�
	//������ ���������
	int jumpStartY;//������ ���۵� ����(�̰� �׳� ������ ���ؼ� �����)
public:
	playerNode();
	~playerNode();
	//���ӳ��� 3���� �Լ��� �ݵ�� �ۼ��ؾ���
	//HRESULT�� �׳� �� ���Ҵ��� �Ǵ��ϱ� ���ؼ� ����ϴ°�
	HRESULT init(const char* keyName, const char* fileName, int playerNumber);//Ŭ���� �ʱ�ȭ�� �Ҵ�� ���൵ ������ ���ظ� �������� init�� ���⸦ ������

	void update();//�� �״�� ������Ʈ�� ����ϴ� �Լ�

	void render();//�׸��� �׷��ִ� �Լ�
	//�̹� ���ΰ��ӿ��� �̱���(�������� �����ϸ��)���� ���ӳ�忡�� ����������
	//gameNode::init()������ �ȿ��� ������ �ʿ�� ����

	//������Ʈ���� ���� �Լ���
	//�׳� �и��ؼ� �θ� �������ϴ� �и��ص�

	int getX() { return x; }

	//�÷��̾��� ���°��� ���� ������Ʈ ����
	inline void stateUpdate();
	//Ű���� ������ ������ ���ϸ� �������ִ� �Լ�
	inline void keySet();
	inline void keySet2();
	//���ٸ��� ������ �������� �¿츦 �������ִ� �Լ�
	inline void stateFrameUpdate();
};

