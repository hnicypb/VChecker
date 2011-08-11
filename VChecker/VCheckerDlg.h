// VCheckerDlg.h : 头文件
//

#pragma once
#include "VCheckerClsGlobal.h"
#include "VCheckerClsConfig.h"

#include "DlgVIdling.h"
#include "DlgVSports.h"
#include "DlgVCruise.h"
#include "DlgVDetail.h"
#include "DlgVConfig.h"

// CVCheckerDlg 对话框
class CVCheckerDlg : public CDialog
{
// 构造
public:
	CVCheckerDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_VCHECKER_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	int				m_iPanelIndex;	//当前界面索引

	CDlgVIdling		m_DlgIdling;	//怠速界面
	CDlgVSports		m_DlgSports;	//竞技界面
	CDlgVCruise		m_DlgCruise;	//巡航界面
	CDlgVDetail		m_DlgDetail;	//行程明细
	CDlgVConfig		m_DlgConfig;	//系统设置

	CTime			m_timeBegin;	//本次行驶开始时间
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 切换界面
	int fSetPanel(CPoint point);
	// 获取程序启动时间
	CTime fGetStartTime(void);
};
