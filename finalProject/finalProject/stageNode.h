#pragma once
#include "gameNode.h"
#include "tileNode.h"

class objectManger;

class stageNode :
	public gameNode
{
private:
	POINT mainLocate;

	tagTile tiles[TILEX*TILEY];
	DWORD attribute[TILEX*TILEY];

	objectManger* oManager;
public:
	stageNode();
	~stageNode();

	virtual HRESULT init(const char* map);
	virtual void update();
	virtual void release();
	virtual void render();

	void load(const char* map);

	//��ǥ�� �ٲٴ°� ������ �׸��˾ƺ��� ������ ���߿� ����
	int getEdge0() { return tiles[0].rc.left; }
	int getEdge1() { return tiles[TILEX - 1].rc.right; }
	void moveX(int x) {
		for (int i = 0; i < TILEX*TILEY; ++i) {
			tiles[i].rc.left += x;
			tiles[i].rc.right += x;
		}
	}
	void setMainPosition(POINT point) { }
	void LinkToOBJ(objectManger* om = NULL) 
	{
		oManager = om;
	}

};