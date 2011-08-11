#pragma once
#include "afxwin.h"


//#include <Imaging.h>
// CDlgVShowData 对话框

class CDlgVShowData : public CDialog
{
	DECLARE_DYNAMIC(CDlgVShowData)

public:
	CDlgVShowData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVShowData();

// 对话框数据
	enum { IDD = IDD_DIALOG_V_SHOW_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	CString m_strData;							// 即时显示数据
	CString m_strText;							// 单位说明文本
	CStatic m_staticData;						// 即时数值	
	CStatic m_staticText;						// 单位文本

	BOOL	m_bUnitVisiable;					//无单位背景情况

	CBitmap m_cBitmapBkBmp;						//背景图片
	CDC		m_memdcBkBmp;						//背景图片DC

	int		m_iResID;

	//IImagingFactory *m_pIImgFactory;
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 设置显示数据
	int fSetData(CString strData);
	// 设置单位文本信息
	int fSetText(CString strText);
	// 设置窗口背景图片
	int fSetBkBmpFile(CString strBmpFile);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 是否显示单位
	int fSetUnitVisible(bool bUnitVisible);
	afx_msg void OnClose();
	int fSetBkBmpFile(int iResID);
	afx_msg void OnPaint();
};
