#pragma once


// CDlgVConfig �Ի���

class CDlgVConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgVConfig)

public:
	CDlgVConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_CONFIG };

protected:
	CBitmap m_cBitmapBkBmp;						//����ͼƬ
	CDC		m_memdcBkBmp;						//����ͼƬDC

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
