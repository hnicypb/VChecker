#pragma once
#include "afxwin.h"


// CDlgVCruise �Ի���

class CDlgVCruise : public CDialog
{
	DECLARE_DYNAMIC(CDlgVCruise)

public:
	CDlgVCruise(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVCruise();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_CRUISE };
protected:
	CRect			m_rectShowData[7];			//������ʾλ��
	int				m_iShowDataBkImg[7];		//���ݿ鱳��ͼƬ������Ҳ���ǵ�λ
	CString			m_strShowDataText[7];		//���ݿ��ı���ʾ��Ϣ
	CDlgVShowData	m_dlgShowData[6];			//������ʾ��

	CBitmap m_cBitmapBkBmp;						//����ͼƬ
	CDC		m_memdcBkBmp;						//����ͼƬDC

	CPoint			m_pointCircle;			//Բ��
	WORD			m_dRaduis;				//�뾶

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ��ʼ���ؼ�����
	int fInitData(void);
	CStatic m_staticTime;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// ʱ��
	CStatic m_staticSS;
	CString m_strSS;
	afx_msg void OnStnClickedStaticSs();
	// ��ָ����ͼ�굽������
	int fDrawCompass(CDC * dc);
	// �Ƿ��Զ�ˢ������
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
};
