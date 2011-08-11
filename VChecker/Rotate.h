// Rotate.h: interface for the CRotate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROTATE_H__F1AC2823_A2EA_437F_BBDB_E1E581754947__INCLUDED_)
#define AFX_ROTATE_H__F1AC2823_A2EA_437F_BBDB_E1E581754947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define PI 3.14159265358979
#define Rad 1.74532925199433E-02
#define BPC 4 //Weird behaviour if set to 3Bytes per color
#define LEFT BPC
#define FAILED_GETTING_BACKGROUND_BITS -1
#define FAILED_GETTING_IMAGE_BITS -2
#define FAILED_TO_ALLOCATE_MEMORY -3
#define FAILED_TO_DRAWIMAGE -4

enum {
	ccTA_2, ccTC_2, D50_2, D55_2, D65_2, D75_2, F2_2, F7_2, F11_2,
		ccTA_10, ccTC_10, D50_10, D55_10, D65_10, D75_10, F2_10, F7_10, F11_10,
		ccNTristimulus
};

enum { ccX, ccY, ccZ};

/*
 *	Tristimulus reference values
 */
const double _ccTristimulusValues[ccNTristimulus][3] = 
{
      /* 2 degrees */
  /*ccTA_2*/{109.850, 100.000, 35.585},
  /*ccTC_2*/{98.074,  100.000, 118.232},
  /* D50 */ {96.422,  100.000, 82.521},
  /* D55 */ {95.682,  100.000, 92.149},
  /* D65 */ {95.047,  100.000, 108.883},
  /* D75 */ {94.972,  100.000, 122.638},
  /* F2 */  {99.187,  100.000, 67.395},
  /* F7 */  {95.044,  100.000, 108.755},
  /* F11 */ {100.966, 100.000, 64.370},

      /* 10 degrees */
  /* A */   {111.144, 100.000, 35.200},
  /* C */   {97.285,  100.000, 116.145},
  /* D50 */ {96.720,  100.000, 81.427},
  /* D55 */ {95.799,  100.000, 90.926},
  /* D65 */ {94.811,  100.000, 107.304},
  /* D75 */ {94.416,  100.000, 120.641},
  /* F2 */  {103.280, 100.000, 69.026},
  /* F7 */  {95.792,  100.000, 107.687},
  /* F11 */ {103.866, 100.000, 65.627}
};

class CRotate  
{
public:
	double enclose(double a);
	double norm(double a);
	/*
	aHDC : 目标设备上下文 (.hdc  picturebox 需要设 scalemode=pixels 和 autoredraw=true)
	Angle : 旋转角度值 (360 度 = 2*pi)
	X : 目标 X 坐标
	Y : 目标 Y 坐标
	W : 原始图片宽度
	H : 原始图片高度
	PicDC: 原始图片设备上下文 (.hdc picturebox 需要设 scalemode=pixels 和 autoredraw=true)
	SrcX: 原目标左上角矩形 X坐标 (从哪个位置复制. 复制位图局部时有用)
	SrcY:  原目标左上角矩形 Y坐标
	pScale :图片缩放值(用1为100%,0.5为50%,2为200%等)
	TraspColor : 整数(3字节)表达RGB值的透明色
	Alpha :  0 和 1 用来表示是否透明
	Hue : 图像色调偏移量(色调就像光的波长的颜色)
	Sat : 饱和度 
	Lum :亮度
	*/
	int rotatedc(HDC DestDC, float Angle, int x, int y, int w, int h, HDC SrcDC, int srcx, int srcy, float pScale, int TranspColor, float Alpha, float Hue, float Sat, float Lum);
	int CMYKtoCMY(double c, double m, double y, double k, double* C, double* M, double* Y);
	int CMYtoCMYK(double c, double m, double y, double* C, double* M, double* Y, double* K);
	int CMYtoiRGB(double c, double m, double y, int* r, int* g, int* b);
	int CMYtofRGB(double c, double m, double y, double* r, double* g, double* b);
	int iRGBtoCMY(int r, int g, int b, double* c, double* m, double* y);
	int fRGBtoCMY(double r, double g, double b, double* c, double* m, double* y);
	int HSVtoRGB(double h, double s, double v, double* r, double* g, double* b);
	int RGBtoHSV(double r, double g, double b, double* h, double* s, double* v);
	int HSLtoRGB(double h, double s, double l, double* r, double* g, double* b);
	int RGBtoHSL(double L, double a, double b, double* h, double* s, double* l);
	int CIE_LuvtoXYZ(double L, double u, double v, double* x, double* y, double* z, char ObsIll);
	int XYZtoCIE_Luv(double x, double y, double z, double* L, double* u, double* v, char ObsIll);
	int CIE_LCHtoCIE_Lab(double L, double C, double H, double* rL, double* ra, double* rb);
	int CIE_LabtoCIE_LCH(double L, double a, double b, double* rL, double* rC, double* rH);
	int CIE_LabtoXYZ(double L, double a, double b, double* x, double* y, double* z, char ObsIll);
	int XYZtoCIE_Lab(double x, double y, double z, double* L, double* a, double* b, char ObsIll);
	int HunterLabtoXYZ(double L, double a, double b, double* x, double* y, double* z);
	int XYZtoHunterLab(double x, double y, double z, double* L, double* a, double* b);
	int YxytoXYZ(double Y, double x, double y, double* rx, double* ry, double* rz);
	int XYZtoYxy(double x, double y, double z, double* rY, double* rx, double* ry);
	int ccRGBtoXYZ(double r, double g, double b, double* x, double* y, double* z, char ObsIll);
	int ccXYZtoRGB(double x, double y, double z, double* r, double* g, double* b, char ObsIll);
	CRotate();
	virtual ~CRotate();

	void SaveDCToBMP(HDC hDC,int nStartX,int nStartY,int nWidth,int nHeight,LPCTSTR szFileName);
};

#endif // !defined(AFX_ROTATE_H__F1AC2823_A2EA_437F_BBDB_E1E581754947__INCLUDED_)
