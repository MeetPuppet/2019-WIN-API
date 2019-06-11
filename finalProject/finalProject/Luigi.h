#pragma once
#include "playerNode.h"
class Luigi :
	public playerNode
{
public:
	Luigi();
	~Luigi();
	HRESULT init(Point p);
	void update();
	void render();
	void keySet() override;
};

