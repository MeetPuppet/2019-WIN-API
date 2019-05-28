#include "stdafx.h"//매니저가 여기에 다 몰려있으니 필요함
#include "playerNode.h"
//순서가 매우 중요함
//그리고 속성에서 버전맞추어줄때
//문자집합도 멀티바이트로 맞추어 줘야 고칠게 없음

#define WIDTH 540  //이미지 가로길이
#define HEIGHT 360 //이미지 세로길이

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

HRESULT playerNode::init(const char* keyName, const char* fileName , int playerNumber)
{			//프레임이미지 저장용			호출명	 파일위치  가로	  세로
	image = IMAGEMANAGER->addFrameImage(keyName, fileName, WIDTH, HEIGHT,
										7, 2, //프레임X,Y갯수
										true, //지우는 색이 있는가 ?
										RGB(255,255,255));//지울 색의 RGB값
	//현재 함수가 돌면 이미지를 map이라는 STL에 저장하고 그 위치의 주소값을 돌려줌
	//그러면 image는 만들어둔 구조체+클래스의 값을 가진 변수를 가르키게 됨
	//호출명을 설정하는 이유는 IMAGEMANAGER->findImage(keyName) 로 찾아내기 위해서임(편함)
	
	//현재 사용할 이미지는 little만 아니면 값들이 똑같으니 당장은 이렇게 설정함
	//직접 little을 한번 만들어 봐도 괜찮을 거임
	
	x, y;//캐릭터의 중심점 설정

	//딱 윈도우 중간
	x = WINSIZEX / 2;//이미 설정해둔 윈도우 사이즈 define임
	y = WINSIZEY / 2;//이미 설정해둔 윈도우 사이즈 define임
	 //설정해둔 매크로   중앙지점 가로  세로
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());
							  //이미지에서 설정해둔 x,y 당 프레임 가로세로길이

	state = IDLE;//움직이지 않는다는 뜻

	JumpPower = 0;//점프파워 설정(중력적용에 필요)
	//얘는 점프하는 순간 작동하게 됨

	time = 0;
	playerNum = playerNumber;
	//잘돌았으니까
	return S_OK;
	//만약 void 라면 없으면 되는것
}

void playerNode::update() 
{
	//이건 웬만하면 맨위나 맨아래 있어야함
	//그냥 깜박하는 경우가 많아서 그렇게 생각하고있음
	//이미지를 띄울위치를 RECT값으로 저장해 놓고 띄우기
	rc = RectMakeCenter(x, y, image->getFrameWidth(), image->getFrameHeight());

	//당장 여기 업데이트 순서는 별로 상관없음
	//상태값으로 업뎃
	stateUpdate();
	if (playerNum == 1) {
		//키에 의한 업뎃
		keySet();
	}
	else {
		//키에 의한 업뎃
		keySet2();
	}
	//프레임 업뎃
	stateFrameUpdate();
}

void playerNode::render() 
{
	//     프레임렌더 얘를써야복사가능 
	image->frameRender(getMemDC(), 
		x, y,//xy값
		image->getFrameX(), //image에서 설정되고 있는 프레임값들
		image->getFrameY());//

	//시간출력용
	//디버그, 릴리즈 모드에 따라서 출력이 다름
	TIMEMANAGER->render(getMemDC());
	//이동속도 적용에 문제가 있어보여서 넣은것
	
	//적용값이 이상해 보일때 이렇게 출력해서 보면 편함
	char str[256];
	sprintf_s(str, "SPEED * ElapsedTime : %f", speed);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
}
void playerNode::stateUpdate() {
	//시간에 따라 돌리면 좋다.
	//컴퓨터마다 성능이 다르기 때문에 시간값을 같이 계산하면 어디서든 같은 동작을 하게되기 때문
	//근데 나도 잘 못함

	//이렇게 스위치나 if는 없어도 가능함
	//그냥 보기 편하게 만들기위해서 스위치를 썼음
	float elapsedTime;
	switch (state)
	{
	case IDLE://암움직임
		break;
	case MOVE:						//시간 간격을 1이하의 float값으로 돌려줌
		elapsedTime = TIMEMANAGER->getElapsedTime();
		speed = SPEED * TIMEMANAGER->getElapsedTime();

		//오른쪽 이냐는 뜻
		if (image->getFrameY() == 0) {
			x += speed;
			//좌우 이속이 달라보이는데 분명 맞게 돌아감
		}
		else if (image->getFrameY() == 1) {
			x -= speed;
		}
		break;
	case SIT:
		break;
	case JUMP:
		//점프값 만큼 위로 올라간다.
		if (250 < y && y < 300) {
			jumpagain = TRUE;
		}
		y -= JumpPower;// JUMPSPEED로 초기화됨
		//시간 반영을 위해 실시간으로 빼주기
		JumpPower -= JUMPSPEED* 1.8 * TIMEMANAGER->getElapsedTime();

		//이건 충돌할 걸 아무거 해줘도 된다.
		//지금 당장은 시작점을 받아서 만들었다.
		if (jumpStartY < y) {
			y = jumpStartY;
			image->setFrameX(0);
			state = IDLE;
		}
		break;
	}
}
//키셋을 포함한 프레임 상하를 관리해주는 함수
void playerNode::keySet()
{
	//이미지에서 상하(Y)로 볼때는
	//왼쪽이 아래쪽(1), 오른쪽이 위쪽(0)이다 이다.
	//좌우(X)는 아래함수 stateUpdate()를 참조바람

	//상하좌우 방향키
	//if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
	//	//그냥 한번 둬봄
	//}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && state != JUMP) {
		image->setFrameX(6);
		//state = SIT;
		//그냥 한번 둬봄
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && state != JUMP) {
		image->setFrameX(0);
		//state = SIT;
		//그냥 한번 둬봄
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(1);//왼쪽으로 프레임Y 설정(이미지 아랫부분)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && state == MOVE
		&& image->getFrameY() == 1) {
		image->setFrameX(0);//이건 stateFrameUpdate()에서 돌려도 무방
		state = IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(0);//왼쪽으로 프레임Y 설정(이미지 윗부분)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && state == MOVE
		&& image->getFrameY() == 0) {
		image->setFrameX(0);//이건 stateFrameUpdate()에서 돌려도 무방
		state = IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x -= speed;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && state != JUMP) {//점프상태가 아니고 z키가 눌리면
		state = JUMP;
		image->setFrameX(5);
		//점프 시작지점을 받아서
		jumpStartY = y;
		//나중에 다시 여기 닿으면 꺼짐

		//점프 속도 설정
		JumpPower = JUMPSPEED;
	}
	if (state == JUMP && jumpagain == TRUE) {
		image->setFrameX(1);
		JumpPower = JUMPSPEED;
		image->setFrameX(5);
		jumpagain = FALSE;
	}
}

void playerNode::keySet2()
{
	//이미지에서 상하(Y)로 볼때는
	//왼쪽이 아래쪽(1), 오른쪽이 위쪽(0)이다 이다.
	//좌우(X)는 아래함수 stateUpdate()를 참조바람

	//상하좌우 방향키
	//if (KEYMANAGER->isOnceKeyDown('W')) {
	//	//그냥 한번 둬봄
	//}
	if (KEYMANAGER->isOnceKeyDown('S') && state != JUMP) {
		image->setFrameX(6);
		//state = SIT;
		//그냥 한번 둬봄
	}
	else if (KEYMANAGER->isOnceKeyUp('S') && state != JUMP) {
		image->setFrameX(0);
		//state = SIT;
		//그냥 한번 둬봄
	}
	if (KEYMANAGER->isOnceKeyDown('A') && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(1);//왼쪽으로 프레임Y 설정(이미지 아랫부분)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp('A') && state == MOVE
		&& image->getFrameY() == 1) {
		image->setFrameX(0);//이건 stateFrameUpdate()에서 돌려도 무방
		state = IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown('D') && state != JUMP) {
		image->setFrameX(1);
		image->setFrameY(0);//왼쪽으로 프레임Y 설정(이미지 윗부분)
		state = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyUp('D') && state == MOVE
		&& image->getFrameY() == 0) {
		image->setFrameX(0);//이건 stateFrameUpdate()에서 돌려도 무방
		state = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}

	if (KEYMANAGER->isStayKeyDown('S') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x += speed;
	}
	if (KEYMANAGER->isStayKeyDown('A') && state == JUMP) {
		speed = SPEED * TIMEMANAGER->getElapsedTime();
		x -= speed;
	}

	if (KEYMANAGER->isOnceKeyDown('W') && state != JUMP) {//점프상태가 아니고 z키가 눌리면
		state = JUMP;
		image->setFrameX(5);
		//점프 시작지점을 받아서
		jumpStartY = y;
		//나중에 다시 여기 닿으면 꺼짐

		//점프 속도 설정
		JumpPower = JUMPSPEED;
	}
	if (state == JUMP && jumpagain == TRUE) {
		image->setFrameX(1);
		JumpPower = JUMPSPEED;
		image->setFrameX(5);
		jumpagain = FALSE;
	}
}
//별다른일 없으면 프레임의 좌우를 관리해주는 함수
void playerNode::stateFrameUpdate()
{
	//이미지를 한번보면 알겠지만
	//좌우(X)로 볼때 0번은 가만히있는거(IDLE)
	// 1,2,3번은 이동(MOVE)
	// 5번은 점프 (JUMP)
	// 6번은 앉기 (SIT)
	// 당장은 안쓰니 4번은 거르자
	//상하(Y)는 위함수 keySet()을 참조바람

	switch (state)
	{
	case IDLE://IDLE 상태일때의 업데이트
		    //이미지의 프레임 위치를 0번으로
		//image->setFrameX(0);//키 땔때 써도 됨
		break;
	case MOVE://이하생략
		//시간을 계속 더해줌(꼼수)
		time += TIMEMANAGER->getElapsedTime();
		//프레임 X가 0보다 크고 프레임 X가 3보다 작을때			 0.2초가 지나면
		if (image->getFrameX() > 0 && image->getFrameX() < 3 && time > FRAMETIME) {
			//이미지의 프레임 위치를 현재 프레임+1로 설정
			image->setFrameX(image->getFrameX() + 1);
			time -= FRAMETIME;
		}
		//위 조건과 안맞는데 3번 이미지 일때
		else if (image->getFrameX() == 3 && time > FRAMETIME){
			//다시 1번으로 돌려둠
			image->setFrameX(1);
			time -= FRAMETIME;
		}
		break;
		/*
		더 이상 자세한 설명은 생략한다.
		*/
	case SIT:
		break;
	case JUMP:
		break;
	default:
		//지워도 무방한 곳
		break;
	}
}