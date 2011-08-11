// VCheckerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VChecker.h"
#include "VCheckerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVCheckerDlg 对话框
CVCheckerDlg *g_pDlg = 0;		//主界面对话框

CVCheckerDlg::CVCheckerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCheckerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
		
}

void CVCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVCheckerDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CVCheckerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CVCheckerDlg::OnBnClickedButtonExit)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CVCheckerDlg 消息处理程序

BOOL CVCheckerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_pDlg = this;

	m_DlgIdling.Create(IDD_DIALOG_V_IDLING,this);
	m_DlgIdling.ShowWindow(SW_SHOW);

	m_DlgSports.Create(IDD_DIALOG_V_SPORTS,this);
	m_DlgSports.ShowWindow(SW_HIDE);
	
	m_DlgCruise.Create(IDD_DIALOG_V_CRUISE,this);
	m_DlgCruise.ShowWindow(SW_HIDE);

	m_DlgDetail.Create(IDD_DIALOG_V_DETAIL,this);
	m_DlgDetail.ShowWindow(SW_HIDE);

	m_DlgConfig.Create(IDD_DIALOG_V_CONFIG,this);
	m_DlgConfig.ShowWindow(SW_HIDE);

	m_timeBegin = CTime::GetCurrentTime();	
		
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CVCheckerDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_VCHECKER_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_VCHECKER_DIALOG));
	}
}
#endif


void CVCheckerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CVCheckerClsGlobal clsGlobal;
	//AfxMessageBox(clsGlobal.fGenerateGuid());
	//AfxMessageBox(g_strAppPath);	
	//AfxMessageBox(clsGlobal.fGetScreenResolution());

	//CVCheckerClsConfig clsConfig;
	//clsConfig.fSetConfigFile(clsGlobal.fGetConfigPathFile());
	//clsConfig.fInitConfig();

}

void CVCheckerDlg::OnBnClickedButtonExit()
{	
	OnCancel();
}

void CVCheckerDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialog::OnLButtonDblClk(nFlags, point);
	CDialog::OnCancel();
}

// 切换界面
int CVCheckerDlg::fSetPanel(CPoint point)
{
	int iPanelID = 0;

	if (point.x>10 && point.x<80 && point.y>240 && point.y<270)
		iPanelID = PANEL_DSMS;
	else if (point.x>100 && point.x<170 && point.y>240 && point.y<270)
		iPanelID = PANEL_XHMS;
	else if (point.x>200 && point.x<270 && point.y>240 && point.y<270)
		iPanelID = PANEL_JJMS;
	else if (point.x>300 && point.x<370 && point.y>240 && point.y<270)
		iPanelID = PANEL_XCMX;
	else if (point.x>400 && point.x<470 && point.y>240 && point.y<270)
		iPanelID = PANEL_XTSZ;
	else if (point.x==0 && point.y==0)
		iPanelID = -1;

	if (iPanelID == m_iPanelIndex)
		return 0;
	
	m_iPanelIndex = iPanelID;
	switch (iPanelID)
	{
	case PANEL_LOGO:
		{			
		}
		break;
	case PANEL_MAIN:
		{
		}
		break;
	case PANEL_INFO:
		{
		}
		break;
	case PANEL_DSMS:
		{
			m_DlgIdling.ShowWindow(SW_SHOW);
			m_DlgSports.ShowWindow(SW_HIDE);
			m_DlgCruise.ShowWindow(SW_HIDE);
			m_DlgDetail.ShowWindow(SW_HIDE);
			m_DlgConfig.ShowWindow(SW_HIDE);

			m_DlgIdling.Invalidate();
			m_DlgIdling.fEnableAutoRefresh(TRUE);
			m_DlgSports.fEnableAutoRefresh(FALSE);
			m_DlgCruise.fEnableAutoRefresh(FALSE);
		}
		break;
	case PANEL_JJMS:
		{
			m_DlgIdling.ShowWindow(SW_HIDE);
			m_DlgSports.ShowWindow(SW_SHOW);
			m_DlgCruise.ShowWindow(SW_HIDE);
			m_DlgDetail.ShowWindow(SW_HIDE);

			m_DlgIdling.fEnableAutoRefresh(FALSE);
			m_DlgSports.Invalidate();
			m_DlgSports.fEnableAutoRefresh(TRUE);
			m_DlgCruise.fEnableAutoRefresh(FALSE);
		}
		break;
	case PANEL_XHMS:
		{
			m_DlgIdling.ShowWindow(SW_HIDE);
			m_DlgSports.ShowWindow(SW_HIDE);
			m_DlgCruise.Invalidate();
			m_DlgCruise.ShowWindow(SW_SHOW);
			m_DlgDetail.ShowWindow(SW_HIDE);

			m_DlgIdling.fEnableAutoRefresh(FALSE);
			m_DlgSports.fEnableAutoRefresh(FALSE);
			m_DlgCruise.fEnableAutoRefresh(TRUE);
		}
		break;
	case PANEL_XCMX:
		{			
			m_DlgIdling.ShowWindow(SW_HIDE);
			m_DlgSports.ShowWindow(SW_HIDE);
			m_DlgCruise.ShowWindow(SW_HIDE);
			m_DlgDetail.Invalidate();
			m_DlgDetail.ShowWindow(SW_SHOW);

			m_DlgIdling.fEnableAutoRefresh(FALSE);
			m_DlgSports.fEnableAutoRefresh(FALSE);
			m_DlgCruise.fEnableAutoRefresh(FALSE);
		}
		break;
	case PANEL_XTSZ:
		{
			m_DlgIdling.ShowWindow(SW_HIDE);
			m_DlgSports.ShowWindow(SW_HIDE);
			m_DlgCruise.ShowWindow(SW_HIDE);
			m_DlgDetail.ShowWindow(SW_HIDE);
			m_DlgConfig.Invalidate();
			m_DlgConfig.ShowWindow(SW_SHOW);			

			m_DlgIdling.fEnableAutoRefresh(FALSE);
			m_DlgSports.fEnableAutoRefresh(FALSE);
			m_DlgCruise.fEnableAutoRefresh(FALSE);
		}
		break;
	case -1:
		{
	
			CDialog::OnCancel();
		}
		break;
	}
	return 0;
}

// 获取程序启动时间
CTime CVCheckerDlg::fGetStartTime(void)
{
	return m_timeBegin;
}
