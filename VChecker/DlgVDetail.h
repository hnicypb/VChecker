#pragma once


// CDlgVDetail �Ի���

class CDlgVDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgVDetail)

public:
	CDlgVDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVDetail();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_DETAIL };
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
	afx_msg void OnClose();
	afx_msg void OnPaint();
};
