#include "stdafx.h"
#include "greenShell.h"



greenShell::greenShell()
{
	time = 0;
	isKicked = false;
}


greenShell::~greenShell()
{
}


HRESULT greenShell::init(int x, int y, int sizeX, int sizeY)
{
	objectNode::init("greenShell", x, y, sizeX, sizeY);

	return S_OK;
}
void greenShell::update()
{
	objectNode::update();

	float ET = TIMEMANAGER->getElapsedTime();
	if (ET < 0) ET = 0.016;
	if (isKicked) {
		if (isRight) {
			p.x += 500 * ET;
		}
		else {
			p.x -= 500 * ET;
		}
	}
	else {
		time = time + ET;
		if(time)
		if (time > 1) {
			if (frameX == 0) {
				frameX = 1;
			}
			else
				frameX = 0;
		}
		//if (timenum > 500) {
		//	// º¯½Å
		//}
	}
}

void greenShell::render()
{
	objectNode::render();
}