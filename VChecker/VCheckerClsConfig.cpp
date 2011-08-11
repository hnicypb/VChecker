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

// ��ʼ�������ļ�
int CVCheckerClsConfig::fInitConfig(void)
{
	if (m_strConfigFile == _T(""))
		return CONFIG_ERR_FIND_FILE;

	CVCheckerClsGlobal clsGlobal;

	CMarkup xml;
	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"));//���XMLͷ	

	//��ȡӲ��ϵͳ��Ϣ
	xml.AddElem(_T("System_Info"));
	xml.AddAttrib(_T("Resolution"),clsGlobal.fGetScreenResolution());
	xml.AddAttrib(_T("Language"),_T("zh-cn"));
	xml.OutOfElem();	

	//======800X480�ֱ��ʻ����µ�����Begin======
	xml.AddChildElem(_T("480X272"));
	xml.IntoElem();
	xml.AddChildElem(_T("Defualt_Size"),430);
	xml.OutOfElem();	
	//======ƽ̨�����µ�����End======

	//======����������Begin======
	xml.AddChildElem(_T("Language"));
	xml.IntoElem();	

	xml.AddChildElem(_T("IDOK"));
	xml.IntoElem();
	xml.AddAttrib(_T("zh-cn"),_T("ȷ��"));
	xml.AddAttrib(_T("en-us "),_T("Ok"));
	xml.OutOfElem();

	xml.AddChildElem(_T("IDCANCEL"));
	xml.IntoElem();
	xml.AddAttrib(_T("zh-cn"),_T("ȡ��"));
	xml.AddAttrib(_T("en-us "),_T("Cancel"));
	xml.OutOfElem();

	xml.OutOfElem();
	//======����������End======

	//======����������Begin======
	xml.AddChildElem(_T("Main"));
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	//======����������End======

	//======���ٽ�������Begin======
	xml.AddChildElem(_T("Idling"));
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));

	xml.AddChildElem(_T("LeftUp"));					//����������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("Up"));						//���������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("LeftDown"));				//����������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("RightUp"));				//����������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("Right"));					//�ұ�������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.AddChildElem(_T("RightDown"));				//����������Ϣ
	xml.IntoElem();
	xml.AddAttrib(_T("BackImage"),_T(""));
	xml.AddAttrib(_T("Text"),_T(""));
	xml.AddAttrib(_T("DefaultData"),_T("0"));
	xml.OutOfElem();

	xml.OutOfElem();
	//======���ٽ�������End======

	xml.Save(m_strConfigFile);
	return 0;
}

// ���������ļ�
int CVCheckerClsConfig::fSetConfigFile(CString strFileName)
{
	m_strConfigFile = strFileName;
	return 0;
}

int CVCheckerClsConfig::fCheckConfigFile(void)
{
	return 0;
}

// ��������������ȡ������Ϣ
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

		//xml.ResetMainPos(); //ע�⸴λ
		//xml.FindChildElem( "SN" );
		////	xml.FindChildElem();
		//CString csSN = xml.GetChildData();
		//AfxMessageBox(csSN);

		xml.OutOfElem();
	}	

	return CString();
}
