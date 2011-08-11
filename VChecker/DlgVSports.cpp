// DlgVSports.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVSports.h"
#include "VCheckerClsGlobal.h"

#include "VCheckerDlg.h"


// CDlgVSports �Ի���

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

	//��������ؼ�
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

	//��ʼ������ͼƬDC
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


// ��ʼ��������������

int CDlgVSports::fInitData(void)
{
	CVCheckerClsGlobal clsGlobal;
	m_iShowDataBkImg[0] = RES_BMP_UNIT_BFH;
	m_strShowDataText[0] = _T("����������");
	m_rectShowData[0] =  CRect(178,23,302,83);		

	m_iShowDataBkImg[1] = RES_BMP_UNIT_D;
	m_strShowDataText[1] = _T("�����ǰ��");
	m_rectShowData[1] =	CRect(178,160,302,220);	

	m_pointCircleCs = CPoint(97,123);
	m_pointCircleZs = CPoint(383,123);

	m_dCsRaduis = m_dZsRaduis = 43;

	return 0;
}

void CDlgVSports::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_pDlg->fSetPanel(point);
	CDialog::OnLButtonUp(nFlags, point);
}


// �Ƿ��Զ�ˢ������
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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
			FW_BOLD, //FW_NORMAL,�Ӵ�                // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("����")));              // lpszFacename
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

		//��ָ�뵽����
		////�Ƕ�(60-320) /�̶�(0-240)	/60��	
		int iPos = _ttoi(m_strCs);					//�̶�ֵ
		float fIndex = float((iPos)/4);					//�̶�����
		double dAngle = (60+fIndex*4);				//�Ƕ�����

		CVCheckerClsGlobal clsGlobal;
		clsGlobal.fDrawPoint(&memDC,m_pointCircleCs,m_dCsRaduis,dAngle);

		////�Ƕ�(70-320) /�̶�(0-100)	/100��	
		fIndex = float(_ttoi(m_strZs)/100);			//�̶�����	
		dAngle = (70+fIndex*2.48);				//�Ƕ�����
		clsGlobal.fDrawPoint(&memDC,m_pointCircleZs,m_dZsRaduis,dAngle);

		//double dRectAngle =  (double)((dAngle+100)*PI/180.0);	//����Ƕ�	
		//double dRotateAngle =  2 * PI - (dAngle) * Rad;					
		//m_dZsRaduis = m_dZsRaduis + 30;
		//memDC.Ellipse(m_pointCircleZs.x+m_dZsRaduis,m_pointCircleZs.y+m_dZsRaduis,m_pointCircleZs.x-m_dZsRaduis,m_pointCircleZs.y-m_dZsRaduis);
		//m_dZsRaduis = m_dZsRaduis - 30;

		//������λͼ���Ƶ����ڿͻ��� 
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}
