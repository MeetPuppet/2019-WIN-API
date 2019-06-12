#pragma once

//한 타일의 사이즈는 W X H
#define TILESIZE 80

//y 800 기준 1'2000의 x가 사용되었었음
#define BIGSTAGE 10
#define ONESCENE 1

//타일 갯수(X 12000/80개(150개), Y 800/80(10개))
#define TILEX (WINSIZEX*BIGSTAGE)/TILESIZE
#define TILEY WINSIZEY/TILESIZE

//타일 총 사이즈 (80*45) * (80*10)
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일의 속성
#define ATTR_UNMOVE 0x00000001

//지형에 대한 정의
enum TERRAIN
{
	TR_NONE,
	TR_GROUND,
	TR_LOCK=5
};

//오브젝트 대한 정의
enum OBJECT
{
	OBJ_NONE,
	OBJ_BLOCK,
	OBJ_ITEMBOX,

	OBJ_PIPE,//왼쪽 상단만 지정되도록 할 것
	OBJ_COIN,
	OBJ_AXE,//지형 또는 오브젝트와 연동될 필요가 있음

	OBJ_FLAG_HEAD,
	OBJ_FLAG_BODY,
	OBJ_FLAG_TAIL,

	OBJ_ENEMY_GOOMBA=10,
	OBJ_ENEMY_TURTLE,
	OBJ_BOSS_BOWSER

};

//포지션 (나중에 클래스와 연동키 위함)
enum POS
{//아직 손보지 않음
	//살려는 두겠는데 한번도 안쓰고 뭐에 썼던건지 전혀기억안남
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