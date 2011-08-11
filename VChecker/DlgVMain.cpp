// DlgVMain.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVMain.h"


// CDlgVMain 对话框

IMPLEMENT_DYNAMIC(CDlgVMain, CDialog)

CDlgVMain::CDlgVMain(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVMain::IDD, pParent)
{

}

CDlgVMain::~CDlgVMain()
{
}

void CDlgVMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVMain, CDialog)
END_MESSAGE_MAP()


// CDlgVMain 消息处理程序
