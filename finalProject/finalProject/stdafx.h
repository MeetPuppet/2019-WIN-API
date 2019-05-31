#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "collision.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
//#include "txtData.h" - 2019.05.13 기억안나는건 주석처리
//#include "effectManager.h" - 2019.05.13 기억안나는건 주석처리
#include "sceneManager.h"
#include "keyAniManager.h"
//#include "database.h" - 2019.05.13 기억안나는건 주석처리

using namespace std;
using namespace HEXA_UTIL;

//=====================================
// ## 디파인 ## 17.09.29 ##
//=====================================

#define WINNAME		(LPTSTR)(TEXT("Window Name"))
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1200
#define WINSIZEY	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
//#define EFFECTMANAGER effectManager::getSingleton() - 2019.05.13 기억안나는건 주석처리
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
//#define TXTDATA txtData::getSingleton() - 2019.05.13 기억안나는건 주석처리
//#define INIDATA iniDataManager::getSingleton()
//#define DATABASE database::getSingleton() - 2019.05.13 기억안나는건 주석처리

//=============================================================
// ## 17.10.18 ## Macro ##
//=============================================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}


//=====================================
// ## extern ## 17.10.12 ##
//=====================================

extern HINSTANCE _hInstance;	
extern HWND	_hWnd;			
extern POINT _ptMouse;
extern BOOL _leftMouseButton;