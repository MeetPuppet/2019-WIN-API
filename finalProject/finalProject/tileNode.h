#pragma once

//한 타일의 사이즈는 W X H
#define TILESIZE 80

//y 800 기준 1'2000의 x가 사용되었었음
#define BIGSTAGE 10
#define ONESCENE 1

//타일 갯수(X 1200/80개(15개)*9, Y 800/80개)
#define TILEX (WINSIZEX*BIGSTAGE)/TILESIZE
#define TILEY WINSIZEY/TILESIZE

//타일 총 사이즈 (80*45) * (80*10)
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋(샘플타일) 의 갯수
#define SAMPLETILEX 5
#define SAMPLETILEY 1

//타일의 속성
//비트필드 느리긴 하나 메모리 관리 따봉
#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP	0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_ICE	0x00000008

//지형에 대한 정의
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

//오브젝트 대한 정의
enum OBJECT
{
	OBJ_NONE,
	OBJ_COINBOX,
	OBJ_PIPE,
	OBJ_COIN,
	OBJ_AXE,

	OBJ_SHELL
};

//포지션 (나중에 클래스와 연동키 위함)
enum POS
{//아직 손보지 않음
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