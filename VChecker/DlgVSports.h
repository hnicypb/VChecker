#pragma once
#include "afxwin.h"

// CDlgVSports �Ի���

class CDlgVSports : public CDialog
{
	DECLARE_DYNAMIC(CDlgVSports)

public:
	CDlgVSports(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVSports();

protected:
	CRect			m_rectShowData[2];			//������ʾλ��
	int				m_iShowDataBkImg[2];		//���ݿ鱳��ͼƬ������Ҳ���ǵ�λ
	CString			m_strShowDataText[2];		//���ݿ��ı���ʾ��Ϣ
	CDlgVShowData	m_dlgShowData[2];			//������ʾ��

	CBitmap m_cBitmapBkBmp;						//����ͼƬ
	CDC		m_memdcBkBmp;						//����ͼƬDC

	CPoint			m_pointCircleCs;			//����Բ��
	CPoint			m_pointCircleZs;			//ת��Բ��
	WORD			m_dCsRaduis;				//���ٰ뾶
	WORD			m_dZsRaduis;				//ת�ٰ뾶

// �Ի�������
	enum { IDD = IDD_DIALOG_V_SPORTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ��������������
	int fInitData(void);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	// ����
	CStatic m_staticCs;
	// ת��
	CStatic m_staticZs;
	CString m_strCs;
	CString m_strZs;	
	// ����ָ��
	CStatic m_staticCsPointer;
	// ת��ָ��
	CStatic m_staticZsPointer;
public:
	// �Ƿ��Զ�ˢ������
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
