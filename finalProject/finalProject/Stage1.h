#pragma once
#include "gameNode.h"
#include "tileNode.h"
class Stage1 :
	public gameNode
{
private:
	POINT mainLocate;

	tagTile tiles[TILEX*TILEY];
	DWORD attribute[TILEX*TILEY];
public:
	Stage1();
	~Stage1();

	HRESULT init();
	void update();
	void release();
	void render();

	void load();
	void setMainPosition(POINT point) { mainLocate = point; }
};

