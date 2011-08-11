#pragma once


// CDlgVDetail 对话框

class CDlgVDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgVDetail)

public:
	CDlgVDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVDetail();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_DETAIL };
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
	afx_msg void OnClose();
	afx_msg void OnPaint();
};
