// VChecker.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CVCheckerApp:
// �йش����ʵ�֣������ VChecker.cpp
//
//#include "E:\Yipb\V-Checker\VChecker\VCheckerRes\resource.h"
#include "VCheckerDlg.h"

class CVCheckerApp : public CWinApp
{
public:
	CVCheckerApp();
				
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVCheckerApp theApp;
extern CVCheckerDlg *g_pDlg;		//�����ڶ���
extern HINSTANCE g_hResDll;				//��ԴDLL���
//extern HMODULE g_hMod;				//��Դ��̬�����
