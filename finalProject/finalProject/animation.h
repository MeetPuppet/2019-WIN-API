#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//보이드 포인터는 뭐든지 가르킬 수 가 있다 
//언뜻 편해보이지만 형이 void이기 때문에 꼭 자료형을 선언을 해줘야한다

class animation
{
public:
	typedef vector<POINT> vFrameList;	//프레임 번호 리스트
	typedef vector<int> vPlayList;		//애니메이션 플레이 리스트

private:
	int			_frameNum;
	vFrameList	_frameList;
	vPlayList	_playList;

	int			_frameWidth;
	int			_frameHeight;

	BOOL		_loop;

	float		_frameUpdateSec;
	float		_elapsedSec;

	DWORD		_nowPlayIndex;
	BOOL		_play;

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//디폴트 애니메이션 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열로 애니메이션 재생(원하는 프레임 번호 넣을수있다)
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//구간 애니메이션 재생(ex : 2 ~ 8번만 혹은 9 ~ 1번만)
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//프레임 재생 속도 셋팅
	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	inline BOOL isPlay(void) { return _play; }
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }

};

