#pragma once


// CDlgVConfig 对话框

class CDlgVConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgVConfig)

public:
	CDlgVConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_CONFIG };

protected:
	CBitmap m_cBitmapBkBmp;						//背景图片
	CDC		m_memdcBkBmp;						//背景图片DC

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
