#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{

}

HRESULT tank::init()
{
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));

	_speed = 200.0f;

	


	return S_OK;
}

void tank::release()
{

}

void tank::update()	
{
	if ( KEYMANAGER->isStayKeyDown(VK_LEFT) )
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}
	if ( KEYMANAGER->isStayKeyDown(VK_RIGHT) )
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}

}

void tank::render()	
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

//��ũ ������ �Լ�
void tank::tankMove()		
{
	//���Ⱑ �ٽ�!

	//���� Ÿ������ ������ Ÿ������ ������ ��
	//������ ��Ʈ
	RECT rcCollision;

	//Ÿ�� ���⿡ ����ϴ� Ÿ�� �ε���

	//��Ʈ1
	int tileIndex[2];
	int tileX, tileY;

	//������ ��Ʈ�� ��´�
	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	//�� ���⿡ ���� ��ũ �̹��� ��ȯ�� ����ġ
	switch ( _direction )
	{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);

			_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		case TANKDIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);

			_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		case TANKDIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);

			_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);

			_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		
	}

	_rc = rcCollision;

	//��Ʈ�� �̷��� �־���� �����̱� �����δ�
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}


void tank::setTankPosition() 
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_rc.left = _x - _image->getFrameWidth()/2;
	_rc.top = _y - _image->getFrameHeight() / 2;
	_rc.right = _x + _image->getFrameWidth() / 2;
	_rc.bottom = _y + _image->getFrameHeight() / 2;
}