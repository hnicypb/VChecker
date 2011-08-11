#pragma once
#include "afxwin.h"


//#include <Imaging.h>
// CDlgVShowData �Ի���

class CDlgVShowData : public CDialog
{
	DECLARE_DYNAMIC(CDlgVShowData)

public:
	CDlgVShowData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVShowData();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_SHOW_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	CString m_strData;							// ��ʱ��ʾ����
	CString m_strText;							// ��λ˵���ı�
	CStatic m_staticData;						// ��ʱ��ֵ	
	CStatic m_staticText;						// ��λ�ı�

	BOOL	m_bUnitVisiable;					//�޵�λ�������

	CBitmap m_cBitmapBkBmp;						//����ͼƬ
	CDC		m_memdcBkBmp;						//����ͼƬDC

	int		m_iResID;

	//IImagingFactory *m_pIImgFactory;
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// ������ʾ����
	int fSetData(CString strData);
	// ���õ�λ�ı���Ϣ
	int fSetText(CString strText);
	// ���ô��ڱ���ͼƬ
	int fSetBkBmpFile(CString strBmpFile);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �Ƿ���ʾ��λ
	int fSetUnitVisible(bool bUnitVisible);
	afx_msg void OnClose();
	int fSetBkBmpFile(int iResID);
	afx_msg void OnPaint();
};
