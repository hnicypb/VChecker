/********************************************************************  
2007/12/03   
Yipb  
读写INI文件
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
**函数：GetString  
**功能：读INI文件  
**参数：  
lpAppName[in]         - 字段名  
lpKeyName[in]         - 键名  
lpReturnedString[out] - 键值  
nSize[in]             - 键值缓冲区大小(in characters )  
lpFileName[in]        - 完整的INI文件名  
**返回：Returns the number of bytes read.  
**备注：  
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
   
    //打开文件，将文件数据拷贝到缓冲区m_pData中，返回INI文件大小    
    if (0 == (dwSize = ReadIniFile(lpFileName)))   
    {   
        ERRORMSG(1, (_T("GetString, Could not ReadIniFile INI file: %s/n"), lpFileName));   
        return 0;   
    }   
   
    cchCopied = 0;   
    while ( 0 != (dwOffset = GetLine( pLine , dwOffset , dwSize )))   
    {   
        //RETAILMSG(1,(_T("%s/n"),szLine));    
        // 是不是注释行    
        if (IsComment(pLine))   
            continue;   
   
        // 是不是段名    
        if (IsSection(pLine))   
        {   
            // 是不是我们要找的段名    
            if (IsSectionName(pLine,lpAppName))   
            {   
                // 寻找我们要的键名    
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
**函数：ReadIniFile  
**功能：打开文件，并将文件数据拷贝到一缓冲区m_pData中   
**参数：  
lpFileName[in] - INI文件名，如果没有路径，默认路径为//windows//  
**返回：  
非0 - 该INI文件的大小(in bytes)  
0   - 失败  
**备注：  
1). 判断一个文本文件是不是UNICODE文件:读取文件前两个字节,如果是0XFF和0XFE  
则为UNICODE文件,否则为ASCII文件(注意根据CPU是大端还是小端格式),这里默  
认为小端格式.如果是UNICODE文件,则丢去前两个字节.  
2). 先将INI整个文件数据读到BYTE型缓冲区中，再转为WCHAR型,为什么?还没弄明白  
************************************************************************/   
int CRdWrtIni::ReadIniFile(LPCWSTR lpFileName)   
{   
    int nReturn = 0;   
    WCHAR szFileName[MAX_PATH] ={0} ;   
    BY_HANDLE_FILE_INFORMATION fi = {0};    
    HANDLE hfile;   
    DWORD dwSize , dwIO;   
    BOOL bUnicode = FALSE, bRet = FALSE; // bUnicode - 标志INI文件是不是Unicode文件    
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
**函数：GetLine  
**功能：获取在m_pData中从dwOffset位置开始的一行数据并保存到pLine，同时把偏移量dwOffset  
移到下一行行首  
**参数：  
pLine[out]   - 接收一行数据(不包括/r/n)  
dwOffset[in] - 要读取的那一行的开始位置  
dwSize[in]   - INI文件大小  
**返回：  
正确 - 下一行行首的位置  
错误 - 0  
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
**函数：IsComment  
**功能：判断是不是注释行  
**参数：  
pLine[in] - INI的一行数据  
**返回：  
1 - 注释行  
0 - 不是注释行  
**备注：  
1). 空行也视为注释行  
************************************************************************/   
BOOL CRdWrtIni::IsComment(LPCWSTR pLine)    
{   
    if (!pLine || 0 == wcslen(pLine) || ';' == *pLine)   
        return TRUE;   
    return FALSE;   
}   
   
/************************************************************************  
**函数：IsSection  
**功能：判断是不是段名  
**参数：  
pLine[in] - INI的一行数据  
**返回：  
1 - 是段名  
0 - 不是  
************************************************************************/   
BOOL CRdWrtIni::IsSection(LPCWSTR pLine)   
{   
    if (pLine && '[' == *pLine)   
        return TRUE;   
    return FALSE;   
}   
   
/************************************************************************  
**函数：IsSectionName  
**功能：判断是INI文件的一行(pLine)是不是我们要找的段名(pSection)  
**参数：  
pLine[in]    - INI文件的一行数据  
pSection[in] - 要找的段名  
**返回：  
1 - 是  
0 - 不是  
**备注：  
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
**函数：IsKey  
**功能：判断INI文件中一行的数据是不是我们要找的键名,如果是并读取键值  
**参数：  
pLine[in] - INI文件某行数据  
pKeyName[in] - 要寻找的键名  
pValue[out] - 键值  
dwValLen[out] - 键值pValue大小(in bytes)  
**返回：  
1 - 是，同时pValue返回键值  
0 - 不是，pValue为NULL  
************************************************************************/   
BOOL CRdWrtIni::IsKey(LPCWSTR pLine , LPCWSTR pKeyName, LPWSTR* pValue, DWORD* dwValLen )   
{   
    LPCWSTR pEqual = NULL;   
    DWORD length = 0, len = 0;   
   
    if(!pLine || !pKeyName)   
        return FALSE;   
   
    // pLine是不是注释行    
    if (IsComment( pLine ))   
        return FALSE;   
   
    // 寻找"="号    
    pEqual = wcschr(pLine, L'=' );   
    if (!pEqual)   
        return FALSE;   
   
    // 寻找键名最后一字符的位置    
    while (pEqual - 1 >= pLine && iswspace(*(pEqual-1)))   
        --pEqual;   
    // Badly formed file.    
    if (pEqual - 1 < pLine)   
        return FALSE;   
   
    // 键名长度    
    length = pEqual - pLine;   
   
    len = wcslen(pKeyName);   
    //if (len == length && 0 == _wcsnicmp(pLine, pKeyName, len))    
    if ( 0 == _wcsnicmp(pLine, pKeyName, len))   
    {   
        *pValue = (LPWSTR)wcschr(pLine, L'=' );   
        ++(*pValue);   
        *dwValLen = wcslen(pLine) - ((*pValue) - pLine);   
   
        // 去掉紧跟在"="号后的所有空格    
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
**函数：GetPrivateProfileString  
**功能：WCE下读取INI文件中某段名/键名的键值的字符串  
**参数：  
lpAppName[in]         - points to section name  
lpKeyName[in]         - points to key name  
lpDefault[in]         - points to default string  
lpReturnedString[out] - points to destination buffer  
nSize[in]             - size of destination buffer "lpReturnedString"(in characters)  
lpFileName[in]        - points to initialization filename   
**返回：The return value is the number of characters copied to the buffer,   
not including the terminating null character.     
1). 如果INI文件没有你关心的数据，返回默认值lpDefault  
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
   
    // 释放内存    
    if (NULL != m_pData)   
    {   
        free( m_pData );   
        m_pData = NULL;   
    }   
   
    return dwReturn;   
}   
   
/************************************************************************  
**函数：GetPrivateProfileInt  
**功能： retrieves an integer associated with a key in the  
specified section of the given initialization file  
**参数：  
LPCTSTR lpAppName,  // address of section name  
LPCTSTR lpKeyName,  // address of key name  
INT nDefault,       // return value if key name is not found  
LPCTSTR lpFileName  // address of initialization filename  
**返回：  
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
   
    // 释放内存    
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
**函数：WriteLine  
**功能：向文件写入一行数据(包括回车换行符)  
**参数：  
hOutput[in] - 已打开的文件句柄  
pLine[in]   - 要写入的一行数据  
**备注：  
1). 写入一行数据，也包括写入行末的"/r/n"两个字符  
2). 注意区分是不是UNICODE版本的INI文件，如果不是，要将WCHAR转为char再写入INI文件  
3). 注意不要将结束符也写入文件  
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
   
            WriteFile(hOutput, buffer, bsize-1 , &dwWrote, NULL); // 注意不要将结束符也写入    
            WriteFile(hOutput, "/r/n", 2, &dwWrote, NULL);   
        }   
    }   
}   


/************************************************************************  
**函数：WritePrivateProfileString  
**功能：WCE环境下，向指定INI文件指定段名写入字符串数据  
**参数：  
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
**返回：  
FALSE - fail  
TRUE  - success  
**备注：  
1). 先将要修改的INI文件的全部数据读取到全局内存m_pData中  
2). 在m_pData中定位到我们要修改的位置，将其它数据和我们修改的数据写入一临时ini文件  
3). 最后将临时ini文件覆盖原来的ini文件，再删除临时ini文件  
4). 主要的API函数：  
CreateFile、ReadFile、WriteFile、SetEndOfFile、CopyFile、DeleteFile  
5). 如果lpKeyName == NULL, 删除整个段, 如果lpString == NULL, 删除健  
************************************************************************/   
BOOL CRdWrtIni::WritePrivateProfileString(   
                               LPCTSTR lpAppName,   
                               LPCTSTR lpKeyName,   
                               LPCTSTR lpString,   
                               LPCTSTR lpFileName)   
{   
    DWORD dwSize, dwOffset;                // dwSize - ini文件大小, dwOffset - 偏移量    
    BOOL  bReadLine = TRUE;   
    BOOL  bWrote = FALSE;   
    TCHAR pszLine[MAX_PATH] = {0};         // 存储一行的数据    
    TCHAR pszIniFileTemp[MAX_PATH] = {0};  // 临时ini文件的名称(包括路径)    
    HANDLE hOutputFile ;   
    LPWSTR pValue;   
    DWORD dwValLen;   
    LPWSTR pName;   
   
    dwOffset = 0;   
    if (!lpFileName)   
        return FALSE;   
   
    // 读取INI文件内容到全局变量m_pData内存中    
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
   
    // 将所有数据写入临时ini文件    
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
                // 以下如果lpKeyName为NULL，删除整个段    
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
                        // 如果lpString为NULL，删除健lpKeyName    
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
   
                // 如果在段名lpAppName下键名lpKeyName不存在，则新建键名lpKeyName和键值lpString    
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
   
    // 如果指定的段名lpAppName不存在，则新建段名lpAppName及键名lpKeyName和键值lpString    
    if (!bWrote && lpKeyName && lpString)   
    {   
        WriteValue(hOutputFile , lpAppName, lpKeyName, lpString);   
    }   
   
    // 用临时ini文件覆盖原来的ini文件并删除临时ini文件    
    if (INVALID_HANDLE_VALUE != hOutputFile)   
    {   
        SetEndOfFile(hOutputFile );   
        CloseHandle(hOutputFile);   
        CopyFile(pszIniFileTemp, lpFileName, FALSE);   
        DeleteFile(pszIniFileTemp);   
    }   
   
    // 释放ReadIniFile函数的全局内存    
    if (NULL != m_pData)   
    {   
        free( m_pData ) ;   
        m_pData = NULL ;   
    }   
   
    return TRUE;   
}   
   
/************************************************************************  
**函数：WritePrivateProfileInt  
**功能：WCE环境下，向指定INI文件指定段名写入整型数据  
**参数：参考WritePrivateProfileString函数  
**返回：  
FALSE - fail  
TRUE  - success  
**备注：  
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
**函数：WriteValue  
**功能：向指定INI文件中写入段名、键名和键值  
**参数：  
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
**返回：NONE  
**备注：  
1). 要成功写入INI文件，键名pKeyName和键值pString都不能为NULL。  
2). 如果段名pAppName为NULL，则只写入键名pKeyName和键值pString。  
3). 注意往INI文件写入字符串时，不要写入结束符。  
************************************************************************/   
void CRdWrtIni::WriteValue(HANDLE m_hOutput, LPCWSTR pAppName, LPCWSTR pKeyName, LPCWSTR pString)   
{   
    char buffer[MAX_PATH] = {0} ;   
    DWORD dwWrote;   
    BOOL m_bUnicode = FALSE ;   
   
    if (pKeyName && pString)   
    {   
        //RETAILMSG( 1 , (TEXT("pKeyName : %s , pString : %s"), pKeyName , pString) ) ;    
   
        if (pAppName)  // 写入段名    
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
   
        if (m_bUnicode)  // 写入健名和键值    
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