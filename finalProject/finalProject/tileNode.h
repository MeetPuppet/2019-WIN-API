#pragma once

//�� Ÿ���� ������� W X H
#define TILESIZE 80

//y 800 ���� 1'2000�� x�� ���Ǿ�����
#define BIGSTAGE 10
#define ONESCENE 1

//Ÿ�� ����(X 12000/80��(150��), Y 800/80(10��))
#define TILEX (WINSIZEX*BIGSTAGE)/TILESIZE
#define TILEY WINSIZEY/TILESIZE

//Ÿ�� �� ������ (80*45) * (80*10)
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ���� �Ӽ�
#define ATTR_UNMOVE 0x00000001

//������ ���� ����
enum TERRAIN
{
	TR_NONE,
	TR_GROUND,
	TR_LOCK=5
};

//������Ʈ ���� ����
enum OBJECT
{
	OBJ_NONE,
	OBJ_BLOCK,
	OBJ_ITEMBOX,

	OBJ_PIPE,//���� ��ܸ� �����ǵ��� �� ��
	OBJ_COIN,
	OBJ_AXE,//���� �Ǵ� ������Ʈ�� ������ �ʿ䰡 ����

	OBJ_FLAG_HEAD,
	OBJ_FLAG_BODY,
	OBJ_FLAG_TAIL,

	OBJ_ENEMY_GOOMBA=10,
	OBJ_ENEMY_TURTLE,
	OBJ_BOSS_BOWSER

};

//������ (���߿� Ŭ������ ����Ű ����)
enum POS
{//���� �պ��� ����
	//����� �ΰڴµ� �ѹ��� �Ⱦ��� ���� ������� �������ȳ�
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT	obj;
	RECT	rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	tagTile() {
		terrain = TR_NONE;
		obj = OBJ_NONE;
		rc = { 0,0,0,0 };
		terrainFrameX = 0;
		terrainFrameY = 0;
		objFrameX = 0;
		objFrameY = 0;
	}
};

struct tagCurrentTile
{
	int x;
	int y;
};