/*
创建:	Yipb	2011-08-02
说明:	怠速主界面
*/
#pragma once

#include "DlgVShowData.h"
#include "afxwin.h"
// CDlgVIdling 对话框

class CDlgVIdling : public CDialog
{
	DECLARE_DYNAMIC(CDlgVIdling)

public:
	CDlgVIdling(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVIdling();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_IDLING };

protected:
	CRect			m_rectShowData[7];			//界面显示位置
	int				m_iShowDataBkImg[7];		//数据块背景图片索引，也就是单位
	CString			m_strShowDataText[7];		//数据块文本显示信息
	CDlgVShowData	m_dlgShowData[6];			//数据显示块

	HBITMAP			m_hBkBmp;					//背景图片

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// 初始化怠速界面数据
	int fInitData(void);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedStaticLon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//日期时间
	CStatic m_staticTime;
	CStatic m_staticDate;
	CStatic m_staticWeek;
	//经纬度
	CStatic m_staticLon;
	CStatic m_staticLon1;
	CStatic m_staticLat;
	CStatic m_staticLat1;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 是否自动刷新数据
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
};
