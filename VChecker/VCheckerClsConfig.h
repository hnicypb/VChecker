/*
����:	Yipb	2011-07-20
˵��:	ϵͳ�����ļ������࣬
		ʹ��CMarkup����XML�ļ�
*/
#pragma once

enum CONFIG_ERR
{
	CONFIG_ERR_FIND_FILE,							//�����������ļ�
	CONFIG_ERR_LOAD_FILE,							//װ�������ļ�ʧ��
};

class CVCheckerClsConfig
{
private:
	CString m_strConfigFile;
public:
	CVCheckerClsConfig(void);
	CVCheckerClsConfig(CString strFileName);
	~CVCheckerClsConfig(void);
	// ��ʼ�������ļ�
	int fInitConfig(void);
	// ���������ļ�
	int fSetConfigFile(CString strFileName);
	int fCheckConfigFile(void);
	// ��������������ȡ������Ϣ
	CString fGetConfigData(int nConfigIndex);
};
