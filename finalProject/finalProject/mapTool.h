#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool :
	public gameNode
{
private:
	int frameIndex;
	tagTile tiles[TILEX*TILEY];

	//���� �Ӽ����� �־�ξ����͸� ��ﳲ
	//������ ������ �𸣰���
	DWORD attribute[TILEX*TILEY];

	//�浹�Ǵܿ�?
	int _pos[2];

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void update();
	void render();
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	void save();
	void load();
};

