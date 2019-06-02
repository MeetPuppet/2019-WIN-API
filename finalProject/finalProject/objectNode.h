#pragma once
#include "gameNode.h"
class objectNode :
	public gameNode
{
protected:
	image* img;
	Point p;
	RECT rc;

	int frameX;
	int frameY;
public:
	objectNode();
	~objectNode();
	virtual HRESULT init(const char* key, int x, int y, int sizeX, int sizeY);
	virtual void update();
	virtual void render();
	
	//��ǥ�� �ٲٴ°� ������ �׸��˾ƺ��� ������ ���߿� ����
	void moveX(int x) { p.x += x; }
	Point getPoint() { return p; }
	RECT getRect() { return rc; }
};

