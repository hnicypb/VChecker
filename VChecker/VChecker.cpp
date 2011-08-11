// VChecker.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "VChecker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVCheckerApp

BEGIN_MESSAGE_MAP(CVCheckerApp, CWinApp)
END_MESSAGE_MAP()


// CVCheckerApp ����
CVCheckerApp::CVCheckerApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVCheckerApp ����
CVCheckerApp theApp;
//HMODULE g_hMod;
HINSTANCE g_hResDll;

// CVCheckerApp ��ʼ��

BOOL CVCheckerApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//AfxSetResourceHandle(g_hMod);
	g_hResDll = LoadLibrary(_T("VCheckerResZhCn.dll"));		
	if (g_hResDll == NULL)
	{
		AfxMessageBox(_T("������Դ���ļ�ʧ��!"));
	}

	CVCheckerClsGlobal clsGlobal;
	if (NULL != AddFontResource(clsGlobal.fGetAppPath() + _T("\\font\\ARLRDBD.TTF")))		// AddFontResource(CUSTOM_FONT))
	{
		::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	}

	CVCheckerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}

	if(RemoveFontResource(clsGlobal.fGetAppPath() + _T("\\font\\ARLRDBD.ttf")))
	{
		::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	}

	FreeLibrary(g_hResDll);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
