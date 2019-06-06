#pragma once
#include "playerNode.h"
class Mario :
	public playerNode
{
public:
	Mario();
	~Mario(); 
	HRESULT init(Point p);
	void update();
	void render();
	void keySet() override;
};

