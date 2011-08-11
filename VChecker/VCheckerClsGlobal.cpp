
#include "StdAfx.h"
#include "VCheckerClsGlobal.h"
#include "VChecker.h"

CVCheckerClsGlobal::CVCheckerClsGlobal(void)
{
	fInitGlobalVariable();
}

// 初始化全局变量
int CVCheckerClsGlobal::fInitGlobalVariable(void)
{
	m_strAppPath = fGetAppPath();
	m_strConfigFile = _T("\\config.xml");

	return 0;
}

CVCheckerClsGlobal::~CVCheckerClsGlobal(void)
{
}

//生成一个新的的GUID编码
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

// 产生一个iMin-iMax整数型随机数字
int CVCheckerClsGlobal::fGetRangeRandom(int iMin, int iMax)
{
	CTime now = CTime::GetCurrentTime();
	srand(int(now.GetTime()));
	int r = iMin + rand()%(iMax-iMin);
	return r;
}

// 获取运行程序路径
CString CVCheckerClsGlobal::fGetAppPath(void)
{
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	return strPath;
}

// 获取配置文完整路径文件
CString CVCheckerClsGlobal::fGetConfigPathFile(void)
{
	return m_strAppPath + m_strConfigFile;
}

// 获取屏幕分辨率
CString CVCheckerClsGlobal::fGetScreenResolution(void)
{
	int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //屏幕宽度 
	y = GetSystemMetrics(SM_CYSCREEN); //屏幕高度

	CString strReturn;
	strReturn.Format(_T("%dX%d"),x,y);
	return strReturn;

	/*
	SM_CLEANBOOT 返回系统启动方式　 　　
	0 正常启动 　　1 安全模式启动 　　2 网络安全模式启动 　　
	SM_CMOUSEBUTTONS 返回值为系统支持的鼠标键数，返回0，则系统中没有安装鼠标。 　　
	SM_CXBORDER, 　　SM_CYBORDER 返回以像素值为单位的Windows窗口边框的宽度和高度，如果Windows的为3D形态，则 　　等同于SM_CXEDGE参数 　　
	SM_CXCURSOR, 　　SM_CYCURSOR 返回以像素值为单位的标准光标的宽度和高度 　　
	SM_CXDLGFRAME, 　　SM_CYDLGFRAME 等同与SM_CXFIXEDFRAME and SM_CYFIXEDFRAME 　　
	SM_CXDOUBLECLK, 　　SM_CYDOUBLECLK 以像素值为单位的双击有效的矩形区域 　　
	SM_CXEDGE,SM_CYEDGE 以像素值为单位的3D边框的宽度和高度 　　
	SM_CXFIXEDFRAME, 　　SM_CYFIXEDFRAME 围绕具有标题但无法改变尺寸的窗口（通常是一些对话框）的边框的厚度 　　
	SM_CXFRAME,SM_CYFRAME 等同于SM_CXSIZEFRAME and SM_CYSIZEFRAME 　　
	SM_CXFULLSCREEN, 　　SM_CYFULLSCREEN 全屏幕窗口的窗口区域的宽度和高度 　　
	SM_CXHSCROLL, 　　SM_CYHSCROLL 水平滚动条的高度和水平滚动条上箭头的宽度 　　
	SM_CXHTHUMB 以像素为单位的水平滚动条上的滑动块宽度 　　
	SM_CXICON,SM_CYICON 系统缺省的图标的高度和宽度（一般为32*32） 　　
	SM_CXICONSPACING, 　　SM_CYICONSPACING 以大图标方式查看Item时图标之间的间距，这个距离总是大于等于 　　SM_CXICON and SM_CYICON. 　　
	SM_CXMAXIMIZED, 　　SM_CYMAXIMIZED 处于顶层的最大化窗口的缺省尺寸 　　
	SM_CXMAXTRACK, 　　SM_CYMAXTRACK 具有可改变尺寸边框和标题栏的窗口的缺省最大尺寸，如果窗口大于这个 　　尺寸，窗口是不可移动的。 　　
	SM_CXMENUCHECK, 　　SM_CYMENUCHECK 以像素为单位计算的菜单选中标记位图的尺寸 　　
	SM_CXMENUSIZE, 　　SM_CYMENUSIZE 以像素计算的菜单栏按钮的尺寸 　　
	SM_CXMIN,SM_CYMIN 窗口所能达到的最小尺寸 　　
	SM_CXMINIMIZED, 　　SM_CYMINIMIZED 正常的最小化窗口的尺寸 　　
	SM_CXMINTRACK, 　　SM_CYMINTRACK 最小跟踪距离，当使用者拖动窗口移动距离小于这个值，窗口不会移动。 　　
	SM_CXSCREEN, 　　SM_CYSCREEN 以像素为单位计算的屏幕尺寸。 　　
	SM_CXSIZE,		SM_CYSIZE 以像素计算的标题栏按钮的尺寸 　　
	SM_CXSIZEFRAME, 　　SM_CYSIZEFRAME 围绕可改变大小的窗口的边框的厚度 　　
	SM_CXSMICON, 　　SM_CYSMICON 以像素计算的小图标的尺寸，小图标一般出现在窗口标题栏上。 　　
	SM_CXVSCROLL, 　　SM_CYVSCROLL 以像素计算的垂直滚动条的宽度和垂直滚动条上箭头的高度 　　
	SM_CYCAPTION 以像素计算的普通窗口标题的高度 　　
	SM_CYMENU 以像素计算的单个菜单条的高度 　　
	SM_CYSMCAPTION 以像素计算的窗口小标题栏的高度 　　
	SM_CYVTHUMB 以像素计算的垂直滚动条中滚动块的高度 　　
	SM_DBCSENABLED 如果为TRUE或不为0的值表明系统安装了双字节版本的USER.EXE,为FALSE或0则不是。 　　
	SM_DEBUG 如果为TRUE或不为0的值表明系统安装了debug版本的USER.EXE,为FALSE或0则不是。 　　
	SM_MENUDROPALIGNMENT 如果为TRUE或不为0的值下拉菜单是右对齐的否则是左对齐的。 　　
	SM_MOUSEPRESENT 如果为TRUE或不为0的值则安装了鼠标，否则没有安装。 　　
	SM_MOUSEWHEELPRESENT 如果为TRUE或不为0的值则安装了滚轮鼠标，否则没有安装。(Windows NT only) 　　
	SM_SWAPBUTTON 如果为TRUE或不为0的值则鼠标左右键交换，否则没有。
	*/
}

// 读二进制文件
int CVCheckerClsGlobal::fReadBin(void)
{

	return 0;
}

// 根据ID获取资源文件
CString CVCheckerClsGlobal::fGetRes(int iResID)
{
	CString strReturn = m_strAppPath;
	switch (iResID)
	{
	case RES_BMP_MAIN_DS:
		strReturn = strReturn + _T("\\res\\底-怠速.bmp");
		break;
	case RES_BMP_MAIN_XH:
		strReturn = strReturn + _T("\\res\\底-巡航.bmp");
		break;
	case RES_BMP_MAIN_JJ:
		strReturn = strReturn + _T("\\res\\底-竞技.bmp");
		break;		
	case RES_BMP_MAIN_MX:
		strReturn = strReturn + _T("\\res\\底-行程明细.bmp");
		break;		
	case RES_BMP_MAIN_SZ:
		strReturn = strReturn + _T("\\res\\底-系统设置.bmp");
		break;		
	case RES_BMP_UNIT:
		strReturn = strReturn + _T("\\res\\单位-空.bmp");
		break;
	case RES_BMP_UNIT_WD:
		strReturn = strReturn + _T("\\res\\单位-温度.bmp");
		break;
	case RES_BMP_UNIT_DY:
		strReturn = strReturn + _T("\\res\\单位-电压.bmp");
		break;
	case RES_BMP_UNIT_ZS:
		strReturn = strReturn + _T("\\res\\单位-转速.bmp");
		break;
	case RES_BMP_UNIT_PJYH:
		strReturn = strReturn + _T("\\res\\单位-平均油耗.bmp");
		break;
	case RES_BMP_UNIT_JSYH:
		strReturn = strReturn + _T("\\res\\单位-即时油耗.bmp");
		break;
	case RES_BMP_UNIT_BFH:
		strReturn = strReturn + _T("\\res\\单位-百分号.bmp");
		break;
	case RES_BMP_UNIT_LC:
		strReturn = strReturn + _T("\\res\\单位-里程.bmp");
		break;
	case RES_BMP_UNIT_D:
		strReturn = strReturn + _T("\\res\\单位-度.bmp");
		break;	
	case RES_BMP_UNIT_SS:
		strReturn = strReturn + _T("\\res\\单位-时速.bmp");
		break;			
	//case RES_BMP_XH_POINTER:
	//	strReturn = strReturn +  _T("\\res\\巡航-表针.bmp");
	//	break;
	//case RES_BMP_XH_COMPASS:
	//	strReturn = strReturn + _T("\\res\\巡航-指南针.bmp");
	//	break;
	//case RES_BMP_JJ_POINTER:
	//	strReturn = strReturn + _T("\\res\\竞技-表针.bmp");
	//	break;	
	}

	return strReturn;
}

/* 根据圆心，半径，角度画指针到DC上
	dc：目标DC
	pointCircle：圆心
	iRaduis：半径
	dAngle：角度
	iStart：画指针起始位置
	iLen：指针长度
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


// 根据资源ID从资源库加载Bmp图片
int CVCheckerClsGlobal::fLoadBitmap(HBITMAP hBmp, int iResID)
{
	HINSTANCE hResDll = LoadLibrary(_T("VCheckerResZhCn.dll"));
	if (hResDll == NULL)
	{
		AfxMessageBox(_T("加载资源失败!"));
		return -1;
	}	

	hBmp = LoadBitmap(hResDll,MAKEINTRESOURCE(iResID));

	FreeLibrary(hResDll);	

	return 0;
}
