/*
创建:	Yipb	2011-07-20
说明:	系统配置文件操作类，
		使用CMarkup操作XML文件
*/
#pragma once

enum CONFIG_ERR
{
	CONFIG_ERR_FIND_FILE,							//不存在配置文件
	CONFIG_ERR_LOAD_FILE,							//装载配置文件失败
};

class CVCheckerClsConfig
{
private:
	CString m_strConfigFile;
public:
	CVCheckerClsConfig(void);
	CVCheckerClsConfig(CString strFileName);
	~CVCheckerClsConfig(void);
	// 初始化配置文件
	int fInitConfig(void);
	// 设置配置文件
	int fSetConfigFile(CString strFileName);
	int fCheckConfigFile(void);
	// 根据配置索引获取配置信息
	CString fGetConfigData(int nConfigIndex);
};
