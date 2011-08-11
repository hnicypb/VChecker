// VCheckerDlg.h : ͷ�ļ�
//

#pragma once
#include "VCheckerClsGlobal.h"
#include "VCheckerClsConfig.h"

#include "DlgVIdling.h"
#include "DlgVSports.h"
#include "DlgVCruise.h"
#include "DlgVDetail.h"
#include "DlgVConfig.h"

// CVCheckerDlg �Ի���
class CVCheckerDlg : public CDialog
{
// ����
public:
	CVCheckerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_VCHECKER_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	int				m_iPanelIndex;	//��ǰ��������

	CDlgVIdling		m_DlgIdling;	//���ٽ���
	CDlgVSports		m_DlgSports;	//��������
	CDlgVCruise		m_DlgCruise;	//Ѳ������
	CDlgVDetail		m_DlgDetail;	//�г���ϸ
	CDlgVConfig		m_DlgConfig;	//ϵͳ����

	CTime			m_timeBegin;	//������ʻ��ʼʱ��
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// �л�����
	int fSetPanel(CPoint point);
	// ��ȡ��������ʱ��
	CTime fGetStartTime(void);
};
