#include "stdafx.h"//�Ŵ����� ���⿡ �� ���������� �ʿ���
#include "playerNode.h"
//������ �ſ� �߿���
//�׸��� �Ӽ����� �������߾��ٶ�
//�������յ� ��Ƽ����Ʈ�� ���߾� ��� ��ĥ�� ����

#define WIDTH 540  //�̹��� ���α���
#define HEIGHT 360 //�̹��� ���α���

#define SPEED 300
#define JUMPSPEED 6
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

HRESULT playerNode::init(const char* keyName, const char* fileName , int playerNumber)
{			//�������̹��� �����			ȣ���	 ������ġ  ����	  ����
	image = IMAGEMANAGER->addFrameImage(keyName, fileName, WIDTH, HEIGHT,
										7, 2, //������X,Y����
										true, //����� ���� �ִ°� ?
										RGB(255,255,255));//���� ���� RGB��
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
	playerNum = playerNumber;
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
	if (playerNum == 1) {
		//Ű�� ���� ����
		keySet();
	}
	else {
		//Ű�� ���� ����
		keySet2();
	}
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

	//�ð���¿�
	//�����, ������ ��忡 ���� ����� �ٸ�
	TIMEMANAGER->render(getMemDC());
	//�̵��ӵ� ���뿡 ������ �־���� ������
	
	//���밪�� �̻��� ���϶� �̷��� ����ؼ� ���� ����
	char str[256];
	sprintf_s(str, "SPEED * ElapsedTime : %f", speed);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
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
		speed = SPEED * TIMEMANAGER->getElapsedTime();

		//������ �̳Ĵ� ��
		if (image->getFrameY() == 0) {
			x += speed;
			//�¿� �̼��� �޶��̴µ� �и� �°� ���ư�
		}
		else if (image->getFrameY() == 1) {
			x -= speed;
		}
		break;
	case SIT:
		break;
	case JUMP:
		//������ ��ŭ ���� �ö󰣴�.
		if (250 < y && y < 300) {
			jumpagain = TRUE;
		}
		y -= JumpPower;// JUMPSPEED�� �ʱ�ȭ��
		//�ð� �ݿ��� ���� �ǽð����� ���ֱ�
		JumpPower -= JUMPSPEED* 1.8 * TIMEMANAGER->getElapsedTime();

		//�̰� �浹�� �� �ƹ��� ���൵ �ȴ�.
		//���� ������ �������� �޾Ƽ� �������.
		if (jumpStartY < y) {
			y = jumpStartY;
			image->setFrameX(0);
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
	//if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
	//	//�׳� �ѹ� �ֺ�
	//}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && state != JUMP) {
		image->setFrameX(6);
		//state = SIT;
		//�׳� �ѹ� �ֺ�
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && state != JUMP) {
		image->setFrameX(0);
		//state = SIT;
		//�׳� �ѹ� �ֺ�
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(1);//�������� ������Y ����(�̹��� �Ʒ��κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && state == MOVE
		&& image->getFrameY() == 1) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(0);//�������� ������Y ����(�̹��� ���κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && state == MOVE
		&& image->getFrameY() == 0) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x -= speed;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && state != JUMP) {//�������°� �ƴϰ� zŰ�� ������
		state = JUMP;
		image->setFrameX(5);
		//���� ���������� �޾Ƽ�
		jumpStartY = y;
		//���߿� �ٽ� ���� ������ ����

		//���� �ӵ� ����
		JumpPower = JUMPSPEED;
	}
	if (state == JUMP && jumpagain == TRUE) {
		image->setFrameX(1);
		JumpPower = JUMPSPEED;
		image->setFrameX(5);
		jumpagain = FALSE;
	}
}

void playerNode::keySet2()
{
	//�̹������� ����(Y)�� ������
	//������ �Ʒ���(1), �������� ����(0)�̴� �̴�.
	//�¿�(X)�� �Ʒ��Լ� stateUpdate()�� �����ٶ�

	//�����¿� ����Ű
	//if (KEYMANAGER->isOnceKeyDown('W')) {
	//	//�׳� �ѹ� �ֺ�
	//}
	if (KEYMANAGER->isOnceKeyDown('S') && state != JUMP) {
		image->setFrameX(6);
		//state = SIT;
		//�׳� �ѹ� �ֺ�
	}
	else if (KEYMANAGER->isOnceKeyUp('S') && state != JUMP) {
		image->setFrameX(0);
		//state = SIT;
		//�׳� �ѹ� �ֺ�
	}
	if (KEYMANAGER->isOnceKeyDown('A') && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(1);//�������� ������Y ����(�̹��� �Ʒ��κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp('A') && state == MOVE
		&& image->getFrameY() == 1) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown('D') && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(0);//�������� ������Y ����(�̹��� ���κ�)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp('D') && state == MOVE
		&& image->getFrameY() == 0) {
		image->setFrameX(0);//�̰� stateFrameUpdate()���� ������ ����
		state = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}

	if (KEYMANAGER->isStayKeyDown('S') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}
	if (KEYMANAGER->isStayKeyDown('A') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x -= speed;
	}

	if (KEYMANAGER->isOnceKeyDown('W') && state != JUMP) {//�������°� �ƴϰ� zŰ�� ������
		state = JUMP;
		image->setFrameX(5);
		//���� ���������� �޾Ƽ�
		jumpStartY = y;
		//���߿� �ٽ� ���� ������ ����

		//���� �ӵ� ����
		JumpPower = JUMPSPEED;
	}
	if (state == JUMP && jumpagain == TRUE) {
		image->setFrameX(1);
		JumpPower = JUMPSPEED;
		image->setFrameX(5);
		jumpagain = FALSE;
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
		//image->setFrameX(0);//Ű ���� �ᵵ ��
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