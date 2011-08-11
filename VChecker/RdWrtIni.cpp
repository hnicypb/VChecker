/********************************************************************  
2007/12/03   
Yipb  
��дINI�ļ�
*********************************************************************/   

#include "StdAfx.h"
#include "RdWrtIni.h"

CRdWrtIni::CRdWrtIni(void)
{
	m_pData = NULL;
}

CRdWrtIni::~CRdWrtIni(void)
{

}


/************************************************************************  
**������GetString  
**���ܣ���INI�ļ�  
**������  
lpAppName[in]         - �ֶ���  
lpKeyName[in]         - ����  
lpReturnedString[out] - ��ֵ  
nSize[in]             - ��ֵ��������С(in characters )  
lpFileName[in]        - ������INI�ļ���  
**���أ�Returns the number of bytes read.  
**��ע��  
************************************************************************/   
DWORD CRdWrtIni::GetString( LPCWSTR lpAppName,LPCWSTR lpKeyName,   
                LPWSTR lpReturnedString, DWORD nSize,LPCWSTR lpFileName)   
{   
    //WCHAR szFileName[MAX_PATH];    
    DWORD dwSize , cchCopied;   
    DWORD dwOffset = 0;   
    TCHAR pLine[MAX_PATH] = {0} ;   
    DWORD dwValLen = 0;   
   
    if (!lpAppName || !lpFileName)   
        return 0;   
   
    //���ļ������ļ����ݿ�����������m_pData�У�����INI�ļ���С    
    if (0 == (dwSize = ReadIniFile(lpFileName)))   
    {   
        ERRORMSG(1, (_T("GetString, Could not ReadIniFile INI file: %s/n"), lpFileName));   
        return 0;   
    }   
   
    cchCopied = 0;   
    while ( 0 != (dwOffset = GetLine( pLine , dwOffset , dwSize )))   
    {   
        //RETAILMSG(1,(_T("%s/n"),szLine));    
        // �ǲ���ע����    
        if (IsComment(pLine))   
            continue;   
   
        // �ǲ��Ƕ���    
        if (IsSection(pLine))   
        {   
            // �ǲ�������Ҫ�ҵĶ���    
            if (IsSectionName(pLine,lpAppName))   
            {   
                // Ѱ������Ҫ�ļ���    
                while ( 0 != (dwOffset = GetLine(pLine , dwOffset , dwSize)))   
                {   
                    LPWSTR pValue=NULL;   
   
                    if (IsSection(pLine))   
                        break;   
   
                    if (IsKey(pLine , lpKeyName, &pValue, &dwValLen))   
                    {   
                        cchCopied = min(dwValLen, nSize-1);   
                        wcsncpy(lpReturnedString, pValue, cchCopied);   
                        lpReturnedString[cchCopied] = 0;   
                        // We're done.    
                        break;         
                    }   
                }   
                break;   
            }   
        }   
    }   
   
    return cchCopied;   
}   
   
/************************************************************************  
**������ReadIniFile  
**���ܣ����ļ��������ļ����ݿ�����һ������m_pData��   
**������  
lpFileName[in] - INI�ļ��������û��·����Ĭ��·��Ϊ//windows//  
**���أ�  
��0 - ��INI�ļ��Ĵ�С(in bytes)  
0   - ʧ��  
**��ע��  
1). �ж�һ���ı��ļ��ǲ���UNICODE�ļ�:��ȡ�ļ�ǰ�����ֽ�,�����0XFF��0XFE  
��ΪUNICODE�ļ�,����ΪASCII�ļ�(ע�����CPU�Ǵ�˻���С�˸�ʽ),����Ĭ  
��ΪС�˸�ʽ.�����UNICODE�ļ�,��ȥǰ�����ֽ�.  
2). �Ƚ�INI�����ļ����ݶ���BYTE�ͻ������У���תΪWCHAR��,Ϊʲô?��ûŪ����  
************************************************************************/   
int CRdWrtIni::ReadIniFile(LPCWSTR lpFileName)   
{   
    int nReturn = 0;   
    WCHAR szFileName[MAX_PATH] ={0} ;   
    BY_HANDLE_FILE_INFORMATION fi = {0};    
    HANDLE hfile;   
    DWORD dwSize , dwIO;   
    BOOL bUnicode = FALSE, bRet = FALSE; // bUnicode - ��־INI�ļ��ǲ���Unicode�ļ�    
    BYTE* pData = NULL;   
   
    if (!lpFileName)   
    {   
        nReturn = 0;   
        goto exit;   
    }   
   
    if (wcschr(lpFileName, '//'))   
        wcscpy(szFileName, lpFileName);   
    else   
        wsprintf(szFileName, _T("//windows//%s"), lpFileName);   
   
    // ReadIniFile the file.    
    hfile = CreateFile(szFileName, GENERIC_READ,   
        FILE_SHARE_READ,   
        (LPSECURITY_ATTRIBUTES)0, OPEN_EXISTING,   
        FILE_ATTRIBUTE_NORMAL, (HANDLE)0);   
   
    if (hfile == INVALID_HANDLE_VALUE)   
    {   
        ERRORMSG(1, (_T("ReadIniFile, CreateFile failed on INI file: %s, err %d/n"), szFileName, GetLastError()));   
        nReturn = 0;   
        goto exit;   
    }   
   
    // Get its size.    
    if (!GetFileInformationByHandle(hfile, &fi))   
    {   
        CloseHandle(hfile);   
        ERRORMSG(1, (_T("ReadIniFile, GetFileInformationByHandle failed on INI file: %s/n"), szFileName));   
        nReturn = 0;   
        goto exit;   
    }   
   
    dwSize = (fi.nFileSizeLow + 1) & ~0x1; //keep it word aligned    
   
    // Now check if the file is unicode.    
    dwIO = 0;   
    if (sizeof(WORD) <= dwSize)   
    {   
        WORD wByteOrderMark = 0;   
   
        // See comment at the bottom of the file.    
        if ((ReadFile(hfile, &wByteOrderMark, sizeof(WORD), &dwIO, NULL)) &&    
            (dwIO == sizeof(WORD)) &&    
            (0xfeff == wByteOrderMark))   
        {   
            dwSize -= sizeof(WORD);   
            bUnicode = TRUE;   
        }   
        else   
            SetFilePointer(hfile, 0, NULL, FILE_BEGIN);   
    }   
   
    // Next, load the data.    
    //RETAILMSG(1, (_T("ReadIniFile, the size of ini file [%s] is [%d]/n"), szFileName, dwSize));     
    if (0 < dwSize)   
    {   
        pData = (BYTE *)malloc( dwSize + sizeof(WCHAR) );   
        if (!pData)   
        {   
            RETAILMSG(1, (_T("ReadIniFile, no enough memory/n")));   
            nReturn = 0;   
            goto exit;   
        }   
        memset(pData,0,dwSize + sizeof(WCHAR));   
        bRet = ReadFile(hfile, pData, dwSize, &dwIO, NULL);   
        CloseHandle(hfile);   
        if (!bRet)   
        {   
   
            RETAILMSG(1, (_T("ReadIniFile, ReadFile fail, err = [%d]/n"),GetLastError()));    
            nReturn = 0;   
            goto exit;   
        }   
   
        // Create the buffer.    
        if( m_pData )   
        {   
            free(m_pData);   
            m_pData = NULL;   
        }   
   
        dwSize = MultiByteToWideChar( CP_ACP,0, (char *)pData ,-1,NULL,0);   
        m_pData = (TCHAR *)malloc(dwSize*sizeof(WCHAR));   
        if(!m_pData)   
        {   
            RETAILMSG(1, (_T("ReadIniFile, no enough momery/n")));   
            nReturn = 0;   
            goto exit;   
        }   
        MultiByteToWideChar(CP_ACP,0,(char *)pData,-1,m_pData,dwSize);   
   
        dwSize--; // includes the NULL termination character    
        nReturn = dwSize;   
    }   
   
exit:   
    if(pData)   
    {   
        free(pData);   
        pData = NULL;   
    }   
    if(hfile)   
    {   
        CloseHandle(hfile);   
        hfile = NULL;   
    }   
    return nReturn;   
}   
   
   
/************************************************************************  
**������GetLine  
**���ܣ���ȡ��m_pData�д�dwOffsetλ�ÿ�ʼ��һ�����ݲ����浽pLine��ͬʱ��ƫ����dwOffset  
�Ƶ���һ������  
**������  
pLine[out]   - ����һ������(������/r/n)  
dwOffset[in] - Ҫ��ȡ����һ�еĿ�ʼλ��  
dwSize[in]   - INI�ļ���С  
**���أ�  
��ȷ - ��һ�����׵�λ��  
���� - 0  
/************************************************************************/   
DWORD CRdWrtIni::GetLine(LPWSTR pLine, DWORD dwOffset, DWORD dwSize)   
{   
    DWORD len = 0;   
    DWORD len2 = 0;   
    // Look for the end of the line.    
    while ( dwOffset + len < dwSize   
        && '/r' != m_pData[dwOffset+len] && '/n' != m_pData[dwOffset+len])   
    {   
        if( m_pData[dwOffset+len]==0 )   
            break;   
        pLine[len] = m_pData[dwOffset+len] ;   
        ++len;   
    }   
   
    pLine[len] = 0 ;   
    // Now push the internal offset past the newline.    
    // (We assume /r/n pairs are always in this order)    
    if (dwOffset + len + len2 < dwSize && '/r' == m_pData[dwOffset+len+len2])   
        ++len2;   
    if (dwOffset + len + len2+1 < dwSize && '/n' == m_pData[dwOffset+len+len2])   
        ++len2;   
    if (2 >= len + len2 && (dwOffset +2 >=dwSize) )   
        return 0;   
   
    dwOffset += len + len2;   
    return dwOffset;   
}   
   
/************************************************************************  
**������IsComment  
**���ܣ��ж��ǲ���ע����  
**������  
pLine[in] - INI��һ������  
**���أ�  
1 - ע����  
0 - ����ע����  
**��ע��  
1). ����Ҳ��Ϊע����  
************************************************************************/   
BOOL CRdWrtIni::IsComment(LPCWSTR pLine)    
{   
    if (!pLine || 0 == wcslen(pLine) || ';' == *pLine)   
        return TRUE;   
    return FALSE;   
}   
   
/************************************************************************  
**������IsSection  
**���ܣ��ж��ǲ��Ƕ���  
**������  
pLine[in] - INI��һ������  
**���أ�  
1 - �Ƕ���  
0 - ����  
************************************************************************/   
BOOL CRdWrtIni::IsSection(LPCWSTR pLine)   
{   
    if (pLine && '[' == *pLine)   
        return TRUE;   
    return FALSE;   
}   
   
/************************************************************************  
**������IsSectionName  
**���ܣ��ж���INI�ļ���һ��(pLine)�ǲ�������Ҫ�ҵĶ���(pSection)  
**������  
pLine[in]    - INI�ļ���һ������  
pSection[in] - Ҫ�ҵĶ���  
**���أ�  
1 - ��  
0 - ����  
**��ע��  
************************************************************************/   
BOOL CRdWrtIni::IsSectionName(LPCWSTR pLine, LPCWSTR pSection)   
{   
    if (IsSection(pLine))   
    {   
        DWORD len = wcslen(pSection);   
        if (wcslen(pLine) - 2 == len && 0 == _wcsnicmp(pLine+1, pSection, len))   
            return TRUE;   
    }   
    return FALSE;   
}   
   
/************************************************************************  
**������IsKey  
**���ܣ��ж�INI�ļ���һ�е������ǲ�������Ҫ�ҵļ���,����ǲ���ȡ��ֵ  
**������  
pLine[in] - INI�ļ�ĳ������  
pKeyName[in] - ҪѰ�ҵļ���  
pValue[out] - ��ֵ  
dwValLen[out] - ��ֵpValue��С(in bytes)  
**���أ�  
1 - �ǣ�ͬʱpValue���ؼ�ֵ  
0 - ���ǣ�pValueΪNULL  
************************************************************************/   
BOOL CRdWrtIni::IsKey(LPCWSTR pLine , LPCWSTR pKeyName, LPWSTR* pValue, DWORD* dwValLen )   
{   
    LPCWSTR pEqual = NULL;   
    DWORD length = 0, len = 0;   
   
    if(!pLine || !pKeyName)   
        return FALSE;   
   
    // pLine�ǲ���ע����    
    if (IsComment( pLine ))   
        return FALSE;   
   
    // Ѱ��"="��    
    pEqual = wcschr(pLine, L'=' );   
    if (!pEqual)   
        return FALSE;   
   
    // Ѱ�Ҽ������һ�ַ���λ��    
    while (pEqual - 1 >= pLine && iswspace(*(pEqual-1)))   
        --pEqual;   
    // Badly formed file.    
    if (pEqual - 1 < pLine)   
        return FALSE;   
   
    // ��������    
    length = pEqual - pLine;   
   
    len = wcslen(pKeyName);   
    //if (len == length && 0 == _wcsnicmp(pLine, pKeyName, len))    
    if ( 0 == _wcsnicmp(pLine, pKeyName, len))   
    {   
        *pValue = (LPWSTR)wcschr(pLine, L'=' );   
        ++(*pValue);   
        *dwValLen = wcslen(pLine) - ((*pValue) - pLine);   
   
        // ȥ��������"="�ź�����пո�    
        while (0 < *dwValLen && iswspace(**pValue))   
        {   
            ++(*pValue);   
            --(*dwValLen);   
        }   
        while (0 < *dwValLen && iswspace((*pValue)[*dwValLen-1]))   
        {   
            --(*dwValLen);   
        }   
        // If the string is surrounded by quotes, remove them.    
        if ('"' == (**pValue))   
        {   
            ++(*pValue);   
            --(*dwValLen);   
            if ('"' == (*pValue)[*dwValLen-1])   
            {   
                --(*dwValLen);   
            }   
        }   
        return TRUE;   
    }   
    else   
    {   
        *pValue = NULL;   
        return FALSE;   
    }   
}   
   
   
/************************************************************************  
**������GetPrivateProfileString  
**���ܣ�WCE�¶�ȡINI�ļ���ĳ����/�����ļ�ֵ���ַ���  
**������  
lpAppName[in]         - points to section name  
lpKeyName[in]         - points to key name  
lpDefault[in]         - points to default string  
lpReturnedString[out] - points to destination buffer  
nSize[in]             - size of destination buffer "lpReturnedString"(in characters)  
lpFileName[in]        - points to initialization filename   
**���أ�The return value is the number of characters copied to the buffer,   
not including the terminating null character.     
1). ���INI�ļ�û������ĵ����ݣ�����Ĭ��ֵlpDefault  
************************************************************************/   
DWORD CRdWrtIni::GetPrivateProfileString(   
                              LPCWSTR lpAppName,   
                              LPCWSTR lpKeyName,   
                              LPCWSTR lpDefault,    
                              LPWSTR  lpReturnedString,   
                              DWORD   Size,   
                              LPCWSTR lpFileName )   
{   
    DWORD dwRc = 0, dwReturn = 0;   
    if(!lpAppName || !lpKeyName || !lpReturnedString || !lpFileName || Size<=0 )   
        return 0;   
   
    dwRc = GetString(lpAppName,lpKeyName,lpReturnedString,Size,lpFileName);   
    if(dwRc != 0)   
    {   
        dwReturn = dwRc;   
    }   
    else   
    {   
        if(lpDefault)   
        {   
            wcsncpy(lpReturnedString, lpDefault, Size);   
            lpReturnedString[Size-1] = NULL;   
        }   
        else   
            *lpReturnedString = 0;   
        dwReturn = wcslen(lpReturnedString);   
    }   
   
    // �ͷ��ڴ�    
    if (NULL != m_pData)   
    {   
        free( m_pData );   
        m_pData = NULL;   
    }   
   
    return dwReturn;   
}   
   
/************************************************************************  
**������GetPrivateProfileInt  
**���ܣ� retrieves an integer associated with a key in the  
specified section of the given initialization file  
**������  
LPCTSTR lpAppName,  // address of section name  
LPCTSTR lpKeyName,  // address of key name  
INT nDefault,       // return value if key name is not found  
LPCTSTR lpFileName  // address of initialization filename  
**���أ�  
The return value is the integer equivalent of the string following   
the specified key name in the specified initialization file. If the   
key is not found, the return value is the specified default value.   
If the value of the key is less than zero, the return value is zero.   
************************************************************************/   
UINT CRdWrtIni::GetPrivateProfileInt(   
                          LPCTSTR lpAppName,   
                          LPCTSTR lpKeyName,    
                          INT nDefault,   
                          LPCTSTR lpFileName )   
{   
    WCHAR szRet[80] ={0};   
   
    if(!lpAppName || !lpKeyName || !lpFileName )   
        return 0;   
   
    DWORD cch = GetString(lpAppName, lpKeyName, szRet, sizeof(szRet)/sizeof(WCHAR), lpFileName);   
   
    // �ͷ��ڴ�    
    if (NULL != m_pData)   
    {   
        free( m_pData );   
        m_pData = NULL;   
    }   
   
    if (cch)   
        return _wtoi(szRet);   
    else   
        return nDefault;    
}   
   
/************************************************************************  
**������WriteLine  
**���ܣ����ļ�д��һ������(�����س����з�)  
**������  
hOutput[in] - �Ѵ򿪵��ļ����  
pLine[in]   - Ҫд���һ������  
**��ע��  
1). д��һ�����ݣ�Ҳ����д����ĩ��"/r/n"�����ַ�  
2). ע�������ǲ���UNICODE�汾��INI�ļ���������ǣ�Ҫ��WCHARתΪchar��д��INI�ļ�  
3). ע�ⲻҪ��������Ҳд���ļ�  
************************************************************************/   
void CRdWrtIni::WriteLine(HANDLE hOutput , LPCWSTR pLine)   
{   
    DWORD dwWrote = 0;   
    WCHAR wBuffer[MAX_PATH] = {0};   
    char buffer[MAX_PATH] ={0};   
    DWORD dwlen = wcslen(pLine) ;   
    BOOL bUnicode = FALSE ;   
   
    if(bUnicode)   
    {   
        if (pLine)   
        {   
            WriteFile(hOutput, pLine, wcslen(pLine)*sizeof(WCHAR), &dwWrote, NULL);   
            WriteFile(hOutput, L"/r/n", 2*sizeof(WCHAR), &dwWrote, NULL);   
        }   
    }   
    else   
    {   
        if (pLine)   
        {   
            int bsize ;   
            TCHAR szTempLine[MAX_PATH] = {0} ;   
            wcsncpy( szTempLine, pLine, dwlen);   
   
            bsize=WideCharToMultiByte(CP_ACP,0,szTempLine,-1,NULL,0,NULL,NULL);   
            WideCharToMultiByte(CP_ACP,0,szTempLine,-1,buffer, bsize,NULL,NULL);   
            buffer[bsize] = 0 ;   
   
            WriteFile(hOutput, buffer, bsize-1 , &dwWrote, NULL); // ע�ⲻҪ��������Ҳд��    
            WriteFile(hOutput, "/r/n", 2, &dwWrote, NULL);   
        }   
    }   
}   


/************************************************************************  
**������WritePrivateProfileString  
**���ܣ�WCE�����£���ָ��INI�ļ�ָ������д���ַ�������  
**������  
lpAppName[in]  
Pointer to a null-terminated string containing section name. If  
the section does not exit, it is created.  
lpKeyName[in]  
Pointer to a null-terminated string containing key name. If the  
key does not exit in the specified section pointed to by the lpAppName   
parameter, it's created. If this parameter is NULL, the ertire section,   
including all keys within the section, is deleted. When deleting a   
section, leave the comments intact.  
lpString[in]  
pointer to a null-terminated string to be written to the file.   
If this parameter is NULL, the key pointed to by the lpKeyName   
parameter is deleted.  
lpFileName[in]  
Pointer to a null-terminated string that names the initialization file.   
**���أ�  
FALSE - fail  
TRUE  - success  
**��ע��  
1). �Ƚ�Ҫ�޸ĵ�INI�ļ���ȫ�����ݶ�ȡ��ȫ���ڴ�m_pData��  
2). ��m_pData�ж�λ������Ҫ�޸ĵ�λ�ã����������ݺ������޸ĵ�����д��һ��ʱini�ļ�  
3). �����ʱini�ļ�����ԭ����ini�ļ�����ɾ����ʱini�ļ�  
4). ��Ҫ��API������  
CreateFile��ReadFile��WriteFile��SetEndOfFile��CopyFile��DeleteFile  
5). ���lpKeyName == NULL, ɾ��������, ���lpString == NULL, ɾ����  
************************************************************************/   
BOOL CRdWrtIni::WritePrivateProfileString(   
                               LPCTSTR lpAppName,   
                               LPCTSTR lpKeyName,   
                               LPCTSTR lpString,   
                               LPCTSTR lpFileName)   
{   
    DWORD dwSize, dwOffset;                // dwSize - ini�ļ���С, dwOffset - ƫ����    
    BOOL  bReadLine = TRUE;   
    BOOL  bWrote = FALSE;   
    TCHAR pszLine[MAX_PATH] = {0};         // �洢һ�е�����    
    TCHAR pszIniFileTemp[MAX_PATH] = {0};  // ��ʱini�ļ�������(����·��)    
    HANDLE hOutputFile ;   
    LPWSTR pValue;   
    DWORD dwValLen;   
    LPWSTR pName;   
   
    dwOffset = 0;   
    if (!lpFileName)   
        return FALSE;   
   
    // ��ȡINI�ļ����ݵ�ȫ�ֱ���m_pData�ڴ���    
    dwSize = ReadIniFile(lpFileName);   
   
    //RETAILMSG(1, (TEXT("lpFileName=[%s], dwSize=[%d]"), lpFileName, dwSize));    
   
    // Create the output file.    
    //wcscpy(pszIniFileTemp, lpFileName);    
    pName = (LPWSTR)_tcsrchr(lpFileName, TEXT'//');   
    if(pName)   
    {   
        pName++;   
        wsprintf(pszIniFileTemp,TEXT("//Windows//%s.tmp"),pName);   
    }   
    else   
    {    
        wsprintf(pszIniFileTemp, TEXT("//Windows//%s.ini.tmp"),lpAppName);   
    }   
   
    hOutputFile = CreateFile(pszIniFileTemp,   
        GENERIC_WRITE,   
        0,(LPSECURITY_ATTRIBUTES)0,    
        CREATE_ALWAYS,   
        FILE_ATTRIBUTE_NORMAL,   
        0);   
    if (INVALID_HANDLE_VALUE == hOutputFile)   
    {   
        ERRORMSG(1, (TEXT("Could not open output file: %s/n"), pszIniFileTemp));   
        return FALSE;   
    }   
   
    // ����������д����ʱini�ļ�    
    for (;;)   
    {   
        // The bReadLine flag is used to not read a new line after we break    
        // out of the inner loop. We've already got a line to process.    
        if (bReadLine)   
        {   
            dwOffset = GetLine( pszLine , dwOffset , dwSize );   
            if (!dwOffset)   
                break;   
        }   
        bReadLine = TRUE;   
        // Skip past comments.    
        if (IsComment(pszLine))   
        {   
            WriteLine(hOutputFile , pszLine);   
            continue;   
        }   
        // Found a section name.    
        if (IsSection(pszLine))   
        {   
            // It's the section we want.    
            if (IsSectionName(pszLine , lpAppName))   
            {   
                // �������lpKeyNameΪNULL��ɾ��������    
                if (lpKeyName)   
                    WriteLine(hOutputFile , pszLine);   
   
                // Process the whole section.    
                while (0 != (dwOffset = GetLine( pszLine , dwOffset , dwSize )))   
                {   
                    // Reached the end of the section.    
                    if (IsSection(pszLine))   
                    {   
                        bReadLine = FALSE;   
                        // This line will be written in the outer loop.    
                        break;   
                    }   
                    // When deleting a section, leave the comments intact.    
                    else if (IsComment(pszLine))   
                    {   
                        WriteLine(hOutputFile , pszLine);   
                        continue;   
                    }   
                    // Got the value we want.    
                    if (!bWrote && IsKey(pszLine , lpKeyName, &pValue, &dwValLen))   
                    {   
                        bWrote = TRUE;   
                        // ���lpStringΪNULL��ɾ����lpKeyName    
                        if(lpString)   
                            WriteValue(hOutputFile , NULL, lpKeyName, lpString);   
                    }   
                    else   
                    {   
                        if (lpKeyName)   
                            WriteLine(hOutputFile , pszLine);   
                    }   
   
                    if(dwOffset >= dwSize)   
                        break ;   
                }   
   
                // ����ڶ���lpAppName�¼���lpKeyName�����ڣ����½�����lpKeyName�ͼ�ֵlpString    
                if (!bWrote)   
                {   
                    bWrote = TRUE;   
                    WriteValue(hOutputFile, NULL, lpKeyName, lpString);   
                }   
            }   
            else   
                WriteLine(hOutputFile , pszLine);   
        }   
        else   
            WriteLine(hOutputFile , pszLine);   
   
        if(dwOffset ==0)    
            break;   
    }   
   
    // ���ָ���Ķ���lpAppName�����ڣ����½�����lpAppName������lpKeyName�ͼ�ֵlpString    
    if (!bWrote && lpKeyName && lpString)   
    {   
        WriteValue(hOutputFile , lpAppName, lpKeyName, lpString);   
    }   
   
    // ����ʱini�ļ�����ԭ����ini�ļ���ɾ����ʱini�ļ�    
    if (INVALID_HANDLE_VALUE != hOutputFile)   
    {   
        SetEndOfFile(hOutputFile );   
        CloseHandle(hOutputFile);   
        CopyFile(pszIniFileTemp, lpFileName, FALSE);   
        DeleteFile(pszIniFileTemp);   
    }   
   
    // �ͷ�ReadIniFile������ȫ���ڴ�    
    if (NULL != m_pData)   
    {   
        free( m_pData ) ;   
        m_pData = NULL ;   
    }   
   
    return TRUE;   
}   
   
/************************************************************************  
**������WritePrivateProfileInt  
**���ܣ�WCE�����£���ָ��INI�ļ�ָ������д����������  
**�������ο�WritePrivateProfileString����  
**���أ�  
FALSE - fail  
TRUE  - success  
**��ע��  
************************************************************************/   
BOOL WINAPI CRdWrtIni::WritePrivateProfileInt(   
                                   LPCTSTR lpAppName,   
                                   LPCTSTR lpKeyName,   
                                   INT     Value,   
                                   LPCTSTR lpFileName)   
{      
    TCHAR ValBuf[16]={0};       
   
    wsprintf( ValBuf, TEXT( "%i" ), Value);       
    return( WritePrivateProfileString(lpAppName, lpKeyName, ValBuf, lpFileName) );    
}   
   
/************************************************************************  
**������WriteValue  
**���ܣ���ָ��INI�ļ���д������������ͼ�ֵ  
**������  
m_hOutput[in]  
pointer to the handle of ini file.  
pAppName[in]  
Pointer to a null-terminated string containing the name of the section  
in which data is written. If this parameter is NULL, the WriteValue  
function just wirte the pKeyName and pString.  
pKeyName[in]  
Pointer to a null-terminated string containing the name of the key in  
which data is writtern.   
pString[in]  
Pointer to a null-terminated string to be written to the file.   
**���أ�NONE  
**��ע��  
1). Ҫ�ɹ�д��INI�ļ�������pKeyName�ͼ�ֵpString������ΪNULL��  
2). �������pAppNameΪNULL����ֻд�����pKeyName�ͼ�ֵpString��  
3). ע����INI�ļ�д���ַ���ʱ����Ҫд���������  
************************************************************************/   
void CRdWrtIni::WriteValue(HANDLE m_hOutput, LPCWSTR pAppName, LPCWSTR pKeyName, LPCWSTR pString)   
{   
    char buffer[MAX_PATH] = {0} ;   
    DWORD dwWrote;   
    BOOL m_bUnicode = FALSE ;   
   
    if (pKeyName && pString)   
    {   
        //RETAILMSG( 1 , (TEXT("pKeyName : %s , pString : %s"), pKeyName , pString) ) ;    
   
        if (pAppName)  // д�����    
        {   
            if (m_bUnicode)   
            {   
                WriteFile(m_hOutput, L"[", sizeof(WCHAR), &dwWrote, NULL);   
                WriteFile(m_hOutput, pAppName, wcslen(pAppName)*sizeof(WCHAR), &dwWrote, NULL);   
                WriteFile(m_hOutput, L"]/r/n", 3*sizeof(WCHAR), &dwWrote, NULL);   
            }   
            else   
            {   
                int bsize , iRetLen;   
                TCHAR szTempLine[256] ={0} ;   
   
                wcscpy( szTempLine , TEXT("[") ) ;   
                wcscat( szTempLine , pAppName ) ;   
                wcscat( szTempLine , TEXT("]") ) ;   
   
                bsize=WideCharToMultiByte(CP_ACP,0,szTempLine,-1,NULL,0,NULL,NULL);   
                iRetLen = WideCharToMultiByte(CP_ACP,0,szTempLine,-1,buffer, bsize,NULL,NULL);   
                buffer[bsize] = 0 ;   
   
                WriteFile(m_hOutput, buffer , bsize-1 , &dwWrote, NULL);   
                WriteFile(m_hOutput, "/r/n", 2, &dwWrote, NULL);   
   
            }   
        }   
   
        if (m_bUnicode)  // д�뽡���ͼ�ֵ    
        {   
            WriteFile(m_hOutput, pKeyName, wcslen(pKeyName)*sizeof(WCHAR), &dwWrote, NULL);   
            WriteFile(m_hOutput, L"=", sizeof(WCHAR), &dwWrote, NULL);   
            WriteFile(m_hOutput, pString, wcslen(pString)*sizeof(WCHAR), &dwWrote, NULL);   
            WriteFile(m_hOutput, L"/r/n", 2*sizeof(WCHAR), &dwWrote, NULL);   
        }   
        else   
        {      
            int bsize , iRetLen;   
            TCHAR szTempLine[256] ={0} ;   
   
            wcscpy( szTempLine , pKeyName ) ;   
            wcscat( szTempLine , TEXT("=") ) ;   
            wcscat( szTempLine , pString )  ;   
   
            bsize=WideCharToMultiByte(CP_ACP,0,szTempLine,-1,NULL,0,NULL,NULL);   
            iRetLen = WideCharToMultiByte(CP_ACP,0,szTempLine,-1,buffer, bsize,NULL,NULL);   
            buffer[bsize] = 0 ;   
   
            WriteFile(m_hOutput, buffer, bsize-1 , &dwWrote, NULL);   
            WriteFile(m_hOutput, "/r/n", 2, &dwWrote, NULL);   
        }   
    }   
}   