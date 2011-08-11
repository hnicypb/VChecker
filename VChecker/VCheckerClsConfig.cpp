#include "StdAfx.h"
#include "VCheckerClsConfig.h"
#include "Markup.h"
#include "VCheckerClsGlobal.h"

CVCheckerClsConfig::CVCheckerClsConfig(void)
{
	m_strConfigFile = _T("");	
}

CVCheckerClsConfig::CVCheckerClsConfig(CString strFileName)
{
	m_strConfigFile = strFileName;
}

CVCheckerClsConfig::~CVCheckerClsConfig(void)
{
}

// 初始化配置文件
int CVCheckerClsConfig::fInitConfig(void)
{
	if (m_strConfigFile == _T(""))
		return CONFIG_ERR_FIND_FILE;

	CVCheckerClsGlobal clsGlobal;

	CMarkup xml;
	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"));//添加XML头	

	//获取硬件系统信息
	xml.AddElem(_T("System_Info"));
	xml.AddAttrib(_T("Resolution"),clsGlobal.fGetScreenResolution());
	xml.AddAttrib(_T("Language"),_T("zh-cn"));
	xml.OutOfElem();	

	//======800X480分辨率环境下的设置Begin======
	xml.AddChildElem(_T("480X272"));
	xml.IntoElem();
	xml.AddChildElem(_T("Defualt_Size"),430);
	xml.OutOfElem();	
	//======平台环境下的设置End======

	//======多语言设置Begin======
	xml.AddChildElem(_T("Language"));
	xml.IntoElem();	

	xml.AddChildElem(_T("IDOK"));
	xml.IntoElem();
	xml.AddAttrib(_T("zh-cn"),_T("确定"));
	xml.AddAttrib(_T("en-us "),_T("Ok"));
	xml.OutOfElem();

	xml.AddChildElem(_T("IDCANCEL"));
	xml.IntoElem();
	xml.AddAttrib(_T("zh-cn"),_T("取消"));
	xml.AddAttrib(_T("en-us "),_T("Cancel"));
	xml.OutOfElem();

	xml.OutOfElem();
	//======多语言设置End======

	//======主界面设置Begin======
	xml.AddChildElem(_T("Main"));
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	//======主界面设置End======

	//======怠速界面设置Begin======
	xml.AddChildElem(_T("Idling"));
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));

	xml.AddChildElem(_T("LeftUp"));					//左上数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("Up"));						//左边数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("LeftDown"));				//左下数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("RightUp"));				//右上数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("Right"));					//右边数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("RightDown"));				//右下数据信息
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.OutOfElem();
	//======怠速界面设置End======

	xml.Save(m_strConfigFile);
	return 0;
}

// 设置配置文件
int CVCheckerClsConfig::fSetConfigFile(CString strFileName)
{
	m_strConfigFile = strFileName;
	return 0;
}

int CVCheckerClsConfig::fCheckConfigFile(void)
{
	return 0;
}

// 根据配置索引获取配置信息
CString CVCheckerClsConfig::fGetConfigData(int nConfigIndex)
{
	if (m_strConfigFile == _T(""))
		return _T("");

	CMarkup xml;
	BOOL bLoad = FALSE;
	bLoad = xml.Load(m_strConfigFile);
	if (!bLoad)
		return _T(""); 

	xml.ResetPos();
	while ( xml.FindChildElem(_T("System_Config")))
	{
		xml.IntoElem();
		
		//xml.ResetMainPos();
		//xml.FindChildElem( "NAME" );
		////	xml.FindChildElem();
		//CString csName = xml.GetChildData();
		//AfxMessageBox(csName);

		//xml.ResetMainPos(); //注意复位
		//xml.FindChildElem( "SN" );
		////	xml.FindChildElem();
		//CString csSN = xml.GetChildData();
		//AfxMessageBox(csSN);

		xml.OutOfElem();
	}	

	return CString();
}
