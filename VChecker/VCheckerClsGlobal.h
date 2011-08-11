/*
创建:	Yipb	2011-07-20
说明:	公共函数
*/
#pragma once

/*=====全局宏定义begin=====*/

////界面模块
#define PANEL_LOGO	101			//登陆Logo
#define PANEL_MAIN	102			//主界面
#define PANEL_INFO	103			//提示信息
#define PANEL_DSMS	104			//怠速模式
#define PANEL_JJMS	105			//竞技模式
#define PANEL_XHMS	106			//巡航模式
#define PANEL_XCMX	107			//行程明细
#define PANEL_XTSZ	108			//系统设置

#include "e:\Yipb\V-Checker\VChecker\VCheckerResZhCn\resource.h"
//
////资源文件
//#define RES_BMP_MAIN_DS			101			//怠速界面底图
//#define RES_BMP_MAIN_XH			102			//巡航界面底图
//#define RES_BMP_MAIN_JJ			103			//竞技界面底图
//#define RES_BMP_MAIN_MX			104			//行程明细界面底图
//#define RES_BMP_MAIN_SZ			105			//系统设置界面底图
//
//#define RES_BMP_UNIT			200			//无单位底图
//#define RES_BMP_UNIT_WD			201			//温度底图
//#define RES_BMP_UNIT_DY			202			//电压底图
//#define RES_BMP_UNIT_ZS			203			//转速底图
//#define RES_BMP_UNIT_PJYH		204			//平均油耗底图
//#define RES_BMP_UNIT_JSYH		205			//即时油耗底图
//#define RES_BMP_UNIT_BFH		206			//百分号底图
//#define RES_BMP_UNIT_LC			207			//里程底图
//#define RES_BMP_UNIT_D			208			//度底图
//#define RES_BMP_UNIT_SS			209			//时速图
//
//#define RES_BMP_XH_POINTER		301			//巡航指针
//#define RES_BMP_XH_COMPASS		302			//巡航指南针
//#define RES_BMP_JJ_POINTER		303			//竞技指针
/*=====全局宏定义end=====*/

/*=====数据结构定义=====*/
class CVCheckerClsGlobal
{
protected:
	//应用程序路径
	CString m_strAppPath;				
	//应用程序配置文件
	CString m_strConfigFile;

public:
	CVCheckerClsGlobal(void);
	~CVCheckerClsGlobal(void);
	//生成一个新的的GUID编码
	CString fGenerateGuid(void);
	// 产生一个iMin-iMax整数型随机数字
	int fGetRangeRandom(int iMin, int iMax);
	// 获取运行程序路径
	CString fGetAppPath(void);
	// 初始化全局变量
	int fInitGlobalVariable(void);
	// 获取配置文完整路径文件
	CString fGetConfigPathFile(void);
	// 获取屏幕分辨率
	CString fGetScreenResolution(void);
	// 读二进制文件
	int fReadBin(void);
	// 根据ID获取资源文件
	CString fGetRes(int iResID);
	// 根据圆心，半径，角度画指针到DC上
	int fDrawPoint(CDC * dc,CPoint pointCircle,int iRaduis,double dAngle,int iStart = 0,int iLen = 0);
	// 根据资源ID从资源库加载Bmp图片
	int fLoadBitmap(HBITMAP hBmp, int iResID);
};
