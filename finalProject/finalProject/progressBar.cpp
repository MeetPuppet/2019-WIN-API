#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{

}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBottom = IMAGEMANAGER->addImage("backBar",
		"hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));


	//재호랑, 태호랑, 신우는 내가 시켜볼게 있는데...
	//지금 프로그레스 바를 사용하게 되면 젤 처음 선언한 크기로 모조리 셋팅이 강제로 될텐데
	//그 부분을 고쳐서 반친구들이 사용하기 편하도록 셋팅할떄 크기를 바꾸면 죄다 각각 크기 바껴서
	//설정이 될 수 있도록 만들어서 배포하시요~

	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update() 
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarBottom->getWidth(), _progressBarTop->getHeight());
}

void progressBar::render() 
{
	IMAGEMANAGER->render("backBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render("frontBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

}


void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//퍼센테이지 산출한다
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}


