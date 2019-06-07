#pragma once
#include "gameNode.h"
#include "tileNode.h"

#include "Mario.h"

class mapTool :
	public gameNode
{
private:
	int frameIndex;
	int mode;

	Mario mario;

	tagTile tiles[TILEX*TILEY];

	//기억상 속성값을 넣어두었던것만 기억남
	//실제로 쓴지는 모르겠음
	DWORD attribute[TILEX*TILEY];

	//충돌판단용?
	int pos[2];

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void update();
	void render();
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	SWITCHER whatSet() override { return MAPTOOL; }
	void save();
	void load();
};

