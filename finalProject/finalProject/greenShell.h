#pragma once
#include "objectNode.h"
class greenShell :
	public objectNode
{
private:
	float time;
	bool isRight;
	bool isKicked;
public:
	greenShell();
	~greenShell();

	HRESULT init(int x, int y, int sizeX, int sizeY);
	void update();
	void render();
	float getTime()
	{
		return time;
	}
	bool getKicked() { return isKicked; }
	void stop() {
		isKicked = false;
	}
	void kicked(bool isright)
	{
		if (isKicked == false) {
			isKicked = true;
			isRight = isright;
		}
	}

};

