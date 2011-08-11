/*
����:	Yipb	2011-08-02
˵��:	����������
*/
#pragma once

#include "DlgVShowData.h"
#include "afxwin.h"
// CDlgVIdling �Ի���

class CDlgVIdling : public CDialog
{
	DECLARE_DYNAMIC(CDlgVIdling)

public:
	CDlgVIdling(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVIdling();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_IDLING };

protected:
	CRect			m_rectShowData[7];			//������ʾλ��
	int				m_iShowDataBkImg[7];		//���ݿ鱳��ͼƬ������Ҳ���ǵ�λ
	CString			m_strShowDataText[7];		//���ݿ��ı���ʾ��Ϣ
	CDlgVShowData	m_dlgShowData[6];			//������ʾ��

	HBITMAP			m_hBkBmp;					//����ͼƬ

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ�����ٽ�������
	int fInitData(void);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedStaticLon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//����ʱ��
	CStatic m_staticTime;
	CStatic m_staticDate;
	CStatic m_staticWeek;
	//��γ��
	CStatic m_staticLon;
	CStatic m_staticLon1;
	CStatic m_staticLat;
	CStatic m_staticLat1;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// �Ƿ��Զ�ˢ������
	int fEnableAutoRefresh(bool bEnable);
	afx_msg void OnPaint();
};
