#pragma once


// CDlgVMain 对话框

class CDlgVMain : public CDialog
{
	DECLARE_DYNAMIC(CDlgVMain)

public:
	CDlgVMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVMain();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
