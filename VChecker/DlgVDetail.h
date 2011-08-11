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
	CString			m_strBkBmpFile;				//对话框背景图片

	HBITMAP			m_hBkBmp;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
};
