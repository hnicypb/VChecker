#pragma once


// CDlgVMain �Ի���

class CDlgVMain : public CDialog
{
	DECLARE_DYNAMIC(CDlgVMain)

public:
	CDlgVMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVMain();

// �Ի�������
	enum { IDD = IDD_DIALOG_V_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
