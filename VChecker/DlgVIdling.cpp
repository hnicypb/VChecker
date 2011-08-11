// DlgVIdling.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVIdling.h"
#include "VCheckerDlg.h"

// CDlgVIdling 对话框

IMPLEMENT_DYNAMIC(CDlgVIdling, CDialog)

CDlgVIdling::CDlgVIdling(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVIdling::IDD, pParent)
{
}

CDlgVIdling::~CDlgVIdling()
{
	DeleteDC(m_memdcBkBmp);
	DeleteObject(m_cBitmapBkBmp);
}

void CDlgVIdling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticTime);
	DDX_Control(pDX, IDC_STATIC_DATE, m_staticDate);
	DDX_Control(pDX, IDC_STATIC_WEEK, m_staticWeek);
	DDX_Control(pDX, IDC_STATIC_LON, m_staticLon);
	DDX_Control(pDX, IDC_STATIC_LON1, m_staticLon1);
	DDX_Control(pDX, IDC_STATIC_LAT, m_staticLat);
	DDX_Control(pDX, IDC_STATIC_LAT1, m_staticLat1);
}

BOOL CDlgVIdling::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	fInitData();

	//m_dlgShowData[0].Create(IDD_DIALOG_V_SHOW_DATA,this);		
	//m_dlgShowData[0].fSetBkBmpFile(m_strShowDataBkImg[0]);
	//m_dlgShowData[0].fSetText(m_strShowDataText[0]);

	//m_dlgShowData[i].ShowWindow(SW_SHOW);
	
	//创建界面控件
	for (int i=0;i<6;i++)
	{
		m_dlgShowData[i].Create(IDD_DIALOG_V_SHOW_DATA,this);		
		m_dlgShowData[i].fSetBkBmpFile(m_iShowDataBkImg[i]);
		m_dlgShowData[i].fSetText(m_strShowDataText[i]);		
		m_dlgShowData[i].MoveWindow(m_rectShowData[i]);
		m_dlgShowData[i].ShowWindow(SW_SHOW);
	}

	m_dlgShowData[0].fSetData(_T("70.1"));
	m_dlgShowData[1].fSetData(_T("1708"));
	m_dlgShowData[2].fSetData(_T("14.1"));
	m_dlgShowData[3].fSetData(_T("51.1"));
	m_dlgShowData[4].fSetData(_T("0.8"));
	m_dlgShowData[5].fSetData(_T("11.0"));

	fEnableAutoRefresh(TRUE);

	//初始化背景图片DC
	HBITMAP hBmpBk = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_DS));
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

BEGIN_MESSAGE_MAP(CDlgVIdling, CDialog)
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_STATIC_LON, &CDlgVIdling::OnStnClickedStaticLon)
	ON_WM_TIMER()
//	ON_WM_MBUTTONDBLCLK()
//ON_WM_LBUTTONDBLCLK()
//ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_PAINT()
END_MESSAGE_MAP()


// 初始化怠速界面数据
int CDlgVIdling::fInitData(void)
{
	CVCheckerClsGlobal clsGlobal;

	m_iShowDataBkImg[0] = RES_BMP_UNIT_WD;
	m_strShowDataText[0] = clsGlobal.fGetRes(IDS_STRING_FDJSW);	//_T("发动机水温");
	m_rectShowData[0] =  CRect(28,20,152,80);		

	m_iShowDataBkImg[1] = RES_BMP_UNIT_WD;
	m_strShowDataText[1] = clsGlobal.fGetRes(IDS_STRING_FDJZS);	//_T("发动机转速");
	m_rectShowData[1] =	CRect(28,90,152,150);	

	m_iShowDataBkImg[2] = RES_BMP_UNIT_WD;
	m_strShowDataText[2] = clsGlobal.fGetRes(IDS_STRING_DPDY);	 //_T("电瓶电压");
	m_rectShowData[2] =	CRect(28,160,152,220);	

	m_iShowDataBkImg[3] = RES_BMP_UNIT_WD;
	m_strShowDataText[3] = clsGlobal.fGetRes(IDS_STRING_JQWD);	//_T("进气温度");
	m_rectShowData[3] = CRect(328,20,452,80);

	m_iShowDataBkImg[4] = RES_BMP_UNIT_WD;
	m_strShowDataText[4] = clsGlobal.fGetRes(IDS_STRING_JSYH);	//_T("即时油耗");
	m_rectShowData[4] = CRect(328,90,452,150);

	m_iShowDataBkImg[5] = RES_BMP_UNIT_WD;
	m_strShowDataText[5] =clsGlobal.fGetRes(IDS_STRING_LSPJYH);	//_T("历史平均油耗");
	m_rectShowData[5] = CRect(328,160,452,220);

	return 0;
}

BOOL CDlgVIdling::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgVIdling::OnStnClickedStaticLon()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgVIdling::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CTime now = CTime::GetCurrentTime();
	CString str;
	int r;

	for (int i=0;i<6;i++)
	{
		srand(int(now.GetTime()));
		r = 999 + rand()%(999);
		str.Format(_T("%d"),r);
		m_dlgShowData[i].fSetData(str);
	}	

	this->Invalidate();

	CDialog::OnTimer(nIDEvent);
}

//void CDlgVIdling::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	
//	CDialog::OnLButtonDblClk(nFlags, point);
//}

//void CDlgVIdling::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CDialog::OnLButtonDown(nFlags, point);
//}

void CDlgVIdling::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}

// 是否自动刷新数据
int CDlgVIdling::fEnableAutoRefresh(bool bEnable)
{
	if (bEnable)
		SetTimer(1,1000,NULL);
	else
		KillTimer(1);
	return 0;
}

void CDlgVIdling::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CDC *pDC =  this->GetDC();
	if (m_memdcBkBmp.m_hDC != NULL)
	{	
		CString strDate;
		CString strTime;
		CString strWeek;
		CString strLon;
		CString strLon1;
		CString strLat;
		CString strLat1;		
		CTime time = CTime::GetCurrentTime();
		strTime.Format(_T("%02d:%02d"),time.GetHour(),time.GetMinute());
		strDate.Format(_T("%04d-%02d-%02d"),time.GetYear(),time.GetMonth(),time.GetDay());
		switch (time.GetDayOfWeek())
		{
		case 1:
			strWeek = _T("星期日");
			break;
		case 2:
			strWeek = _T("星期一");
			break;
		case 3:
			strWeek = _T("星期二");
			break;
		case 4:
			strWeek = _T("星期三");
			break;
		case 5:
			strWeek = _T("星期四");
			break;
		case 6:
			strWeek = _T("星期五");
			break;
		case 7:
			strWeek = _T("星期六");
			break;		
		}
		strLon = _T("114");
		strLon1 = _T("53");
		strLat = _T("089");
		strLat1 = _T("35");

		CRect rect; 
		CDC   memDC; 
		GetWindowRect(&rect); 	
		memDC.CreateCompatibleDC(pDC); 	

		CBitmap* pOldMemBmp = NULL; 
		pOldMemBmp = memDC.SelectObject(&m_cBitmapBkBmp);
		memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_memdcBkBmp,0,0,SRCCOPY);

		memDC.SetBkMode(TRANSPARENT);
		CFont fontText;
		VERIFY(fontText.CreateFont(
			50,                        // nHeight
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
			_T("Arial Rounded MT")));              // lpszFacename
		CRect rc;
		m_staticTime.GetWindowRect(&rc);
		ScreenToClient(&rc);
		DWORD dwStyle = m_staticTime.GetStyle();
		int nDTFlags = 0;
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
		memDC.SelectObject(&fontText); 
		fontText.DeleteObject();
		memDC.SetTextColor(RGB(255,255,255));   //设置字体颜色白色  
		memDC.DrawText(strTime, -1, &rc, nDTFlags);

		m_staticDate.GetWindowRect(&rc);
		ScreenToClient(&rc);
		VERIFY(fontText.CreateFont(
			20,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL, //FW_NORMAL,加粗                // nWeight
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
		memDC.DrawText(strDate, -1, &rc, nDTFlags);

		m_staticWeek.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(strWeek, -1, &rc, nDTFlags);

		VERIFY(fontText.CreateFont(
			30,                        // nHeight
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
		dwStyle = m_staticLon.GetStyle();
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
		m_staticLon.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(strLon, -1, &rc, nDTFlags);

		m_staticLon1.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(strLon1, -1, &rc, nDTFlags);

		m_staticLat.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(strLat, -1, &rc, nDTFlags);

		m_staticLat1.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(strLat1, -1, &rc, nDTFlags);

		//将背景位图复制到窗口客户区 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		if(pOldMemBmp)   
			memDC.SelectObject(pOldMemBmp); 

		DeleteObject(pOldMemBmp);
		DeleteObject(fontText);
		DeleteDC(memDC);
	}
}
