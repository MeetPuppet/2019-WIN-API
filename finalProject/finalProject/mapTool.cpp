#include "stdafx.h"
#include "mapTool.h"

#define MAX TILEX*TILEY


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
	gameNode::release();
}

HRESULT mapTool::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addFrameImage("Tiles", "image/tile/Tiles.bmp", 480, 160, 6, 2, true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("itemBox", "image/tile/itemBox.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	
	for (int i = 0; i < TILEY; ++i) {
		for (int j = 0; j < TILEX; ++j) {
			tiles[(i*TILEX) + j].rc = { j*TILESIZE,i*TILESIZE
									,j*TILESIZE + TILESIZE
									,i*TILESIZE + TILESIZE };
			
		}
	}
	frameIndex = 0;
	return S_OK;
}
void mapTool::update() 
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		frameIndex = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('S')) {
		save();
	}
	if (KEYMANAGER->isOnceKeyDown('L')) {
		load();
	}
	if (KEYMANAGER->isOnceKeyDown('1')) {
		frameIndex = 1;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && tiles[0].rc.left < 10) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left += 10;
			tiles[i].rc.right += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && tiles[TILEX-1].rc.right > WINSIZEX+10) {
		for (int i = 0; i < MAX; ++i) {
			tiles[i].rc.left -= 10;
			tiles[i].rc.right -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		for (int i = 0; i < MAX; ++i) {
			if (PtInRect(&tiles[i].rc, _ptMouse)) {
				tiles[i].terrainFrameX = frameIndex;
				break;
			}
		}
	}
	
}
void mapTool::render() 
{//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================

	for (int i = 0; i < MAX; ++i) {
		if (tiles[i].rc.right > 0 && tiles[i].rc.left < 1200)
			IMAGEMANAGER->frameRender("Tiles", getMemDC(),
				tiles[i].rc.left, tiles[i].rc.top,
				tiles[i].terrainFrameX, tiles[i].terrainFrameY);
	}

	//==================== 건들지마라 =======================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


void mapTool::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("map/save1.map", GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tiles, sizeof(tagTile)*MAX, &write, NULL);

	CloseHandle(file);
}
void mapTool::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("map/save1.map", GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FAILED(file)) {
		return;
	}
	memset(attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	memset(pos, 0, sizeof(int) * 2);

	ReadFile(file, tiles, sizeof(tagTile)*MAX, &read, NULL);

	CloseHandle(file);
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
