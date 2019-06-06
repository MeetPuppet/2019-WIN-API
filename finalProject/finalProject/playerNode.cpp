#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "playerNode.h"
//순서가 매우 중요함
//그리고 속성에서 버전맞추어줄때
//문자집합도 멀티바이트로 맞추어 줘야 고칠게 없음
//Commit is Real

#define WIDTH 560  //이미지 가로길이
#define HEIGHT 320 //이미지 세로길이

#define SPEED 300
#define JUMPSPEED 6
#define FRAMETIME 0.2

playerNode::playerNode()
{//무슨일이 벌어질지 모르니 설정해둠
	image = NULL;
	x = y = 0;
	rc = { 0,0,0,0 };
	speed = 0;
	JumpPower = 0;
	state = IDLE;
	time = 0;

	jumpStartY = 0;
}


playerNode::~playerNode()
{
}

HRESULT playerNode::init()
{			


	return S_OK;
}

void playerNode::update() 
{
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());

}

void playerNode::render() 
{
	
}
void playerNode::stateUpdate() {
	
}

void playerNode::keySet()
{
	
}

void playerNode::stateFrameUpdate()
{
	
}