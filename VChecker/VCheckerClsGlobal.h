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

#define RES_STRING_MAX_LEN	50	//字符最大长度
//使用资源的头文件，多语言的时候修改该头文件即可
#include "e:\Yipb\Projects\VChecker\VCheckerResZhCn\resource.h"

/*=====全局宏定义end=====*/

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
	// 根据ID获取字符串
	CString fGetRes(int iResID);
	// 根据圆心，半径，角度画指针到DC上
	int fDrawPoint(CDC * dc,CPoint pointCircle,int iRaduis,double dAngle,int iStart = 0,int iLen = 0);
	// 根据资源ID从资源库加载Bmp图片
	int fLoadBitmap(HBITMAP hBmp, int iResID);
};
