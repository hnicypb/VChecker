// VCheckerResZhCn.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "VCheckerResZhCn.h"
#include <windows.h>
#include <commctrl.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

// ���ǵ���������һ��ʾ��
VCHECKERRESZHCN_API int nVCheckerResZhCn=0;

// ���ǵ���������һ��ʾ����
VCHECKERRESZHCN_API int fnVCheckerResZhCn(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� VCheckerResZhCn.h
CVCheckerResZhCn::CVCheckerResZhCn()
{ 
	return; 
}
