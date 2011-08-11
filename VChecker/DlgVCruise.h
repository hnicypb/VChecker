#pragma once
#include "afxwin.h"


// CDlgVCruise 对话框

class CDlgVCruise : public CDialog
{
	DECLARE_DYNAMIC(CDlgVCruise)

public:
	CDlgVCruise(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVCruise();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_CRUISE };
protected:
	CRect			m_rectShowData[7];			//界面显示位置
	int				m_iShowDataBkImg[7];		//数据块背景图片索引，也就是单位
	CString			m_strShowDataText[7];		//数据块文本显示信息
	CDlgVShowData	m_dlgShowData[6];			//数据显示块

	CBitmap m_cBitmapBkBmp;						//背景图片
	CDC		m_memdcBkBmp;						//背景图片DC

	CPoint			m_pointCircle;			//圆心
	WORD			m_dRaduis;				//半径

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 初始化控件界面
	int fInitData(void);
	CStatic m_staticTime;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 时速
	CStatic m_staticSS;
	CString m_strSS;
	afx_msg void OnStnClickedStaticSs();
	// 画指南针图标到界面上
	int fDrawCompass(CDC * dc);
	// 是否自动刷新数据
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
};
