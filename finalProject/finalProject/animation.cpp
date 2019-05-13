#include "stdafx.h"
#include "animation.h"


animation::animation()
	: _frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(FALSE)
{
}


animation::~animation()
{

}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 몇개의 프레임인지 계산한다
	_frameNum = _frameNumWidth * _frameNumHeight;

	for ( int i = 0; i < _frameNumHeight; ++i )
	{
		for ( int j = 0; j < _frameNumWidth; ++j )
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	//처음엔 디폴트 애니메이션 재생으로 둔다
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{

}


//디폴트 애니메이션 재생
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프여부 
	_loop = loop;
	//벡터는 한 번 초기화해준다
	_playList.clear();

	if ( reverse )
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum -1; i >= 0; --i )
			{
				_playList.push_back(i);
			}

		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum - 1; i >= 0; --i )
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	//루프여부 
	_loop = loop;
	//벡터는 한 번 초기화해준다
	_playList.clear();

	if ( reverse )
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum - 1; i >= 0; --i )
			{
				_playList.push_back(i);
			}

		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum - 1; i >= 0; --i )
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	//루프여부 
	_loop = loop;
	//벡터는 한 번 초기화해준다
	_playList.clear();

	if ( reverse )
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum - 1; i >= 0; --i )
			{
				_playList.push_back(i);
			}

		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
			for ( int i = _frameNum - 1; i >= 0; --i )
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if ( _loop )
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for ( int i = 0; i < _frameNum; ++i )
			{
				_playList.push_back(i);
			}
		}
	}
}

//배열로 애니메이션 재생(원하는 프레임 번호 넣을수있다)
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for ( int i = 0; i < arrLen; ++i )
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for ( int i = 0; i < arrLen; ++i )
	{
		_playList.push_back(playArr[i]);
	}
}
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	for ( int i = 0; i < arrLen; ++i )
	{
		_playList.push_back(playArr[i]);
	}
}

//구간 애니메이션 재생(ex : 2 ~ 8번만 혹은 9 ~ 1번만)
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;


	//루프 여부
	_loop = loop;
	//플레이 벡터 초기화
	_playList.clear();

	//재생할 프레임이 1이라면
	if ( start == end )
	{
		_playList.clear();
		stop();
		return;
	}

	//start 프레임번호가 end번호보다 클때(ex : 5 ~ 1)
	if ( start > end )
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;


	//루프 여부
	_loop = loop;
	//플레이 벡터 초기화
	_playList.clear();

	//재생할 프레임이 1이라면
	if ( start == end )
	{
		_playList.clear();
		stop();
		return;
	}

	//start 프레임번호가 end번호보다 클때(ex : 5 ~ 1)
	if ( start > end )
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;


	//루프 여부
	_loop = loop;
	//플레이 벡터 초기화
	_playList.clear();

	//재생할 프레임이 1이라면
	if ( start == end )
	{
		_playList.clear();
		stop();
		return;
	}

	//start 프레임번호가 end번호보다 클때(ex : 5 ~ 1)
	if ( start > end )
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
				for ( int i = end + 1; i < start; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i >= end; --i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
				for ( int i = end - 1; i >= start; --i )
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if ( _loop )
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for ( int i = start; i < end; ++i )
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

//프레임 재생 속도 셋팅
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}


void animation::frameUpdate(float elapsedTime)
{
	if ( _play )
	{
		_elapsedSec += elapsedTime;

		if ( _elapsedSec >= _frameUpdateSec )
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;
			//끝까지 재생이 되었다면
			if ( _nowPlayIndex == _playList.size() )
			{
				if ( _loop ) _nowPlayIndex = 0;
				else
				{
					if ( _obj == NULL )
					{
						if ( _callbackFunction != NULL ) _callbackFunction();
					}
					else
					{
						_callbackFunctionParameter(_obj);
					}

					_nowPlayIndex--;
					_play = FALSE;
				}
			}
		}
	}
}


void animation::start(void)	
{
	_play = TRUE;
	_nowPlayIndex = 0;
}

void animation::stop(void)	
{
	_play = FALSE;
	_nowPlayIndex = 0;
}

void animation::pause(void)	
{
	_play = FALSE;
}

void animation::resume(void)
{
	_play = TRUE;
}
