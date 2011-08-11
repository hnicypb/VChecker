// VChecker.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CVCheckerApp:
// 有关此类的实现，请参阅 VChecker.cpp
//
//#include "E:\Yipb\V-Checker\VChecker\VCheckerRes\resource.h"
#include "VCheckerDlg.h"

class CVCheckerApp : public CWinApp
{
public:
	CVCheckerApp();
				
	
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CVCheckerApp theApp;
extern CVCheckerDlg *g_pDlg;		//主窗口对象
extern HINSTANCE g_hResDll;				//资源DLL句柄
//extern HMODULE g_hMod;				//资源动态库对象
