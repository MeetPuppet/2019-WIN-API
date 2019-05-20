#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"
//������ �ſ� �߿���
//�׸��� �Ӽ����� �������߾��ٶ�
//�������յ� ��Ƽ����Ʈ�� ���߾� ��� ��ĥ�� ����

#define WIDTH 540  //�̹��� ���α���
#define HEIGHT 360 //�̹��� ���α���

#define SPEED 200
#define JUMPSPEED 5
#define FRAMETIME 0.2

playerNode::playerNode()
{//�������� �������� �𸣴� �����ص�
	image = NULL;
	x = y = 0;
	rc = { 0,0,0,0 };
	speed = 0;
	JumpPower = 0;
	state = IDLE;
	time = 0;

	jumpStartY = 0;
}


playerNode::~playerNode()
{
}

HRESULT playerNode::init(const char* keyName, const char* fileName )
{			//�������̹��� �����			ȣ���	 ������ġ  ����	  ����
	image = IMAGEMANAGER->addFrameImage("mario","image/player/fireSuit.bmp", WIDTH, HEIGHT,
										7, 2, //������X,Y����
										true, //����� ���� �ִ°� ?
										RGB(255,0,255));//���� ���� RGB��
	//���� �Լ��� ���� �̹����� map�̶�� STL�� �����ϰ� �� ��ġ�� �ּҰ��� ������
	//�׷��� image�� ������ ����ü+Ŭ������ ���� ���� ������ ����Ű�� ��
	//ȣ����� �����ϴ� ������ IMAGEMANAGER->findImage(keyName) �� ã�Ƴ��� ���ؼ���(����)
	
	//���� ����� �̹����� little�� �ƴϸ� ������ �Ȱ����� ������ �̷��� ������
	//���� little�� �ѹ� ����� ���� ������ ����
	
	x, y;//ĳ������ �߽��� ����

	//�� ������ �߰�
	x = WINSIZEX / 2;//�̹� �����ص� ������ ������ define��
	y = WINSIZEY / 2;//�̹� �����ص� ������ ������ define��
	 //�����ص� ��ũ��   �߾����� ����  ����
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());
							  //�̹������� �����ص� x,y �� ������ ���μ��α���

	state = IDLE;//�������� �ʴ´ٴ� ��

	JumpPower = 0;//�����Ŀ� ����(�߷����뿡 �ʿ�)
	//��� �����ϴ� ���� �۵��ϰ� ��

	time = 0;

	//�ߵ������ϱ�
	return S_OK;
	//���� void ��� ������ �Ǵ°�
}

void playerNode::update() 
{
	//�̰� �����ϸ� ������ �ǾƷ� �־����
	//�׳� �����ϴ� ��찡 ���Ƽ� �׷��� �����ϰ�����
	//�̹����� �����ġ�� RECT������ ������ ���� ����
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());

	//���� ���� ������Ʈ ������ ���� �������
	//���°����� ����
	stateUpdate();
	//Ű�� ���� ����
	keySet();
	//������ ����
	stateFrameUpdate();
}

void playerNode::render() 
{
	//     �����ӷ��� �긦��ߺ��簡�� 
	image->frameRender(getMemDC(), 
		x, y,//xy��
		image->getFrameX(), //image���� �����ǰ� �ִ� �����Ӱ���
		image->getFrameY());//
}
void playerNode::stateUpdate() {
	//�ð��� ���� ������ ����.
	//��ǻ�͸��� ������ �ٸ��� ������ �ð����� ���� ����ϸ� ��𼭵� ���� ������ �ϰԵǱ� ����
	//�ٵ� ���� �� ����

	//�̷��� ����ġ�� if�� ��� ������
	//�׳� ���� ���ϰ� ��������ؼ� ����ġ�� ����
	float elapsedTime;
	switch (state)
	{
	case IDLE://�Ͽ�����
		break;
	case MOVE:						//�ð� ������ 1������ float������ ������
		elapsedTime = TIMEMANAGER->getElapsedTime();
		speed = SPEED * elapsedTime;

		//������ �̳Ĵ� ��
		if (image->getFrameY() == 0) {
			x += speed;
		}
		else if (image->getFrameY() == 1) {
			x -= speed;
		}
		//������ �ľ����� ���ϰ� �ִµ� �¿� �ӵ��� �ٸ�
		break;
	case SIT:
		break;
	case JUMP:
		//������ ��ŭ ���� �ö󰣴�.
		y -= JumpPower;
		//�ð� �ݿ��� ���� �ǽð����� ���ֱ�
		JumpPower -= JUMPSPEED * TIMEMANAGER->getElapsedTime();

		//�̰� �浹�� �� �ƹ��� ���൵ �ȴ�.
		//���� ������ �������� �޾Ƽ� �������.
		if (jumpStartY < y) {
			y = jumpStartY;
			state = IDLE;
		}
		break;
	}
}
//Ű���� ������ ������ ���ϸ� �������ִ� �Լ�
void playerNode::keySet()
{
	//�̹������� ����(Y)�� ������
	//������ �Ʒ���(1), �������� ����(0)�̴� �̴�.
	//�¿�(X)�� �Ʒ��Լ� stateUpdate()�� �����ٶ�

	//�����¿� ����Ű
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		//�׳� �ѹ� �ֺ�
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		//�׳� �ѹ� �ֺ�
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		image->setFrameX(1);
		image->setFrameY(1);//�������� ������Y ����(�̹��� �Ʒ��κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		image->setFrameX(1);
		image->setFrameY(0);//�������� ������Y ����(�̹��� ���κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown('Z')) {//zŰ�� ������
		state = JUMP;
		image->setFrameX(5);
		//���� ���������� �޾Ƽ�
		jumpStartY = y;
		//���߿� �ٽ� ���� ������ ����

		//���� �ӵ� ����
		JumpPower = JUMPSPEED;
	}
}

//���ٸ��� ������ �������� �¿츦 �������ִ� �Լ�
void playerNode::stateFrameUpdate()
{
	//�̹����� �ѹ����� �˰�����
	//�¿�(X)�� ���� 0���� �������ִ°�(IDLE)
	// 1,2,3���� �̵�(MOVE)
	// 5���� ���� (JUMP)
	// 6���� �ɱ� (SIT)
	// ������ �Ⱦ��� 4���� �Ÿ���
	//����(Y)�� ���Լ� keySet()�� �����ٶ�

	switch (state)
	{
	case IDLE://IDLE �����϶��� ������Ʈ
		    //�̹����� ������ ��ġ�� 0������
		image->setFrameX(0);//Ű ���� �ᵵ ��
		break;
	case MOVE://���ϻ���
		//�ð��� ��� ������(�ļ�)
		time += TIMEMANAGER->getElapsedTime();
		//������ X�� 0���� ũ�� ������ X�� 3���� ������			 0.2�ʰ� ������
		if (image->getFrameX() > 0 && image->getFrameX() < 3 && time > FRAMETIME) {
			//�̹����� ������ ��ġ�� ���� ������+1�� ����
			image->setFrameX(image->getFrameX() + 1);
			time -= FRAMETIME;
		}
		//�� ���ǰ� �ȸ´µ� 3�� �̹��� �϶�
		else if (image->getFrameX() == 3 && time > FRAMETIME){
			//�ٽ� 1������ ������
			image->setFrameX(1);
			time -= FRAMETIME;
		}
		break;
		/*
		�� �̻� �ڼ��� ������ �����Ѵ�.
		*/
	case SIT:
		break;
	case JUMP:
		break;
	default:
		//������ ������ ��
		break;
	}
}