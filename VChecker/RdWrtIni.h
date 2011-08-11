#pragma once
#define DIM(a)  sizeof(a)/sizeof(a[0])  

class CRdWrtIni
{
public:
	CRdWrtIni(void);
	~CRdWrtIni(void);  

	LPWSTR m_pData;    // 存储整个INI文件数据的缓冲区   
	//////////////////////////////////////////////////////////////////////////    
	// 函数声明    
	// 打开文件，并将文件数据拷贝到一缓冲区m_pData中 
	int  ReadIniFile(LPCWSTR lpFileName);   
	// 获取在m_pData中从dwOffset位置开始的一行数据并保存到pLine，同时把偏移量dwOffset 
	DWORD GetLine(LPWSTR pLine, DWORD dwOffset, DWORD dwSize);   
	// 判断是不是注释行 
	BOOL IsComment(LPCWSTR pLine);  
	// 判断是不是段名
	BOOL IsSection(LPCWSTR pLine);   
	// 判断是INI文件的一行(pLine)是不是我们要找的段名(pSection)  
	BOOL IsSectionName(LPCWSTR pLine, LPCWSTR pSection);   
	// 判断INI文件中一行的数据是不是我们要找的键名,如果是并读取键值  
	BOOL IsKey(LPCWSTR pLine , LPCWSTR pKeyName, LPWSTR* pValue, DWORD* dwValLen );   
	// 向指定INI文件中写入段名、键名和键值  
	void WriteValue(HANDLE m_hOutput , LPCWSTR pAppName, LPCWSTR pKeyName, LPCWSTR pString);   
	// 读INI文件
	DWORD GetString(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName );   

	// WCE下读取INI文件中某段名/键名的键值的字符串  
	DWORD GetPrivateProfileString(   
		LPCWSTR lpAppName,   
		LPCWSTR lpKeyName,   
		LPCWSTR lpDefault,    
		LPWSTR  lpReturnedString,   
		DWORD   Size,   
		LPCWSTR lpFileName );   

	UINT GetPrivateProfileInt(   
		LPCTSTR lpAppName,   
		LPCTSTR lpKeyName,    
		INT nDefault,   
		LPCTSTR lpFileName );   

	BOOL WritePrivateProfileString(   
		LPCTSTR lpAppName,   
		LPCTSTR lpKeyName,   
		LPCTSTR lpString,   
		LPCTSTR lpFileName);   

	// 向指定INI文件中写入段名、键名和键值  
	BOOL WINAPI WritePrivateProfileInt(   
		LPCTSTR lpAppName,   
		LPCTSTR lpKeyName,   
		INT     Value,   
		LPCTSTR lpFileName);   

	// 向文件写入一行数据(包括回车换行符)  
	void WriteLine(HANDLE hOutput , LPCWSTR pLine);
};
