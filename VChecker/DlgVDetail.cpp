// DlgVDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVDetail.h"


// CDlgVDetail 对话框

IMPLEMENT_DYNAMIC(CDlgVDetail, CDialog)

CDlgVDetail::CDlgVDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVDetail::IDD, pParent)
{
	CVCheckerClsGlobal clsGlobal;
	m_strBkBmpFile = clsGlobal.fGetRes(RES_BMP_MAIN_MX);
	m_hBkBmp = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_MX));
}

CDlgVDetail::~CDlgVDetail()
{
}

void CDlgVDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVDetail, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgVDetail 消息处理程序

BOOL CDlgVDetail::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_hBkBmp != NULL)
	{
		CRect rect; 
		CDC   memDC; 

		CString strTime;	
		CTime time = CTime::GetCurrentTime();
		strTime.Format(_T("%02d:%02d"),time.GetHour(),time.GetMinute());		

		GetWindowRect(&rect); 	
			
		HBITMAP hOldBitmap;	

		memDC.CreateCompatibleDC(pDC); 
		hOldBitmap = (HBITMAP)memDC.SelectObject(m_hBkBmp); 

		memDC.SetBkMode(TRANSPARENT);	
		//CFont fontText;
		//VERIFY(fontText.CreateFont(
		//	43,                        // nHeight
		//	0,                         // nWidth
		//	0,                         // nEscapement
		//	0,                         // nOrientation
		//	FW_BOLD, //FW_NORMAL,加粗                // nWeight
		//	FALSE,                     // bItalic
		//	FALSE,                     // bUnderline
		//	0,                         // cStrikeOut
		//	ANSI_CHARSET,              // nCharSet
		//	OUT_DEFAULT_PRECIS,        // nOutPrecision
		//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
		//	DEFAULT_QUALITY,           // nQuality
		//	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		//	_T("Arial Rounded MT")));              // lpszFacename
		//CRect rc;
		//m_staticTime.GetWindowRect(&rc);
		//ScreenToClient(&rc);
		//DWORD dwStyle = m_staticTime.GetStyle();
		//int nDTFlags = 0;
		//if((dwStyle & SS_NOPREFIX) != 0)
		//{
		//	nDTFlags |= DT_NOPREFIX;
		//}
		//if((dwStyle & SS_CENTER) != 0)
		//{
		//	nDTFlags |= DT_CENTER;
		//}
		//else if((dwStyle & SS_RIGHT) != 0)
		//{
		//	nDTFlags |= DT_RIGHT;
		//}
		//else
		//{
		//	nDTFlags |= DT_LEFT;
		//}
		//if((dwStyle & SS_LEFTNOWORDWRAP) != 0)
		//{
		//	nDTFlags |= DT_SINGLELINE;
		//}
		//else
		//{
		//	nDTFlags |= DT_WORDBREAK;
		//}
		//memDC.SelectObject(&fontText); 
		//fontText.DeleteObject();
		//memDC.SetTextColor(RGB(255,255,255));   //设置字体颜色白色  
		//memDC.DrawText(strTime, -1, &rc, nDTFlags);

		//memDC.SetTextColor(RGB(249,223,4));		

		//m_staticSS.GetWindowRect(&rc);
		//ScreenToClient(&rc);
		//memDC.DrawText(m_strSS, -1, &rc, nDTFlags);	

		//将背景位图复制到窗口客户区 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		if(hOldBitmap)   
			memDC.SelectObject(hOldBitmap); 

		
		DeleteObject(hOldBitmap);
		//DeleteObject(fontText);		
		DeleteDC(memDC);

		return TRUE;
	}
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgVDetail::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgVDetail::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DeleteObject(m_hBkBmp);
	CDialog::OnClose();
}
