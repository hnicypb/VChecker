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

#include "e:\Yipb\V-Checker\VChecker\VCheckerResZhCn\resource.h"
//
////��Դ�ļ�
//#define RES_BMP_MAIN_DS			101			//���ٽ����ͼ
//#define RES_BMP_MAIN_XH			102			//Ѳ�������ͼ
//#define RES_BMP_MAIN_JJ			103			//���������ͼ
//#define RES_BMP_MAIN_MX			104			//�г���ϸ�����ͼ
//#define RES_BMP_MAIN_SZ			105			//ϵͳ���ý����ͼ
//
//#define RES_BMP_UNIT			200			//�޵�λ��ͼ
//#define RES_BMP_UNIT_WD			201			//�¶ȵ�ͼ
//#define RES_BMP_UNIT_DY			202			//��ѹ��ͼ
//#define RES_BMP_UNIT_ZS			203			//ת�ٵ�ͼ
//#define RES_BMP_UNIT_PJYH		204			//ƽ���ͺĵ�ͼ
//#define RES_BMP_UNIT_JSYH		205			//��ʱ�ͺĵ�ͼ
//#define RES_BMP_UNIT_BFH		206			//�ٷֺŵ�ͼ
//#define RES_BMP_UNIT_LC			207			//��̵�ͼ
//#define RES_BMP_UNIT_D			208			//�ȵ�ͼ
//#define RES_BMP_UNIT_SS			209			//ʱ��ͼ
//
//#define RES_BMP_XH_POINTER		301			//Ѳ��ָ��
//#define RES_BMP_XH_COMPASS		302			//Ѳ��ָ����
//#define RES_BMP_JJ_POINTER		303			//����ָ��
/*=====ȫ�ֺ궨��end=====*/

/*=====���ݽṹ����=====*/
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
	// ����ID��ȡ��Դ�ļ�
	CString fGetRes(int iResID);
	// ����Բ�ģ��뾶���ǶȻ�ָ�뵽DC��
	int fDrawPoint(CDC * dc,CPoint pointCircle,int iRaduis,double dAngle,int iStart = 0,int iLen = 0);
	// ������ԴID����Դ�����BmpͼƬ
	int fLoadBitmap(HBITMAP hBmp, int iResID);
};
