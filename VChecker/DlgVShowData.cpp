// DlgVShowData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VChecker.h"
#include "DlgVShowData.h"
#include "VCheckerClsGlobal.h"


// CDlgVShowData �Ի���

IMPLEMENT_DYNAMIC(CDlgVShowData, CDialog)

CDlgVShowData::CDlgVShowData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVShowData::IDD, pParent)
	, m_strData(_T(""))
	, m_strText(_T(""))
	, m_bUnitVisiable(TRUE)
{
	
}

CDlgVShowData::~CDlgVShowData()
{
	DeleteDC(m_memdcBkBmp);
	DeleteObject(m_cBitmapBkBmp);
}

void CDlgVShowData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DATA, m_strData);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_strText);
	DDX_Control(pDX, IDC_STATIC_DATA, m_staticData);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_staticText);
}

BOOL CDlgVShowData::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetTimer(1,1000,NULL);	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgVShowData, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgVShowData ��Ϣ�������

BOOL CDlgVShowData::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

// //������ʾ����
int CDlgVShowData::fSetData(CString strData)
{
	if(m_strData != strData)
	{
		m_strData = strData;
		this->Invalidate();
	}
	
	return 0;
}

// //���õ�λ�ı���Ϣ
int CDlgVShowData::fSetText(CString strText)
{
	if(m_strText != strText)
	{
		m_strText = strText;
		UpdateData(FALSE);
	}
	
	return 0;
}

// ���ô��ڱ���ͼƬ
int CDlgVShowData::fSetBkBmpFile(CString strBmpFile)
{
	return 0;
}

void CDlgVShowData::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnTimer(nIDEvent);
}


// �Ƿ���ʾ��λ
int CDlgVShowData::fSetUnitVisible(bool bUnitVisible)
{
	CRect rectText;
	m_staticText.GetWindowRect(&rectText);
	ScreenToClient(&rectText);

	CRect rectData;
	m_staticData.GetWindowRect(&rectData);
	ScreenToClient(&rectData);

	if(!m_bUnitVisiable)
		m_staticData.MoveWindow(rectData.left,rectData.top,rectText.Width() - 10,rectData.Height());
	else
		m_staticData.MoveWindow(rectData.left,rectData.top,rectText.Width() - 30,rectData.Height());
	return 0;
}

void CDlgVShowData::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

;	CDialog::OnClose();
}

int CDlgVShowData::fSetBkBmpFile(int iResID)
{
	m_iResID = iResID;	
	HBITMAP hBmpBk = LoadBitmap(g_hResDll,MAKEINTRESOURCE(iResID));
	
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

	return 0;
}

void CDlgVShowData::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CDC *pDC =  this->GetDC();
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		CRect rc;
		m_staticData.GetWindowRect(&rc);
		ScreenToClient(&rc);

		DWORD dwStyle = m_staticData.GetStyle();

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

		//��������
		CFont fontData;
		CFont *fontOldData = NULL;
		VERIFY(fontData.CreateFont(
			35,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL, //FW_NORMAL,�Ӵ�                // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("����")));              // lpszFacename

		fontOldData = memDC.SelectObject(&fontData); 
		memDC.SetTextColor(RGB(255,255,255));   //����������ɫ��ɫ  
		memDC.DrawText(m_strData, -1, &rc, nDTFlags);
		if (fontOldData)
			memDC.SelectObject(&fontOldData);

		CFont fontText;
		CFont* fontOldText = NULL;
		VERIFY(fontText.CreateFont(
			15,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL, //FW_NORMAL,�Ӵ�                // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("����")));              // lpszFacename
		m_staticText.GetWindowRect(&rc);
		ScreenToClient(&rc);

		dwStyle = m_staticText.GetStyle();

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
		fontOldText = memDC.SelectObject(&fontText); 
		memDC.SetTextColor(RGB(255,255,255));   //����������ɫ��ɫ  
		memDC.DrawText(m_strText, -1, &rc, nDTFlags);
		if (fontOldText)
			memDC.SelectObject(&fontOldText);

		//������λͼ���Ƶ����ڿͻ��� 
		pDC-> BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY); 

		DeleteObject(pOldMemBmp);
		DeleteObject(fontText);
		DeleteObject(fontData);
		DeleteDC(memDC);

		ReleaseDC(pDC);
	}
}
