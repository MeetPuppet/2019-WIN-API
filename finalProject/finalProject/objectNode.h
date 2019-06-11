#pragma once
#include "gameNode.h"

class playerNode;

class objectNode :
	public gameNode
{
protected:
	image* img;
	Point p;
	RECT rc;

	int frameX;
	int frameY;

	playerNode* player1;
	playerNode* player2;
public:
	objectNode();
	~objectNode();
	virtual HRESULT init(const char* key, int x, int y, int sizeX, int sizeY);
	virtual void update();
	virtual void render();
	
	//좌표를 바꾸는게 맞지만 그만알아보고 싶으니 나중에 하자
	void moveX(int x) { p.x += x; }
	Point getPoint() { return p; }
	RECT getRect() { return rc; }

	void LinkToP1(playerNode* p1) { player1 = p1; }
	void LinkToP2(playerNode* p2) { player2 = p2; }
};

