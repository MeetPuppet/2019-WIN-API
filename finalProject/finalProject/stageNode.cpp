#include "stdafx.h"
#include "stageNode.h"
#include "objectManger.h"


#define MAX TILEX*TILEY

stageNode::stageNode()
{
	mainLocate = { WINSIZEX / 2,0 };
	oManager = NULL;
}


stageNode::~stageNode()
{
}


HRESULT stageNode::init(const char* map)
{
	IMAGEMANAGER->addFrameImage("Tiles", "image/tile/Tiles.bmp", 480, 160, 6, 2, true, RGB(255, 0, 255));

	load(map);
	for (int i = 0; i < TILEY; ++i) {
		for (int j = 0; j < TILEX; ++j) {
			tiles[(i*TILEX) + j].rc = { j*TILESIZE,i*TILESIZE
									,j*TILESIZE + TILESIZE
									,i*TILESIZE + TILESIZE 
			};
		}
	}
	return S_OK;
}

void stageNode::update()
{
	//if (tiles[0].rc.left < -10 && mainLocate.x < 200) {
	//	for (int i = 0; i < MAX; ++i) {
	//		tiles[i].rc.left += 10;
	//		tiles[i].rc.right += 10;
	//	}
	//}
	//else if (tiles[TILEX - 1].rc.right > WINSIZEX + 10 && mainLocate.x > 1000) {
	//	for (int i = 0; i < MAX; ++i) {
	//		tiles[i].rc.left -= 10;
	//		tiles[i].rc.right -= 10;
	//	}
	//}

}

void stageNode::release()
{
}

void stageNode::render()
{
	for (int i = 0; i < MAX; ++i) {
		if (tiles[i].rc.right > 0 && tiles[i].rc.left < 1200)
			IMAGEMANAGER->frameRender("Tiles", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				tiles[i].terrainFrameX, tiles[i].terrainFrameY);
	}
}

void stageNode::load(const char* map)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(map, GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, tiles, sizeof(tagTile)*MAX, &read, NULL);

	CloseHandle(file);

	memset(attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	memset(pos, 0, sizeof(int) * 2);

	//��Ʈ����Ʈ ������
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (tiles[i].terrain == TR_GROUND) attribute[i] |= ATTR_UNMOVE;
		if (tiles[i].obj == OBJ_ITEMBOX) attribute[i] |= ATTR_UNMOVE;

		//�̰ź��ʹ� ���߿� ������� �ִ°�
		if (tiles[i].obj == OBJ_BLOCK) attribute[i] |= ATTR_UNMOVE;
		// ������Ʈ == NONE  �ƴϸ� �� �־��ּ��� �P�P�P
	}

	//�� �պ��ʹ� ������Ʈ ������
	//�ݵ�� �Ŵ����� �����ص� ��
	if (oManager == NULL) 
		return;

	for (int i = 0; i < MAX; ++i) {
		if (tiles[i].objFrameX == 0) {
			continue;
		}
		//�����ۺ�
		if (tiles[i].objFrameX == 2) {
			oManager->setItemBox(tiles[i].rc, tiles[i].objFrameX);
		}
		//�׳� ��
		else if (tiles[i].objFrameX == 3) {
			oManager->setBlock(tiles[i].rc, 0, 0);
		}
		//���� ��
		else if (tiles[i].objFrameX == 4) {
			oManager->setItemBox(tiles[i].rc, tiles[i].objFrameX);
		}
		//UNBREAK
		else if (tiles[i].objFrameX == 5) {
			oManager->setBlock(tiles[i].rc, 1, 0);
		}
		//����
		else if (tiles[i].objFrameX == 9) {
			oManager->setCoin(tiles[i].rc);
		}
	}
}