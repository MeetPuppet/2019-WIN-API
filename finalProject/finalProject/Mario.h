#pragma once
#include "playerNode.h"
class Mario :
	public playerNode
{
public:
	Mario();
	~Mario(); 
	HRESULT init(image* IMG);
	void update();
	void render();
	void keySet() override;
};

