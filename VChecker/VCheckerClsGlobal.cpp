
#include "StdAfx.h"
#include "VCheckerClsGlobal.h"
#include "VChecker.h"

CVCheckerClsGlobal::CVCheckerClsGlobal(void)
{
	fInitGlobalVariable();
}

// ��ʼ��ȫ�ֱ���
int CVCheckerClsGlobal::fInitGlobalVariable(void)
{
	m_strAppPath = fGetAppPath();
	m_strConfigFile = _T("\\config.xml");

	return 0;
}

CVCheckerClsGlobal::~CVCheckerClsGlobal(void)
{
}

//����һ���µĵ�GUID����
CString CVCheckerClsGlobal::fGenerateGuid(void)
{
	CString strGuid;
	GUID guid;   
	::CoCreateGuid(&guid);  
	strGuid.Format(_T("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X")
		,guid.Data1,guid.Data2,guid.Data3
		,guid.Data4[0],guid.Data4[1]   
	,guid.Data4[2],guid.Data4[3],guid.Data4[4],guid.Data4[5],guid.Data4[6],guid.Data4[7]   
	);   

	return strGuid;
}

// ����һ��iMin-iMax�������������
int CVCheckerClsGlobal::fGetRangeRandom(int iMin, int iMax)
{
	CTime now = CTime::GetCurrentTime();
	srand(int(now.GetTime()));
	int r = iMin + rand()%(iMax-iMin);
	return r;
}

// ��ȡ���г���·��
CString CVCheckerClsGlobal::fGetAppPath(void)
{
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	return strPath;
}

// ��ȡ����������·���ļ�
CString CVCheckerClsGlobal::fGetConfigPathFile(void)
{
	return m_strAppPath + m_strConfigFile;
}

// ��ȡ��Ļ�ֱ���
CString CVCheckerClsGlobal::fGetScreenResolution(void)
{
	int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //��Ļ��� 
	y = GetSystemMetrics(SM_CYSCREEN); //��Ļ�߶�

	CString strReturn;
	strReturn.Format(_T("%dX%d"),x,y);
	return strReturn;

	/*
	SM_CLEANBOOT ����ϵͳ������ʽ�� ����
	0 �������� ����1 ��ȫģʽ���� ����2 ���簲ȫģʽ���� ����
	SM_CMOUSEBUTTONS ����ֵΪϵͳ֧�ֵ�������������0����ϵͳ��û�а�װ��ꡣ ����
	SM_CXBORDER, ����SM_CYBORDER ����������ֵΪ��λ��Windows���ڱ߿�Ŀ�Ⱥ͸߶ȣ����Windows��Ϊ3D��̬���� ������ͬ��SM_CXEDGE���� ����
	SM_CXCURSOR, ����SM_CYCURSOR ����������ֵΪ��λ�ı�׼���Ŀ�Ⱥ͸߶� ����
	SM_CXDLGFRAME, ����SM_CYDLGFRAME ��ͬ��SM_CXFIXEDFRAME and SM_CYFIXEDFRAME ����
	SM_CXDOUBLECLK, ����SM_CYDOUBLECLK ������ֵΪ��λ��˫����Ч�ľ������� ����
	SM_CXEDGE,SM_CYEDGE ������ֵΪ��λ��3D�߿�Ŀ�Ⱥ͸߶� ����
	SM_CXFIXEDFRAME, ����SM_CYFIXEDFRAME Χ�ƾ��б��⵫�޷��ı�ߴ�Ĵ��ڣ�ͨ����һЩ�Ի��򣩵ı߿�ĺ�� ����
	SM_CXFRAME,SM_CYFRAME ��ͬ��SM_CXSIZEFRAME and SM_CYSIZEFRAME ����
	SM_CXFULLSCREEN, ����SM_CYFULLSCREEN ȫ��Ļ���ڵĴ�������Ŀ�Ⱥ͸߶� ����
	SM_CXHSCROLL, ����SM_CYHSCROLL ˮƽ�������ĸ߶Ⱥ�ˮƽ�������ϼ�ͷ�Ŀ�� ����
	SM_CXHTHUMB ������Ϊ��λ��ˮƽ�������ϵĻ������� ����
	SM_CXICON,SM_CYICON ϵͳȱʡ��ͼ��ĸ߶ȺͿ�ȣ�һ��Ϊ32*32�� ����
	SM_CXICONSPACING, ����SM_CYICONSPACING �Դ�ͼ�귽ʽ�鿴Itemʱͼ��֮��ļ�࣬����������Ǵ��ڵ��� ����SM_CXICON and SM_CYICON. ����
	SM_CXMAXIMIZED, ����SM_CYMAXIMIZED ���ڶ������󻯴��ڵ�ȱʡ�ߴ� ����
	SM_CXMAXTRACK, ����SM_CYMAXTRACK ���пɸı�ߴ�߿�ͱ������Ĵ��ڵ�ȱʡ���ߴ磬������ڴ������ �����ߴ磬�����ǲ����ƶ��ġ� ����
	SM_CXMENUCHECK, ����SM_CYMENUCHECK ������Ϊ��λ����Ĳ˵�ѡ�б��λͼ�ĳߴ� ����
	SM_CXMENUSIZE, ����SM_CYMENUSIZE �����ؼ���Ĳ˵�����ť�ĳߴ� ����
	SM_CXMIN,SM_CYMIN �������ܴﵽ����С�ߴ� ����
	SM_CXMINIMIZED, ����SM_CYMINIMIZED ��������С�����ڵĳߴ� ����
	SM_CXMINTRACK, ����SM_CYMINTRACK ��С���پ��룬��ʹ�����϶������ƶ�����С�����ֵ�����ڲ����ƶ��� ����
	SM_CXSCREEN, ����SM_CYSCREEN ������Ϊ��λ�������Ļ�ߴ硣 ����
	SM_CXSIZE,		SM_CYSIZE �����ؼ���ı�������ť�ĳߴ� ����
	SM_CXSIZEFRAME, ����SM_CYSIZEFRAME Χ�ƿɸı��С�Ĵ��ڵı߿�ĺ�� ����
	SM_CXSMICON, ����SM_CYSMICON �����ؼ����Сͼ��ĳߴ磬Сͼ��һ������ڴ��ڱ������ϡ� ����
	SM_CXVSCROLL, ����SM_CYVSCROLL �����ؼ���Ĵ�ֱ�������Ŀ�Ⱥʹ�ֱ�������ϼ�ͷ�ĸ߶� ����
	SM_CYCAPTION �����ؼ������ͨ���ڱ���ĸ߶� ����
	SM_CYMENU �����ؼ���ĵ����˵����ĸ߶� ����
	SM_CYSMCAPTION �����ؼ���Ĵ���С�������ĸ߶� ����
	SM_CYVTHUMB �����ؼ���Ĵ�ֱ�������й�����ĸ߶� ����
	SM_DBCSENABLED ���ΪTRUE��Ϊ0��ֵ����ϵͳ��װ��˫�ֽڰ汾��USER.EXE,ΪFALSE��0���ǡ� ����
	SM_DEBUG ���ΪTRUE��Ϊ0��ֵ����ϵͳ��װ��debug�汾��USER.EXE,ΪFALSE��0���ǡ� ����
	SM_MENUDROPALIGNMENT ���ΪTRUE��Ϊ0��ֵ�����˵����Ҷ���ķ����������ġ� ����
	SM_MOUSEPRESENT ���ΪTRUE��Ϊ0��ֵ��װ����꣬����û�а�װ�� ����
	SM_MOUSEWHEELPRESENT ���ΪTRUE��Ϊ0��ֵ��װ�˹�����꣬����û�а�װ��(Windows NT only) ����
	SM_SWAPBUTTON ���ΪTRUE��Ϊ0��ֵ��������Ҽ�����������û�С�
	*/
}

// ���������ļ�
int CVCheckerClsGlobal::fReadBin(void)
{

	return 0;
}

// ����ID��ȡ��Դ�ļ�
CString CVCheckerClsGlobal::fGetRes(int iResID)
{
	CString strReturn = m_strAppPath;
	switch (iResID)
	{
	case RES_BMP_MAIN_DS:
		strReturn = strReturn + _T("\\res\\��-����.bmp");
		break;
	case RES_BMP_MAIN_XH:
		strReturn = strReturn + _T("\\res\\��-Ѳ��.bmp");
		break;
	case RES_BMP_MAIN_JJ:
		strReturn = strReturn + _T("\\res\\��-����.bmp");
		break;		
	case RES_BMP_MAIN_MX:
		strReturn = strReturn + _T("\\res\\��-�г���ϸ.bmp");
		break;		
	case RES_BMP_MAIN_SZ:
		strReturn = strReturn + _T("\\res\\��-ϵͳ����.bmp");
		break;		
	case RES_BMP_UNIT:
		strReturn = strReturn + _T("\\res\\��λ-��.bmp");
		break;
	case RES_BMP_UNIT_WD:
		strReturn = strReturn + _T("\\res\\��λ-�¶�.bmp");
		break;
	case RES_BMP_UNIT_DY:
		strReturn = strReturn + _T("\\res\\��λ-��ѹ.bmp");
		break;
	case RES_BMP_UNIT_ZS:
		strReturn = strReturn + _T("\\res\\��λ-ת��.bmp");
		break;
	case RES_BMP_UNIT_PJYH:
		strReturn = strReturn + _T("\\res\\��λ-ƽ���ͺ�.bmp");
		break;
	case RES_BMP_UNIT_JSYH:
		strReturn = strReturn + _T("\\res\\��λ-��ʱ�ͺ�.bmp");
		break;
	case RES_BMP_UNIT_BFH:
		strReturn = strReturn + _T("\\res\\��λ-�ٷֺ�.bmp");
		break;
	case RES_BMP_UNIT_LC:
		strReturn = strReturn + _T("\\res\\��λ-���.bmp");
		break;
	case RES_BMP_UNIT_D:
		strReturn = strReturn + _T("\\res\\��λ-��.bmp");
		break;	
	case RES_BMP_UNIT_SS:
		strReturn = strReturn + _T("\\res\\��λ-ʱ��.bmp");
		break;			
	//case RES_BMP_XH_POINTER:
	//	strReturn = strReturn +  _T("\\res\\Ѳ��-����.bmp");
	//	break;
	//case RES_BMP_XH_COMPASS:
	//	strReturn = strReturn + _T("\\res\\Ѳ��-ָ����.bmp");
	//	break;
	//case RES_BMP_JJ_POINTER:
	//	strReturn = strReturn + _T("\\res\\����-����.bmp");
	//	break;	
	}

	return strReturn;
}

/* ����Բ�ģ��뾶���ǶȻ�ָ�뵽DC��
	dc��Ŀ��DC
	pointCircle��Բ��
	iRaduis���뾶
	dAngle���Ƕ�
	iStart����ָ����ʼλ��
	iLen��ָ�볤��
*/
int CVCheckerClsGlobal::fDrawPoint(CDC * dc,CPoint pointCircle,int iRaduis,double dAngle ,int iStart,int iLen)
{	
	if (dc == NULL)
		return 0;
	
	CPoint ptTemp[4];		
	ptTemp[0].x = (int)(pointCircle.x+(iRaduis + iStart-18)*cos((double)((dAngle+87)*PI/180.0)));
	ptTemp[0].y = (int)(pointCircle.y+(iRaduis + iStart-18)*sin((double)((dAngle+87)*PI/180.0)));	

	ptTemp[1].x = (int)(pointCircle.x+(iRaduis + iStart+10)*cos((double)((dAngle+87)*PI/180.0)));
	ptTemp[1].y = (int)(pointCircle.y+(iRaduis + iStart+10)*sin((double)((dAngle+87)*PI/180.0)));			

	ptTemp[2].x = (int)(pointCircle.x+(iRaduis + iLen + iStart+30)*cos((double)((dAngle+90)*PI/180.0)));
	ptTemp[2].y = (int)(pointCircle.y+(iRaduis + iLen + iStart+30)*sin((double)((dAngle+90)*PI/180.0)));	

	ptTemp[3].x = (int)(pointCircle.x+(iRaduis + iStart-18)*cos((double)((dAngle+90)*PI/180.0)));
	ptTemp[3].y = (int)(pointCircle.y+(iRaduis + iStart-18)*sin((double)((dAngle+90)*PI/180.0)));	

	CPoint ptTemp2[4];
	ptTemp2[0].x = (int)(pointCircle.x+(iRaduis + iStart-18)*cos((double)((dAngle+90)*PI/180.0)));
	ptTemp2[0].y = (int)(pointCircle.y+(iRaduis + iStart-18)*sin((double)((dAngle+90)*PI/180.0)));	

	ptTemp2[1].x = (int)(pointCircle.x+(iRaduis + iLen + iStart+30)*cos((double)((dAngle+90)*PI/180.0)));
	ptTemp2[1].y = (int)(pointCircle.y+(iRaduis + iLen + iStart+30)*sin((double)((dAngle+90)*PI/180.0)));	

	ptTemp2[2].x = (int)(pointCircle.x+(iRaduis + iStart+10)*cos((double)((dAngle+93)*PI/180.0)));
	ptTemp2[2].y = (int)(pointCircle.y+(iRaduis + iStart+10)*sin((double)((dAngle+93)*PI/180.0)));	

	ptTemp2[3].x = (int)(pointCircle.x+(iRaduis + iStart-18)*cos((double)((dAngle+93)*PI/180.0)));
	ptTemp2[3].y = (int)(pointCircle.y+(iRaduis + iStart-18)*sin((double)((dAngle+93)*PI/180.0)));	

	//
	CPen penBound(0,1,RGB(231,31,25));
	CPen* pOldPen = dc->SelectObject(&penBound);
	dc->SelectObject(penBound);

	CBrush brushBound(RGB(231,31,25));
	CBrush* pOldBrush = dc->SelectObject(&brushBound);
	dc->SelectObject(brushBound);

	dc->Polygon(ptTemp,4);

	dc->SelectObject(pOldPen);
	dc->SelectObject(pOldBrush);

	DeleteObject(penBound);
	DeleteObject(brushBound);

	CPen penBound2(0,1,RGB(153,0,0));
	CPen* pOldPen2 = dc->SelectObject(&penBound2);
	dc->SelectObject(penBound2);

	CBrush brushBound2(RGB(153,0,0));
	CBrush* pOldBrush2 = dc->SelectObject(&brushBound2);
	dc->SelectObject(brushBound2);

	dc->Polygon(ptTemp2,4);

	dc->SelectObject(pOldPen2);
	dc->SelectObject(pOldBrush2);	

	DeleteObject(penBound2);
	DeleteObject(brushBound2);	

	return 0;
}


// ������ԴID����Դ�����BmpͼƬ
int CVCheckerClsGlobal::fLoadBitmap(HBITMAP hBmp, int iResID)
{
	HINSTANCE hResDll = LoadLibrary(_T("VCheckerResZhCn.dll"));
	if (hResDll == NULL)
	{
		AfxMessageBox(_T("������Դʧ��!"));
		return -1;
	}	

	hBmp = LoadBitmap(hResDll,MAKEINTRESOURCE(iResID));

	FreeLibrary(hResDll);	

	return 0;
}
