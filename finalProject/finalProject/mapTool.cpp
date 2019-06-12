#include "stdafx.h"
#include "mapTool.h"

#define MAX TILEX*TILEY


mapTool::mapTool()
{
	mode = 0;
}


mapTool::~mapTool()
{
	gameNode::release();
}

HRESULT mapTool::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addFrameImage("Tiles", "image/tile/Tiles.bmp", 480, 160, 6, 2, true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("Coin", "image/object/coin.bmp", 240, 70, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Goomba", "image/enemy/goomba.bmp", 240, 80,
		3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenTurtle", "image/enemy/greenTurtle.bmp", 160, 240,
		2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bowser", "image/bowser/bowser.bmp", 640, 320,
		4, 2, true, RGB(255, 0, 255));
	//load();

	for (int i = 0; i < TILEY; ++i) {
		for (int j = 0; j < TILEX; ++j) {
			tiles[(i*TILEX) + j].rc = { j*TILESIZE,i*TILESIZE
									,j*TILESIZE + TILESIZE
									,i*TILESIZE + TILESIZE };
		}
	}for (int i = 1200; i < TILEY*TILEX; ++i) {
		tiles[i].terrain = TR_GROUND;
		tiles[i].terrainFrameX = 1;
		tiles[i].terrainFrameY = 0;
	}
	frameIndex = 0;

	return S_OK;
}
void mapTool::update() 
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) {
		if (mode == 0) {
			mode = 1;
		}
		else {
			mode = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		frameIndex = 0;
	}
	else if (KEYMANAGER->isOnceKeyDown('1')) {
		frameIndex = 1;
	}
	else if (KEYMANAGER->isOnceKeyDown('2')) {
		frameIndex = 5;//배치 이따위로 한거 개 후회됨
	}
	//오브젝트
	else if (KEYMANAGER->isOnceKeyDown('3')) {
		frameIndex = 2;
	}
	else if (KEYMANAGER->isOnceKeyDown('4')) {
		frameIndex = 3;
	}
	else if (KEYMANAGER->isOnceKeyDown('5')) {
		frameIndex = 4;
	}
	else if (KEYMANAGER->isOnceKeyDown('9')) {
		frameIndex = 9;
	}
	//2~5까지는 오브젝트로
	else if (KEYMANAGER->isOnceKeyDown('S')) {
		save("map/save1.map");
	}
	else if (KEYMANAGER->isOnceKeyDown('L')) {
	}
	//굼바
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) {
		frameIndex = 10;
	}
	//거북이
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) {
		frameIndex = 11;
	}
	//쿠파
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3)) {
		frameIndex = 12;

	}


	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) {
		save("map/save1.map");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) {
		save("map/save2.map");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7)) {
		load("map/save1.map");
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) {
		load("map/save2.map");
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && tiles[0].rc.left < 10) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left += 10;
			tiles[i].rc.right += 10;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && tiles[TILEX-1].rc.right > WINSIZEX+10) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left -= 10;
			tiles[i].rc.right -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		for (int i = 0; i < MAX; ++i) {
			if (PtInRect(&tiles[i].rc, _ptMouse)) {
				if (frameIndex == 1 || frameIndex == 5) {
					if (frameIndex == 1) {
						tiles[i].terrain = TR_GROUND;
					}
					else if (frameIndex == 5) {
						tiles[i].terrain = TR_LOCK;
					}
					tiles[i].terrainFrameX = frameIndex;
					tiles[i].terrainFrameY = mode;
				}
				else if (frameIndex == 0) {
					tiles[i].terrain = TR_NONE;
					tiles[i].obj = OBJ_NONE;
					tiles[i].terrainFrameX = frameIndex;
					tiles[i].objFrameX = frameIndex;
					tiles[i].objFrameY = mode;
				}
				else if (frameIndex >= 10) {
					//몬스터 생성용
					tiles[i].objFrameX = frameIndex;
					switch (frameIndex)
					{
					case OBJ_ENEMY_GOOMBA:
						tiles[i].obj = OBJ_ENEMY_GOOMBA;
						break;
					case OBJ_ENEMY_TURTLE:
						tiles[i].obj = OBJ_ENEMY_TURTLE;
						break;
					case OBJ_BOSS_BOWSER:
						tiles[i].obj = OBJ_BOSS_BOWSER;
						break;
					}
					tiles[i].obj = OBJ_ITEMBOX;
				}
				else {
					if (frameIndex == 3 || frameIndex == 5) {
						tiles[i].obj = OBJ_ITEMBOX;
					}
					else if (frameIndex == 4) {
						tiles[i].obj = OBJ_BLOCK;
					}
					tiles[i].terrain = TR_NONE;
					tiles[i].terrainFrameX = 0;
					tiles[i].objFrameX = frameIndex;
					tiles[i].objFrameY = mode;
				}
				break;
			}
		}
	}
	
}
void mapTool::render() 
{//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	char str[256];
	for (int i = 0; i < MAX; ++i) {
		if (tiles[i].rc.right > 0 && tiles[i].rc.left < 1200) {
			IMAGEMANAGER->frameRender("Tiles", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				tiles[i].terrainFrameX, tiles[i].terrainFrameY);
			sprintf_s(str, "%d", i);
			TextOut(getMemDC(), tiles[i].rc.left, tiles[i].rc.top + 10, str, strlen(str));
			sprintf_s(str, "%d", tiles[i].terrain);
			TextOut(getMemDC(), tiles[i].rc.left, tiles[i].rc.top + 30, str, strlen(str));
			sprintf_s(str, "%d", tiles[i].objFrameX);
			TextOut(getMemDC(), tiles[i].rc.left, tiles[i].rc.top + 50, str, strlen(str));
		}
	}

	//실제 스테이지에서 부를때는 obj랑 deco 매니저를 돌려서 만들 것
	for (int i = 0; i < MAX; ++i) {

		if (tiles[i].objFrameX >= 10) {

			switch (tiles[i].objFrameX)
			{
			case OBJ_ENEMY_GOOMBA:
				IMAGEMANAGER->frameRender("Goomba", getMemDC(),
					tiles[i].rc.left, tiles[i].rc.top,
					0, 0);
				break;
			case OBJ_ENEMY_TURTLE:
				IMAGEMANAGER->frameRender("greenTurtle", getMemDC(),
					tiles[i].rc.left, tiles[i].rc.top,
					0, 0);
				break;
			case OBJ_BOSS_BOWSER:
				IMAGEMANAGER->frameRender("bowser", getMemDC(),
					tiles[i].rc.left, tiles[i].rc.top,
					0, 0);
				break;
			}
		}
		else if (tiles[i].objFrameX == 9) {
			IMAGEMANAGER->frameRender("Coin", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				0, 0);
		}
		else if (tiles[i].objFrameX == 0)
			continue;
		else if (tiles[i].rc.right > 0 && tiles[i].rc.left < 1200)
			IMAGEMANAGER->frameRender("Tiles", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				tiles[i].objFrameX, tiles[i].objFrameY);
	}

	TIMEMANAGER->render(getMemDC());
	//==================== 건들지마라 =======================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


void mapTool::save(const char* mapPath)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(mapPath, GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tiles, sizeof(tagTile)*MAX, &write, NULL);

	CloseHandle(file);
}
void mapTool::load(const char* mapPath)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(mapPath, GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, tiles, sizeof(tagTile)*MAX, &read, NULL);

	CloseHandle(file);

	//if(mapPath == "map/save2.map")
	//for (int i = 0; i < MAX; ++i) {
	//	tiles[i].terrainFrameY = 1;
	//}

}

LRESULT mapTool::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
