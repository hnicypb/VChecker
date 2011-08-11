// DlgVSports.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVSports.h"
#include "VCheckerClsGlobal.h"

#include "VCheckerDlg.h"


// CDlgVSports 对话框

IMPLEMENT_DYNAMIC(CDlgVSports, CDialog)

CDlgVSports::CDlgVSports(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVSports::IDD, pParent)
	, m_strCs(_T(""))
	, m_strZs(_T(""))
{
	for(int i=0;i<2;i++)
	{
		m_strShowDataText[i] = _T("");
	}
}

CDlgVSports::~CDlgVSports()
{
	DeleteDC(m_memdcBkBmp);
	DeleteObject(m_cBitmapBkBmp);
}

void CDlgVSports::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CS, m_staticCs);
	DDX_Control(pDX, IDC_STATIC_ZS, m_staticZs);
	DDX_Text(pDX, IDC_STATIC_CS, m_strCs);
	DDX_Text(pDX, IDC_STATIC_ZS, m_strZs);
	DDX_Control(pDX, IDC_STATIC_CS_POINTER, m_staticCsPointer);
	DDX_Control(pDX, IDC_STATIC_ZS_POINTER, m_staticZsPointer);
}

BOOL CDlgVSports::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fInitData();

	//创建界面控件
	for (int i=0;i<2;i++)
	{
		m_dlgShowData[i].Create(IDD_DIALOG_V_SHOW_DATA,this);	
		m_dlgShowData[i].fSetBkBmpFile(m_iShowDataBkImg[i]);
		m_dlgShowData[i].fSetText(m_strShowDataText[i]);		
		m_dlgShowData[i].MoveWindow(m_rectShowData[i]);
		m_dlgShowData[i].ShowWindow(SW_SHOW);
	}

	m_dlgShowData[0].fSetData(_T("5"));
	m_dlgShowData[1].fSetData(_T("0"));

	m_strCs = _T("0");
	m_strZs = _T("0");

	fEnableAutoRefresh(TRUE);

	//初始化背景图片DC
	HBITMAP hBmpBk = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_JJ));
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

BEGIN_MESSAGE_MAP(CDlgVSports, CDialog)
//	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// 初始化竞技界面数据

int CDlgVSports::fInitData(void)
{
	CVCheckerClsGlobal clsGlobal;
	m_iShowDataBkImg[0] = RES_BMP_UNIT_BFH;
	m_strShowDataText[0] = _T("发动机负荷");
	m_rectShowData[0] =  CRect(178,23,302,83);		

	m_iShowDataBkImg[1] = RES_BMP_UNIT_D;
	m_strShowDataText[1] = _T("点火提前角");
	m_rectShowData[1] =	CRect(178,160,302,220);	

	m_pointCircleCs = CPoint(97,123);
	m_pointCircleZs = CPoint(383,123);

	m_dCsRaduis = m_dZsRaduis = 43;

	return 0;
}

void CDlgVSports::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime now = CTime::GetCurrentTime();
	CString str;
	int r;

	for (int i=0;i<2;i++)
	{
		srand(int(now.GetTime()));
		r = 999 + rand()%(999);
		str.Format(_T("%d"),r);
		m_dlgShowData[i].fSetData(str);
	}	

	if (_ttoi(m_strCs)<240)
	{
		m_strCs.Format(_T("%d"),_ttoi(m_strCs)+3);		
	}
	else
	{
		m_strCs = _T("0");
	}
		
	if (_ttoi(m_strZs)<9000)
	{
		m_strZs.Format(_T("%d"),_ttoi(m_strZs)+100);		
	}
	else
	{
		m_strZs = _T("0");
	}

	this->Invalidate();
	CDialog::OnTimer(nIDEvent);
}

void CDlgVSports::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}


// 是否自动刷新数据
int CDlgVSports::fEnableAutoRefresh(bool bEnable)
{
	if (bEnable)
		SetTimer(1,1000,NULL);
	else
		KillTimer(1);
	return 0;
}

void CDlgVSports::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDC *pDC =  this->GetDC();
	if (m_memdcBkBmp.m_hDC != NULL)
	{
		DWORD dwStyle = 0;
		int nDTFlags = 0;
		CRect rcText;
		CFont fontText;
		CRect rect; 
		CDC   memDC; 
		HBITMAP hOldBitmap = NULL;	

		GetWindowRect(&rect); 	
		memDC.CreateCompatibleDC(pDC); 	

		CBitmap* pOldMemBmp = NULL; 
		pOldMemBmp = memDC.SelectObject(&m_cBitmapBkBmp);
		memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_memdcBkBmp,0,0,SRCCOPY);

		memDC.SetBkMode(TRANSPARENT);

		VERIFY(fontText.CreateFont(
			40,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD, //FW_NORMAL,加粗                // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("宋体")));              // lpszFacename
		memDC.SelectObject(&fontText); 
		fontText.DeleteObject();
		dwStyle = m_staticCs.GetStyle();
		nDTFlags = 0;
		if((dwStyle & SS_NOPREFIX) != 0)
		{
			nDTFlags |= DT_NOPREFIX;
		}
		if((dwStyle & SS_CENTER) != 0)
		{
			nDTFlags |= DT_CENTER;
		}
		else if((dwStyle & SS_RIGHT) != 0)
		{
			nDTFlags |= DT_RIGHT;
		}
		else
		{
			nDTFlags |= DT_LEFT;
		}
		if((dwStyle & SS_LEFTNOWORDWRAP) != 0)
		{
			nDTFlags |= DT_SINGLELINE;
		}
		else
		{
			nDTFlags |= DT_WORDBREAK;
		}
		m_staticCs.GetWindowRect(&rcText);
		ScreenToClient(&rcText);

		memDC.SetTextColor(RGB(249,223,4));		
		memDC.DrawText(m_strCs, -1, &rcText, nDTFlags);

		m_staticZs.GetWindowRect(&rcText);
		ScreenToClient(&rcText);
		memDC.DrawText(m_strZs, -1, &rcText, nDTFlags);	

		//画指针到窗口
		////角度(60-320) /刻度(0-240)	/60格	
		int iPos = _ttoi(m_strCs);					//刻度值
		float fIndex = float((iPos)/4);					//刻度索引
		double dAngle = (60+fIndex*4);				//角度索引

		CVCheckerClsGlobal clsGlobal;
		clsGlobal.fDrawPoint(&memDC,m_pointCircleCs,m_dCsRaduis,dAngle);

		////角度(70-320) /刻度(0-100)	/100格	
		fIndex = float(_ttoi(m_strZs)/100);			//刻度索引	
		dAngle = (70+fIndex*2.48);				//角度索引
		clsGlobal.fDrawPoint(&memDC,m_pointCircleZs,m_dZsRaduis,dAngle);

		//double dRectAngle =  (double)((dAngle+100)*PI/180.0);	//换算角度	
		//double dRotateAngle =  2 * PI - (dAngle) * Rad;					
		//m_dZsRaduis = m_dZsRaduis + 30;
		//memDC.Ellipse(m_pointCircleZs.x+m_dZsRaduis,m_pointCircleZs.y+m_dZsRaduis,m_pointCircleZs.x-m_dZsRaduis,m_pointCircleZs.y-m_dZsRaduis);
		//m_dZsRaduis = m_dZsRaduis - 30;

		//将背景位图复制到窗口客户区 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		if(pOldMemBmp)   
			memDC.SelectObject(pOldMemBmp); 

		DeleteObject(pOldMemBmp);
		DeleteObject(fontText);
		DeleteDC(memDC);
	}
}

BOOL CDlgVSports::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}
