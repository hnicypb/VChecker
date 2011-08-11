// DlgVConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVConfig.h"


// CDlgVConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgVConfig, CDialog)

CDlgVConfig::CDlgVConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVConfig::IDD, pParent)
{
	CVCheckerClsGlobal clsGlobal;
	m_hBkBmp = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_SZ));
}

CDlgVConfig::~CDlgVConfig()
{
}

void CDlgVConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVConfig, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
//	ON_WM_RBUTTONUP()
ON_WM_LBUTTONDBLCLK()
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgVConfig ��Ϣ�������

BOOL CDlgVConfig::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgVConfig::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if (point.y<240)
		g_pDlg->fSetPanel(CPoint(0,0));
	else
		g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgVConfig::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgVConfig::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDC *pDC =  this->GetDC();
	if (m_hBkBmp != NULL)
	{
		CRect rect; 
		CDC   memDC; 
		HBITMAP hOldBitmap = NULL;	

		GetWindowRect(&rect); 	
		memDC.CreateCompatibleDC(pDC); 	

		CBitmap cBitmap; 
		CBitmap cDrawBitmap; 
		CBitmap* pOldMemBmp = NULL; 
		HBITMAP hOldBmp = NULL;	

		CDC memdcBmp;
		memdcBmp.CreateCompatibleDC(pDC);
		hOldBmp = (HBITMAP)memdcBmp.SelectObject(m_hBkBmp);		
		cBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
		pOldMemBmp = memDC.SelectObject(&cBitmap);
		memDC.BitBlt(0,0,rect.Width(),rect.Height(),&memdcBmp,0,0,SRCCOPY);
		if(hOldBmp)
			DeleteObject(hOldBmp);

		memDC.SetBkMode(TRANSPARENT);	
		//CFont fontText;
		//VERIFY(fontText.CreateFont(
		//	43,                        // nHeight
		//	0,                         // nWidth
		//	0,                         // nEscapement
		//	0,                         // nOrientation
		//	FW_BOLD, //FW_NORMAL,�Ӵ�                // nWeight
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
		//memDC.SetTextColor(RGB(255,255,255));   //����������ɫ��ɫ  
		//memDC.DrawText(strTime, -1, &rc, nDTFlags);

		//memDC.SetTextColor(RGB(249,223,4));		

		//m_staticSS.GetWindowRect(&rc);
		//ScreenToClient(&rc);
		//memDC.DrawText(m_strSS, -1, &rc, nDTFlags);	

		//������λͼ���Ƶ����ڿͻ��� 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		if(pOldMemBmp)   
			memDC.SelectObject(pOldMemBmp); 

		DeleteObject(hOldBmp);
		DeleteDC(memdcBmp);

		DeleteObject(pOldMemBmp);		
		DeleteObject(cBitmap);
		DeleteDC(memDC);
	}
}
