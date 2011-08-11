// DlgVCruise.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVCruise.h"


// CDlgVCruise 对话框

IMPLEMENT_DYNAMIC(CDlgVCruise, CDialog)

CDlgVCruise::CDlgVCruise(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVCruise::IDD, pParent)
	, m_strSS(_T(""))
{
}

CDlgVCruise::~CDlgVCruise()
{	
	DeleteDC(m_memdcBkBmp);
	DeleteObject(m_cBitmapBkBmp);
}

void CDlgVCruise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticTime);
	DDX_Control(pDX, IDC_STATIC_SS, m_staticSS);
	DDX_Text(pDX, IDC_STATIC_SS, m_strSS);
}



BEGIN_MESSAGE_MAP(CDlgVCruise, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(IDC_STATIC_SS, &CDlgVCruise::OnStnClickedStaticSs)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// 初始化控件界面
int CDlgVCruise::fInitData(void)
{
	CVCheckerClsGlobal clsGlobal;

	m_iShowDataBkImg[0] = RES_BMP_UNIT;
	m_strShowDataText[0] = clsGlobal.fGetRes(IDS_STRING_BCXSSJ);	//_T("本次行驶时间"); 
	m_rectShowData[0] =  CRect(16,20,141,80);			

	m_iShowDataBkImg[1] = RES_BMP_UNIT_SS;
	m_strShowDataText[1] = clsGlobal.fGetRes(IDS_STRING_BCPJSD);	//_T("本次平均速度");
	m_rectShowData[1] =	CRect(16,90,141,150);	

	m_iShowDataBkImg[2] = RES_BMP_UNIT_WD;
	m_strShowDataText[2] = clsGlobal.fGetRes(IDS_STRING_FDJSW);		//_T("发动机水温");
	m_rectShowData[2] =	CRect(16,160,141,220);	

	m_iShowDataBkImg[3] = RES_BMP_UNIT_LC;
	m_strShowDataText[3] = clsGlobal.fGetRes(IDS_STRING_BCXSLC);	//_T("本次行驶里程");
	m_rectShowData[3] = CRect(339,20,463,80);

	m_iShowDataBkImg[4] = RES_BMP_UNIT_PJYH;
	m_strShowDataText[4] = clsGlobal.fGetRes(IDS_STRING_BCPJYH);	//_T("本次平均油耗");
	m_rectShowData[4] = CRect(339,90,463,150);

	m_iShowDataBkImg[5] = RES_BMP_UNIT_JSYH;
	m_strShowDataText[5] = clsGlobal.fGetRes(IDS_STRING_JSYH);		//_T("即时油耗");
	m_rectShowData[5] = CRect(339,160,463,220);

	m_pointCircle = CPoint(240,145);
	m_dRaduis = 43;

	return 0;
}


BOOL CDlgVCruise::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fInitData();

	//创建界面控件
	for (int i=0;i<6;i++)
	{
		m_dlgShowData[i].Create(IDD_DIALOG_V_SHOW_DATA,this);		
		m_dlgShowData[i].fSetBkBmpFile(m_iShowDataBkImg[i]);
		m_dlgShowData[i].fSetText(m_strShowDataText[i]);		
		m_dlgShowData[i].MoveWindow(m_rectShowData[i]);
		m_dlgShowData[i].ShowWindow(SW_SHOW);
	}

	m_dlgShowData[0].fSetUnitVisible(FALSE);
	m_dlgShowData[0].fSetData(_T("01:51"));
	m_dlgShowData[1].fSetData(_T("84.1"));
	m_dlgShowData[2].fSetData(_T("71.1"));
	m_dlgShowData[3].fSetData(_T("9.8"));
	m_dlgShowData[4].fSetData(_T("5.0"));
	m_dlgShowData[5].fSetData(_T("0.8"));

	fEnableAutoRefresh(TRUE);

	//初始化背景图片DC
	HBITMAP hBmpBk = LoadBitmap(g_hResDll,MAKEINTRESOURCE(RES_BMP_MAIN_XH));
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

// CDlgVCruise 消息处理程序

BOOL CDlgVCruise::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgVCruise::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CTime now = CTime::GetCurrentTime();
	CString str;
	int r;

	CTimeSpan timespan = now - g_pDlg->fGetStartTime();
	str.Format(_T("%02d:%02d"),timespan.GetHours(),timespan.GetMinutes());
	m_dlgShowData[0].fSetData(str);

	for (int i=1;i<6;i++)
	{
		srand(int(now.GetTime()));
		r = 999 + rand()%(999);
		str.Format(_T("%d"),r);
		m_dlgShowData[i].fSetData(str);
	}	

	if (_ttoi(m_strSS)<240)
	{
		m_strSS.Format(_T("%d"),_ttoi(m_strSS)+3);		
	}
	else
	{
		m_strSS = _T("0");
	}

	this->Invalidate();
	CDialog::OnTimer(nIDEvent);
}
void CDlgVCruise::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgVCruise::OnStnClickedStaticSs()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 画指南针图标到界面上
int CDlgVCruise::fDrawCompass(CDC * dc)
{		
	CPoint ptTemp[3];		
	ptTemp[0].x = m_pointCircle.x;	
	ptTemp[0].y = m_pointCircle.y+8;	

	ptTemp[1].x = (int)(m_pointCircle.x+8*cos((double)(180*PI/180.0)));
	ptTemp[1].y = (int)(m_pointCircle.y+8*sin((double)(180*PI/180.0)));		

	ptTemp[2].x = (int)(m_pointCircle.x+25*cos((double)(270*PI/180.0)));
	ptTemp[2].y = (int)(m_pointCircle.y+25*sin((double)(270*PI/180.0)));

	CPen penBound(0,1,RGB(231,31,25));
	CPen* pOldPen = dc->SelectObject(&penBound);
	dc->SelectObject(penBound);
	CBrush brushBound(RGB(231,31,25));
	CBrush* pOldBrush = dc->SelectObject(&brushBound);
	dc->SelectObject(brushBound);

	dc->Polygon(ptTemp,3);	

	dc->SelectObject(pOldPen);
	dc->SelectObject(pOldBrush);	

	DeleteObject(penBound);
	DeleteObject(brushBound);	

	CPoint ptTemp2[3];	
	ptTemp2[0].x = m_pointCircle.x;	
	ptTemp2[0].y = m_pointCircle.y+8;	

	ptTemp2[1].x = (int)(m_pointCircle.x+25*cos((double)(270*PI/180.0)));
	ptTemp2[1].y = (int)(m_pointCircle.y+25*sin((double)(270*PI/180.0)));		

	ptTemp2[2].x = (int)(m_pointCircle.x+8*cos((double)(360*PI/180.0)));	
	ptTemp2[2].y = (int)(m_pointCircle.y+8*sin((double)(360*PI/180.0)));	

	CPen penBound2(0,1,RGB(153,0,0));
	CPen* pOldPen2 = dc->SelectObject(&penBound2);
	dc->SelectObject(penBound2);

	CBrush brushBound2(RGB(153,0,0));
	CBrush* pOldBrush2 = dc->SelectObject(&brushBound2);
	dc->SelectObject(brushBound2);

	dc->Polygon(ptTemp2,3);

	dc->SelectObject(pOldPen2);
	dc->SelectObject(pOldBrush2);	

	DeleteObject(penBound2);
	DeleteObject(brushBound2);	

	CBrush brushBound3(RGB(161,29,131));
	CBrush* pOldBrush3 = dc->SelectObject(&brushBound3);
	dc->SelectObject(brushBound3);
	dc->Ellipse(m_pointCircle.x+5,m_pointCircle.y+5,m_pointCircle.x-5,m_pointCircle.y-5);
	DeleteObject(brushBound3);	

	CBrush brushBound4(RGB(55,80,192));
	CBrush* pOldBrush4 = dc->SelectObject(&brushBound4);
	dc->SelectObject(brushBound4);
	dc->Ellipse(m_pointCircle.x+3,m_pointCircle.y+3,m_pointCircle.x-3,m_pointCircle.y-3);
	DeleteObject(brushBound4);	

	return 0;
}

// 是否自动刷新数据
int CDlgVCruise::fEnableAutoRefresh(bool bEnable)
{
	if (bEnable)
		SetTimer(1,1000,NULL);
	else
		KillTimer(1);
	return 0;
}

void CDlgVCruise::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC =  this->GetDC();
	
	if (m_memdcBkBmp.m_hDC != NULL)
	{
		CString strTime;	
		CTime time = CTime::GetCurrentTime();
		strTime.Format(_T("%02d:%02d"),time.GetHour(),time.GetMinute());		

		CRect rect; 
		CDC   memDC; 
		HBITMAP hOldBitmap = NULL;	

		GetWindowRect(&rect); 	
		memDC.CreateCompatibleDC(pDC); 	

		CBitmap* pOldMemBmp = NULL; 
		pOldMemBmp = memDC.SelectObject(&m_cBitmapBkBmp);
		memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_memdcBkBmp,0,0,SRCCOPY);

		memDC.SetBkMode(TRANSPARENT);	
		CFont fontText;
		VERIFY(fontText.CreateFont(
			43,                        // nHeight
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

		memDC.SetTextColor(RGB(249,223,4));		

		m_staticSS.GetWindowRect(&rc);
		ScreenToClient(&rc);
		memDC.DrawText(m_strSS, -1, &rc, nDTFlags);	


		//画指针到窗口
		////角度(60-320) /刻度(0-240)	/60格	
		int iPos = _ttoi(m_strSS);					//刻度值
		float fIndex = float((iPos)/4);					//刻度索引
		double dAngle = (60+fIndex*4);				//角度索引

		CVCheckerClsGlobal clsGlobal;
		clsGlobal.fDrawPoint(&memDC,m_pointCircle,m_dRaduis,dAngle,18,-10);
		fDrawCompass(&memDC);

		//将背景位图复制到窗口客户区 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		if(pOldMemBmp)   
			memDC.SelectObject(pOldMemBmp); 

		DeleteObject(pOldMemBmp);
		DeleteObject(fontText);
		DeleteDC(memDC);		
	}
}
