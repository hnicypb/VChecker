#pragma once
#define DIM(a)  sizeof(a)/sizeof(a[0])  

class CRdWrtIni
{
public:
	CRdWrtIni(void);
	~CRdWrtIni(void);  

	LPWSTR m_pData;    // �洢����INI�ļ����ݵĻ�����   
	//////////////////////////////////////////////////////////////////////////    
	// ��������    
	// ���ļ��������ļ����ݿ�����һ������m_pData�� 
	int  ReadIniFile(LPCWSTR lpFileName);   
	// ��ȡ��m_pData�д�dwOffsetλ�ÿ�ʼ��һ�����ݲ����浽pLine��ͬʱ��ƫ����dwOffset 
	DWORD GetLine(LPWSTR pLine, DWORD dwOffset, DWORD dwSize);   
	// �ж��ǲ���ע���� 
	BOOL IsComment(LPCWSTR pLine);  
	// �ж��ǲ��Ƕ���
	BOOL IsSection(LPCWSTR pLine);   
	// �ж���INI�ļ���һ��(pLine)�ǲ�������Ҫ�ҵĶ���(pSection)  
	BOOL IsSectionName(LPCWSTR pLine, LPCWSTR pSection);   
	// �ж�INI�ļ���һ�е������ǲ�������Ҫ�ҵļ���,����ǲ���ȡ��ֵ  
	BOOL IsKey(LPCWSTR pLine , LPCWSTR pKeyName, LPWSTR* pValue, DWORD* dwValLen );   
	// ��ָ��INI�ļ���д������������ͼ�ֵ  
	void WriteValue(HANDLE m_hOutput , LPCWSTR pAppName, LPCWSTR pKeyName, LPCWSTR pString);   
	// ��INI�ļ�
	DWORD GetString(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName );   

	// WCE�¶�ȡINI�ļ���ĳ����/�����ļ�ֵ���ַ���  
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

	// ��ָ��INI�ļ���д������������ͼ�ֵ  
	BOOL WINAPI WritePrivateProfileInt(   
		LPCTSTR lpAppName,   
		LPCTSTR lpKeyName,   
		INT     Value,   
		LPCTSTR lpFileName);   

	// ���ļ�д��һ������(�����س����з�)  
	void WriteLine(HANDLE hOutput , LPCWSTR pLine);
};
