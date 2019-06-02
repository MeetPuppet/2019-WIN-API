#include "stdafx.h"
#include "Stage1.h"

#define MAX TILEX*TILEY

Stage1::Stage1()
{
	mainLocate={ WINSIZEX / 2,0 };
}


Stage1::~Stage1()
{
}


HRESULT Stage1::init()
{
	IMAGEMANAGER->addFrameImage("Tiles", "image/tile/Tiles.bmp", 480, 160, 6, 2, true, RGB(255, 0, 255));
	
	load();
	for (int i = 0; i < TILEY; ++i) {
		for (int j = 0; j < TILEX; ++j) {
			tiles[(i*TILEX) + j].rc = { j*TILESIZE,i*TILESIZE
									,j*TILESIZE + TILESIZE
									,i*TILESIZE + TILESIZE };

		}
	}
	return S_OK;
}

void Stage1::update()
{
	if (tiles[0].rc.left < -10 && mainLocate.x < 200) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left += 10;
			tiles[i].rc.right += 10;
		}
	}
	else if (tiles[TILEX - 1].rc.right > WINSIZEX + 10 && mainLocate.x > 1000) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left -= 10;
			tiles[i].rc.right -= 10;
		}
	}

}

void Stage1::release()
{
}

void Stage1::render() 
{
	for (int i = 0; i < MAX; ++i) {
		if (tiles[i].rc.right > 0 && tiles[i].rc.left < 1200)
			IMAGEMANAGER->frameRender("Tiles", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				tiles[i].terrainFrameX, tiles[i].terrainFrameY);
	}
}

void Stage1::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("map/save1.map", GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, tiles, sizeof(tagTile)*MAX, &read, NULL);

	CloseHandle(file);
}