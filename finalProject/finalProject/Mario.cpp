#include "stdafx.h"
#include "Mario.h"



Mario::Mario()
{
}


Mario::~Mario()
{
}

HRESULT Mario::init(image* IMG)
{
	IMAGEMANAGER->addFrameImage("Mario", "image/player/mario.bmp", 560, 320, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("littleMario", "image/player/littlemario.bmp", 560, 160, 7, 2, true, RGB(255, 0, 255));



	return S_OK;
}
void Mario::update()		   
{
}
void Mario::render()		   
{
}
void Mario::keySet()		   
{
}