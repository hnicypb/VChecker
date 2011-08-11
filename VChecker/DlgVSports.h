#pragma once
#include "afxwin.h"

// CDlgVSports 对话框

class CDlgVSports : public CDialog
{
	DECLARE_DYNAMIC(CDlgVSports)

public:
	CDlgVSports(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVSports();

protected:
	CRect			m_rectShowData[2];			//界面显示位置
	int				m_iShowDataBkImg[2];		//数据块背景图片索引，也就是单位
	CString			m_strShowDataText[2];		//数据块文本显示信息
	CDlgVShowData	m_dlgShowData[2];			//数据显示块

	CBitmap m_cBitmapBkBmp;						//背景图片
	CDC		m_memdcBkBmp;						//背景图片DC

	CPoint			m_pointCircleCs;			//车速圆心
	CPoint			m_pointCircleZs;			//转速圆心
	WORD			m_dCsRaduis;				//车速半径
	WORD			m_dZsRaduis;				//转速半径

// 对话框数据
	enum { IDD = IDD_DIALOG_V_SPORTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// 初始化竞技界面数据
	int fInitData(void);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	// 车速
	CStatic m_staticCs;
	// 转速
	CStatic m_staticZs;
	CString m_strCs;
	CString m_strZs;	
	// 车速指针
	CStatic m_staticCsPointer;
	// 转速指针
	CStatic m_staticZsPointer;
public:
	// 是否自动刷新数据
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
