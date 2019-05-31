#pragma once

//�� Ÿ���� ������� W X H
#define TILESIZE 80

//y 800 ���� 1'2000�� x�� ���Ǿ�����
#define BIGSTAGE 10
#define ONESCENE 1

//Ÿ�� ����(X 1200/80��(15��)*9, Y 800/80��)
#define TILEX (WINSIZEX*BIGSTAGE)/TILESIZE
#define TILEY WINSIZEY/TILESIZE

//Ÿ�� �� ������ (80*45) * (80*10)
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ�(����Ÿ��) �� ����
#define SAMPLETILEX 5
#define SAMPLETILEY 1

//Ÿ���� �Ӽ�
//��Ʈ�ʵ� ������ �ϳ� �޸� ���� ����
#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP	0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_ICE	0x00000008

//������ ���� ����
enum TERRAIN
{
	TR_NONE,
	TR_GROUND,
	TR_BREAKABLE1,
	TR_BREAKABLE2,
	TR_UNBREAKABLE1,
	TR_UNBREAKABLE2,
	TR_DECORATION
};

//������Ʈ ���� ����
enum OBJECT
{
	OBJ_NONE,
	OBJ_COINBOX,
	OBJ_PIPE,
	OBJ_COIN,
	OBJ_AXE,

	OBJ_SHELL
};

//������ (���߿� Ŭ������ ����Ű ����)
enum POS
{//���� �պ��� ����
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
		terrainFrameX = 0;
		objFrameX = 0;
		objFrameX = 0;
	}
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};