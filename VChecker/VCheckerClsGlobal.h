/*
����:	Yipb	2011-07-20
˵��:	��������
*/
#pragma once

/*=====ȫ�ֺ궨��begin=====*/

////����ģ��
#define PANEL_LOGO	101			//��½Logo
#define PANEL_MAIN	102			//������
#define PANEL_INFO	103			//��ʾ��Ϣ
#define PANEL_DSMS	104			//����ģʽ
#define PANEL_JJMS	105			//����ģʽ
#define PANEL_XHMS	106			//Ѳ��ģʽ
#define PANEL_XCMX	107			//�г���ϸ
#define PANEL_XTSZ	108			//ϵͳ����

#define RES_STRING_MAX_LEN	50	//�ַ���󳤶�
//ʹ����Դ��ͷ�ļ��������Ե�ʱ���޸ĸ�ͷ�ļ�����
#include "e:\Yipb\Projects\VChecker\VCheckerResZhCn\resource.h"

/*=====ȫ�ֺ궨��end=====*/

class CVCheckerClsGlobal
{
protected:
	//Ӧ�ó���·��
	CString m_strAppPath;				
	//Ӧ�ó��������ļ�
	CString m_strConfigFile;

public:
	CVCheckerClsGlobal(void);
	~CVCheckerClsGlobal(void);
	//����һ���µĵ�GUID����
	CString fGenerateGuid(void);
	// ����һ��iMin-iMax�������������
	int fGetRangeRandom(int iMin, int iMax);
	// ��ȡ���г���·��
	CString fGetAppPath(void);
	// ��ʼ��ȫ�ֱ���
	int fInitGlobalVariable(void);
	// ��ȡ����������·���ļ�
	CString fGetConfigPathFile(void);
	// ��ȡ��Ļ�ֱ���
	CString fGetScreenResolution(void);
	// ���������ļ�
	int fReadBin(void);
	// ����ID��ȡ�ַ���
	CString fGetRes(int iResID);
	// ����Բ�ģ��뾶���ǶȻ�ָ�뵽DC��
	int fDrawPoint(CDC * dc,CPoint pointCircle,int iRaduis,double dAngle,int iStart = 0,int iLen = 0);
	// ������ԴID����Դ�����BmpͼƬ
	int fLoadBitmap(HBITMAP hBmp, int iResID);
};
