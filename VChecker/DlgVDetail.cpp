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
}

CDlgVDetail::~CDlgVDetail()
{
	DeleteDC(m_memdcBkBmp);
	DeleteObject(m_cBitmapBkBmp);
}

void CDlgVDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDlgVDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//初始化背景图片DC
	HBITMAP hBmpBk = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_MX));
	CRect rect; 
	HBITMAP hOldBmp = NULL;	

	GetWindowRect(&rect); 	
	if (m_memdcBkBmp.m_hDC == NULL)	
		m_memdcBkBmp.CreateCompatibleDC(this->GetDC());
	if (m_cBitmapBkBmp.m_hObject == NULL)
		m_cBitmapBkBmp.CreateCompatibleBitmap(this->GetDC(),rect.Width(),rect.Height());	
	hOldBmp = (HBITMAP)m_memdcBkBmp.SelectObject(hBmpBk);			

	if(hOldBmp)
		DeleteObject(hOldBmp);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgVDetail, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgVDetail 消息处理程序

BOOL CDlgVDetail::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
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
	CDialog::OnClose();
}

void CDlgVDetail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDC *pDC =  this->GetDC();
	if (m_memdcBkBmp.m_hDC != NULL)
	{
		CRect rect; 
		CDC   memDC; 

		GetWindowRect(&rect); 	
		memDC.CreateCompatibleDC(pDC); 	

		CBitmap* pOldMemBmp = NULL; 
		pOldMemBmp = memDC.SelectObject(&m_cBitmapBkBmp);
		memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_memdcBkBmp,0,0,SRCCOPY);

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

		if(pOldMemBmp)   
			memDC.SelectObject(pOldMemBmp); 

		DeleteObject(pOldMemBmp);	
		DeleteDC(memDC);
		ReleaseDC(pDC);
	}
}
