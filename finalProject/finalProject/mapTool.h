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

	//���� �Ӽ����� �־�ξ����͸� ��ﳲ
	//������ ������ �𸣰���
	DWORD attribute[TILEX*TILEY];

	//�浹�Ǵܿ�?
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

