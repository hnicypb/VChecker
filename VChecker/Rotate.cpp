// Rotate.cpp: implementation of the CRotate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rotate.h"
#include<assert.h>
#include<math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


static double ccmin(double val1, double val2, double val3)
{
	if (val1 < val2)
	{
		if(val1 < val3) return val1;
		else return val3;
	}
	else if (val2 < val3)
		return val2;
	return val3;
}

static double ccmax(double val1, double val2, double val3)
{
	if (val1 > val2)
	{
		if(val1 > val3) return val1;
		else return val3;
	}
	else if (val2 > val3)
		return val2;
	return val3;
}

static double Hue_2_RGB( double v1, double v2, double vH )
{
	if ( vH < 0 ) vH += 1;
	if ( vH > 1 ) vH -= 1;
	if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
	if ( ( 2 * vH ) < 1 ) return ( v2 );
	if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2./3 ) - vH ) * 6 );
	return ( v1 );
}

static double degree_2_radian(double val)
{
	return (val*PI)/180;
}

CRotate::CRotate()
{

}

CRotate::~CRotate()
{

}

//RGB values = From 0 to 1
int CRotate::RGBtoHSL(double r, double g, double b, double* h, double* s, double* l)
{
  double vmin, vmax, delta;
  double dr,dg,db;

  vmin = ccmin( r, g, b );                // Min. value of RGB
  vmax = ccmax( r, g, b );                // Max. value of RGB
  delta = vmax - vmin;                    // Delta RGB value

  *l = ( vmax + vmin ) / 2;

  if ( delta == 0 )                     // This is a gray, no chroma...
  {
     *h = 0;                            // HSL results = From 0 to 1
     *s = 0;
  }
  else                                  // Chromatic data...
  {
     if ( *l < 0.5 ) *s = delta / ( vmax + vmin );
     else            *s = delta / ( 2 - vmax - vmin );

     dr = ( ( ( vmax - r ) / 6.0 ) + ( delta / 2.0 ) ) / delta;
     dg = ( ( ( vmax - g ) / 6.0 ) + ( delta / 2.0 ) ) / delta;
     db = ( ( ( vmax - b ) / 6.0 ) + ( delta / 2.0 ) ) / delta;

     if      ( r == vmax ) *h = db - dg;
     else if ( g == vmax ) *h = ( 1.0/3.0 ) + dr - db;
     else if ( b == vmax ) *h = ( 2.0/3.0 ) + dg - dr;

     if ( *h < 0 ) *h += 1;
     if ( *h > 1 ) *h -= 1;
  }

  return 1;
}

int CRotate::HSLtoRGB(double h, double s, double l, double* r, double* g, double* b)
{
  double v1, v2;

  if ( s == 0 )                       // HSL values = From 0 to 1
  {
     *r = l ;                     // RGB results = From 0 to 1
     *g = l ;
     *b = l ;
  }
  else
  {
     if ( l < 0.5 ) 
       v2 = l * ( 1 + s );
     else           
       v2 = ( l + s ) - ( s * l );

     v1 = 2 * l - v2;

     *r = Hue_2_RGB( v1, v2, h + ( 1.0/3.0 ) );
     *g =  Hue_2_RGB( v1, v2, h );
     *b =  Hue_2_RGB( v1, v2, h - ( 1.0/3.0 ) );
  } 

  return 1;

}


// RGB values = From 0 to 1
int CRotate::fRGBtoCMY(double r, double g, double b, double* c, double* m, double* y)
{
  assert(c && m && y);
  *c = 1 - r;
  *m = 1 - g;
  *y = 1 - b;

  return 1;
}

// RGB values = From 0 to 255
int CRotate::iRGBtoCMY(int r, int g, int b, double* c, double* m, double* y)
{
  assert(c && m && y);
  assert(r >= 0 && r < 256);
  assert(g >= 0 && g < 256);
  assert(b >= 0 && b < 256);

  *c = 1 - ( (double)r / 255 );
  *m = 1 - ( (double)g / 255 );
  *y = 1 - ( (double)b / 255 );

  return 1;
}

// CMY values = From 0 to 255
int CRotate::CMYtofRGB(double c, double m, double y, double* r, double* g, double* b)
{
  assert(r && g && b);
  assert(c >= 0 && c <= 1);
  assert(m >= 0 && m <= 1);
  assert(y >= 0 && y <= 1);

  *r = ( 1 - c );
  *g = ( 1 - m );
  *b = ( 1 - y );

  return 1;

}
// CMY values = From 0 to 1
int CRotate::CMYtoiRGB(double c, double m, double y, int* r, int* g, int* b)
{
  assert(r && g && b);
  assert(c >= 0 && c <= 1);
  assert(m >= 0 && m <= 1);
  assert(y >= 0 && y <= 1);

  *r = (int)( 1 - c ) * 255;
  *g = (int)( 1 - m ) * 255;
  *b = (int)( 1 - y ) * 255;

  return 1;
}


// CMY values = From 0 to 1
int CRotate::CMYtoCMYK(double c, double m, double y, double* C, double* M, double* Y, double* K)
{
  double var_K = 1;

  assert(C && M && Y && K);
  assert(c >= 0 && c <= 1);
  assert(m >= 0 && m <= 1);
  assert(y >= 0 && y <= 1);

  if ( c < var_K )
    var_K = c;
  if ( m < var_K )
    var_K = m;
  if ( y < var_K )
    var_K = y;

  *C = ( c - var_K ) / ( 1 - var_K );
  *M = ( m - var_K ) / ( 1 - var_K );
  *Y = ( y - var_K ) / ( 1 - var_K );
  *K = var_K;

  return 1;
}

// CMYK values = From 0 to 1
int CRotate::CMYKtoCMY(double c, double m, double y, double k, double* C, double* M, double* Y)
{
  assert(C && M && Y);
  assert(c >= 0 && c <= 1);
  assert(m >= 0 && m <= 1);
  assert(y >= 0 && y <= 1);
  assert(k >= 0 && k <= 1);

  *C = ( c * ( 1 - k ) + k );
  *M = ( m * ( 1 - k ) + k );
  *Y = ( y * ( 1 - k ) + k );
 
  return 1;
}

int CRotate::RGBtoHSV(double r, double g, double b, double* h, double* s, double* v)
{
  double var_Min;
  double var_Max;
  double del_Max;

  var_Min  = ccmin( r, g, b );    //Min. value of RGB
  var_Max  = ccmax( r, g, b );    //Max. value of RGB
  del_Max = var_Max - var_Min;    //Delta RGB value 

  *v = var_Max;

  if ( del_Max == 0 )                      // This is a gray, no chroma...
  {
     *h = 0;                               // HSV results = From 0 to 1
     *s = 0;
  }
  else                                     // Chromatic data...
  {
     double del_R = ( ( ( var_Max - r ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
     double del_G = ( ( ( var_Max - g ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
     double del_B = ( ( ( var_Max - b ) / 6 ) + ( del_Max / 2 ) ) / del_Max;

     *s = del_Max / var_Max;


     if      ( r == var_Max ) *h = del_B - del_G;
     else if ( g == var_Max ) *h = ( 1./3 ) + del_R - del_B;
     else if ( b == var_Max ) *h = ( 2./3 ) + del_G - del_R;

     if ( *h < 0 ) ; 
	 *h += 1;
     if ( *h > 1 ) ; 
	 *h -= 1;
  }

  return 1;
}

int CRotate::HSVtoRGB(double h, double s, double v, double* r, double* g, double* b)
{
  if ( s == 0 )                       // HSV values = From 0 to 1
  {
     *r = v;
     *g = v;
     *b = v;
  }
  else
  {
     double var_h = h * 6;
     double var_i = floor( var_h );
     double var_1 = v * ( 1 - s );
     double var_2 = v * ( 1 - s * ( var_h - var_i ) );
     double var_3 = v * ( 1 - s * ( 1 - ( var_h - var_i ) ) );

     if      ( var_i == 0 ) { *r = v     ; *g = var_3 ; *b = var_1; }
     else if ( var_i == 1 ) { *r = var_2 ; *g = v     ; *b = var_1; }
     else if ( var_i == 2 ) { *r = var_1 ; *g = v     ; *b = var_3; }
     else if ( var_i == 3 ) { *r = var_1 ; *g = var_2 ; *b = v;     }
     else if ( var_i == 4 ) { *r = var_3 ; *g = var_1 ; *b = v;     }
     else                   { *r = v     ; *g = var_1 ; *b = var_2; }

  }

  return 1;
}

int CRotate::XYZtoHunterLab(double x, double y, double z, double* L, double* a, double* b)
{
  *L = 10 * sqrt( y );
  *a = 17.5 * ( ( ( 1.02 * x ) - y ) / sqrt( y ) );
  *b = 7 * ( ( y - ( 0.847 * z ) ) / sqrt( y ) );

  return 1;
}

int CRotate::HunterLabtoXYZ(double L, double a, double b, double* x, double* y, double* z)
{
  double var_Y = L / 10;
  double var_X = a / 17.5 * L / 10;
  double var_Z = b / 7 * L / 10;

  *y = pow(var_Y,2);
  *x = ( var_X + *y ) / 1.02;
  *z = -( var_Z - *y ) / 0.847;

  return 1;
}

int CRotate::XYZtoYxy(double x, double y, double z, double* rY, double* rx, double* ry)
{
  *rY = y;
  *rx = x / ( x + y + z );
  *ry = y / ( x + y + z );

  return 1;
}

int CRotate::YxytoXYZ(double Y, double x, double y, double* rx, double* ry, double* rz)
{
  //Y = From 0 to 100
  //x = From 0 to 1
  //y = From 0 to 1

  *rx = x * ( Y / y );
  *ry = Y;
  *rz = ( 1 - x - y ) * ( Y / y );

  return 1;
}

//r,g,b from 0 to 1
int CRotate::ccXYZtoRGB(double x, double y, double z, double* r, double* g, double* b, char ObsIll)
{
  double ref_X = _ccTristimulusValues[ObsIll][ccX];
  double ref_Y = _ccTristimulusValues[ObsIll][ccY];
  double ref_Z = _ccTristimulusValues[ObsIll][ccZ];

  double var_X = x / 100;        //X = From 0 to ref_X
  double var_Y = y / 100;        //Y = From 0 to ref_Y
  double var_Z = z / 100;        //Z = From 0 to ref_Y

  double var_R = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
  double var_G = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415;
  double var_B = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570;

  if ( var_R > 0.0031308 ) var_R = 1.055 * ( pow(var_R,( 1 / 2.4 )) ) - 0.055;
  else                     var_R = 12.92 * var_R;
  if ( var_G > 0.0031308 ) var_G = 1.055 * ( pow(var_G,( 1 / 2.4 )) ) - 0.055;
  else                     var_G = 12.92 * var_G;
  if ( var_B > 0.0031308 ) var_B = 1.055 * ( pow(var_B,( 1 / 2.4 )) ) - 0.055;
  else                     var_B = 12.92 * var_B;

  *r = var_R;
  *g = var_G;
  *b = var_B;

  return 1;
}

int CRotate::ccRGBtoXYZ(double r, double g, double b, double* x, double* y, double* z, char ObsIll)
{
  double var_R = r;        //R = From 0 to 255
  double var_G = g;        //G = From 0 to 255
  double var_B = b;        //B = From 0 to 255

  if ( var_R > 0.04045 ) var_R = pow(( ( var_R + 0.055 ) / 1.055 ),2.4);
  else                   var_R = var_R / 12.92;
  if ( var_G > 0.04045 ) var_G = pow(( ( var_G + 0.055 ) / 1.055 ),2.4);
  else                   var_G = var_G / 12.92;
  if ( var_B > 0.04045 ) var_B = pow(( ( var_B + 0.055 ) / 1.055 ),2.4);
  else                   var_B = var_B / 12.92;

  var_R = var_R * 100;
  var_G = var_G * 100;
  var_B = var_B * 100;

  *x = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
  *y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
  *z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;

  return 1;
}

int CRotate::XYZtoCIE_Lab(double x, double y, double z, double* L, double* a, double* b, char ObsIll)
{
  double var_X = x/_ccTristimulusValues[ObsIll][ccX];
  double var_Y = y/_ccTristimulusValues[ObsIll][ccY];
  double var_Z = z/_ccTristimulusValues[ObsIll][ccZ];

  if ( var_X > 0.008856 ) var_X = pow(var_X,( 1./3 ));
  else                    var_X = ( 7.787 * var_X ) + ( 16./ 116 );
  if ( var_Y > 0.008856 ) var_Y = pow(var_Y,( 1./3 ));
  else                    var_Y = ( 7.787 * var_Y ) + ( 16./ 116 );
  if ( var_Z > 0.008856 ) var_Z = pow(var_Z,( 1./3 ));
  else                    var_Z = ( 7.787 * var_Z ) + ( 16./ 116 );

  *L = ( 116 * var_Y ) - 16;
  *a = 500 * ( var_X - var_Y );
  *b = 200 * ( var_Y - var_Z );

  return 1;
}

int CRotate::CIE_LabtoXYZ(double L, double a, double b, double* x, double* y, double* z, char ObsIll)
{
  double var_Y = ( L + 16 ) / 116;
  double var_X = a / 500 + var_Y;
  double var_Z = var_Y - b / 200;

  if ( pow(var_Y,3) > 0.008856 ) var_Y = pow(var_Y,3);
  else                      var_Y = ( var_Y - 16./ 116 ) / 7.787;
  if ( pow(var_X,3) > 0.008856 ) var_X = pow(var_X,3);
  else                      var_X = ( var_X - 16./ 116 ) / 7.787;
  if ( pow(var_Z,3) > 0.008856 ) var_Z = pow(var_Z,3);
  else                      var_Z = ( var_Z - 16./ 116 ) / 7.787;

  *x = _ccTristimulusValues[ObsIll][ccX] * var_X;
  *y = _ccTristimulusValues[ObsIll][ccY] * var_Y;
  *z = _ccTristimulusValues[ObsIll][ccZ] * var_Z;

  return 1;
}

int CRotate::CIE_LabtoCIE_LCH(double L, double a, double b, double* rL, double* rC, double* rH)
{
  double var_H = atan2( b, a );  //Quadrant by signs

  if ( var_H > 0 ) var_H = ( var_H / PI ) * 180;
  else             var_H = 360 - ( (int)var_H / PI ) * 180;

  *rL = L;
  *rC = sqrt( pow(a,2) + pow(b,2) );
  *rH = var_H;

  return 1;
}

int CRotate::CIE_LCHtoCIE_Lab(double L, double C, double H, double* rL, double* ra, double* rb)
{
  //CIE-H?= From 0 to 360?

  *rL = L;
  *ra = cos( degree_2_radian(H) ) * C;
  *rb = sin( degree_2_radian(H) ) * C;

  return 1;
}

int CRotate::XYZtoCIE_Luv(double x, double y, double z, double* L, double* u, double* v, char ObsIll)
{
  double ref_X = _ccTristimulusValues[ObsIll][ccX];
  double ref_Y = _ccTristimulusValues[ObsIll][ccY];
  double ref_Z = _ccTristimulusValues[ObsIll][ccZ];
  
  double ref_U = ( 4 * ref_X ) / ( ref_X + ( 15 * ref_Y ) + ( 3 * ref_Z ) );
  double ref_V = ( 9 * ref_Y ) / ( ref_X + ( 15 * ref_Y ) + ( 3 * ref_Z ) );

  double var_U = ( 4 * x ) / ( x + ( 15 * y ) + ( 3 * z ) );
  double var_V = ( 9 * y ) / ( x + ( 15 * y ) + ( 3 * z ) );
  double var_Y = y / 100;

  
  if ( var_Y > 0.008856 ) var_Y = pow(var_Y,( 1./3 ));
  else                    var_Y = ( 7.787 * var_Y ) + ( 16./ 116 );


  *L = ( 116 * var_Y ) - 16;
  *u = 13 * *L * ( var_U - ref_U );
  *v = 13 * *L * ( var_V - ref_V );

  return 1;
}

int CRotate::CIE_LuvtoXYZ(double L, double u, double v, double* x, double* y, double* z, char ObsIll)
{
  double ref_X = _ccTristimulusValues[ObsIll][ccX];
  double ref_Y = _ccTristimulusValues[ObsIll][ccY];
  double ref_Z = _ccTristimulusValues[ObsIll][ccZ];

  double ref_U = ( 4 * ref_X ) / ( ref_X + ( 15 * ref_Y ) + ( 3 * ref_Z ) );
  double ref_V = ( 9 * ref_Y ) / ( ref_X + ( 15 * ref_Y ) + ( 3 * ref_Z ) );

  double var_U = u / ( 13 * L ) + ref_U;
  double var_V = v / ( 13 * L ) + ref_V;

  double var_Y = ( L + 16 ) / 116;
  
  if ( pow(var_Y,3) > 0.008856 ) var_Y = pow(var_Y,3);
  else                      var_Y = ( var_Y - 16./ 116 ) / 7.787;

  (*y) = var_Y * 100;
  (*x) =  - ( 9 * *y * var_U ) / ( ( var_U - 4 ) * var_V  - var_U * var_V );
  (*z) = ( 9 * *y - ( 15 * var_V * *y ) - ( var_V * *x ) ) / ( 3 * var_V );

  return 1;
}
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
int CRotate::rotatedc(HDC DestDC, float Angle, int x, int y, int w, int h, HDC SrcDC, int srcx, int srcy, 
					  float pScale, int TranspColor, float Alpha, float Hue, float Sat, float Lum)
{
	int px, py, CX, CY, XX, YY, ix, iy, dw, dh;
  BYTE *BackgroundImg, *OriginalImg, *RotatedImg, *TransparancyMap;
  BYTE tR, tG, tB;
  BITMAPINFO BackBmp, PicBmp, RotBmp; 
  HDC BackDC, PicDC;
  HBITMAP iBitmap, ImgHandle;
  LPBYTE pBits;
  double PCos, PSin, tx, ty, dx, dy, hh, ss, vv, rr, gg, bb;
  double TopL, TopR, BotL, BotR, TopLV, TopRV, BotLV, BotRV;
  int Pixel, DestPixel, Bixel;
  BYTE BackgroundCol;
  int DDown, DOWN;

  //Calculate the trigonometry in order to find destination dimensions
  PCos = cos(Angle) * pScale;
  PSin = sin(Angle) * pScale;
    
  //Find destination width and height
  dw = (int)ceil(fabs(h * PSin) + fabs(w * PCos));
  dh = (int)ceil(fabs(h * PCos) + fabs(w * PSin));

  //Precalculate the trigonometry to use in rotation
  PCos = cos(Angle) / pScale;
  PSin = sin(Angle) / pScale;

  //used to move through the 3D array in a 1D style                  
  DDown = dw * BPC;     //DDown = 1 Row Down on the Dest Image
  DOWN = w * BPC ;      //DOWN = 1 Row Down on the Original Image
                        //LEFT = 1 Colum Left on either image

  //Pivot coordinates
  px = w / 2;
  py = h / 2;
  
  //Allocate memory for each pixel (4 Bytes for color * Width * Heighr)
  BackgroundImg = (BYTE*)malloc(BPC * dw * dh);
  OriginalImg = (BYTE*)malloc(BPC * w * h); 
  TransparancyMap = (BYTE*)malloc(w * h); 
  RotatedImg = (BYTE*)malloc(BPC * dw * dh);
  //If a pointer returns NULL then memory was not allocated
  if (!BackgroundImg || !OriginalImg|| !RotatedImg || !TransparancyMap) 
     return FAILED_TO_ALLOCATE_MEMORY;
  //Clear the Rotated image memory (no need because it will be initialized with memcpy later)
  //ZeroMemory(RotatedImg, BPC *  dw * dh);

  //Create a bitmap descriptor for the background
  //Set all BackBmp Elements to zero 44bytes
  ZeroMemory(&BackBmp, sizeof(BITMAPINFO)); 
  BackBmp.bmiHeader.biBitCount = BPC * 8;
  BackBmp.bmiHeader.biPlanes = 1;
  BackBmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  BackBmp.bmiHeader.biWidth = dw;
  BackBmp.bmiHeader.biHeight = -dh;   //Height negative meaning top to bottom image

  //Create an identical descriptor for the rotated bitmap as well
  memcpy(&RotBmp, &BackBmp, sizeof(BITMAPINFO));

  //Create a context and a  bitmap handle to hold the part of the background behind the desination image
  BackDC = CreateCompatibleDC(DestDC);
  iBitmap =  CreateDIBSection(BackDC, &BackBmp, DIB_RGB_COLORS,(void **)&pBits, NULL, 0);
  SelectObject (BackDC, iBitmap);

  //Draw the background to our context
  BitBlt(BackDC, 0, 0, dw, dh, DestDC, (int)(x - dw / 2.0), (int)(y - dh / 2.0), SRCCOPY);

  //get background pixel information and store to the BackgroundImg array.
  //if (!GetDIBits(BackDC, iBitmap , 0, dh, BackgroundImg, &BackBmp, DIB_RGB_COLORS))
  //     return(FAILED_GETTING_BACKGROUND_BITS);
       
  //Copy the background pixels to the destination image
  memcpy(BackgroundImg,pBits, BPC * dw * dh);
  memcpy(RotatedImg, BackgroundImg, BPC * dw * dh);
 
  //Create a bitmap descriptor for the original image
  ZeroMemory(&PicBmp, sizeof(BITMAPINFO));
  PicBmp.bmiHeader.biBitCount = BPC * 8;
  PicBmp.bmiHeader.biPlanes = 1;
  PicBmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  PicBmp.bmiHeader.biWidth = w;
  PicBmp.bmiHeader.biHeight = -h;

  //Create a context and a  bitmap handle to hold the original image
  PicDC = CreateCompatibleDC(DestDC);

  ImgHandle =  CreateDIBSection(PicDC, &PicBmp, DIB_RGB_COLORS,(void **)&pBits, NULL, 0);
  SelectObject(PicDC, ImgHandle);

  //Draw the original image to our context
  BitBlt(PicDC, 0, 0, w, h, SrcDC, srcx, srcy, SRCCOPY);
 
  //get original image pixel information and store to the OriginalImg array.
  //if (!GetDIBits(PicDC, ImgHandle , 0, h, OriginalImg, &PicBmp, DIB_RGB_COLORS))
  //     return FAILED_GETTING_IMAGE_BITS;
  memcpy(OriginalImg,pBits, BPC * w * h);

  //Get the min values to scan
  CX = (dw - w) / 2;  
  CY = (dh - h) / 2;  

  //Convert to R,G,B format the transparent color
  if (TranspColor >= 0) {
     tR = TranspColor & 0xFF;
     tG = (TranspColor & 0xFF00) >> 8;
     tB = (TranspColor & 0xFF0000) >> 16;
     Bixel = Pixel = 0;
     for (YY = 0; YY < h; YY++) { 
        for (XX = 0; XX < w; XX++) { 
          //0 If transparent, 1 if Opaque
          TransparancyMap[Bixel++] = !(OriginalImg[Pixel] == tB && OriginalImg[1+Pixel] == tG && OriginalImg[2+Pixel] == tR);
          Pixel += LEFT;
        }    
     } 
  }

  //If Hue, Sat or Lum parameters have changed then change original image bits
  if (Hue != 0 || Sat != 1 || Lum != 1) {
    //Change Hue of original Image pixel by pixel
    Pixel = 0;
    for (YY = 0; YY < h; YY++)
      for (XX = 0; XX < w; XX++) 
      {
          RGBtoHSL(OriginalImg[Pixel+2]/255.0,
                   OriginalImg[Pixel+1]/255.0,
                   OriginalImg[Pixel]/255.0,
                   &hh , &ss, &vv);                
          HSLtoRGB(norm(hh + Hue), enclose(ss*Sat), enclose(vv*Lum), &rr, &gg, &bb);     
          OriginalImg[Pixel+2] = (BYTE)(rr*255);
          OriginalImg[Pixel+1] = (BYTE)(gg*255);
          OriginalImg[Pixel]= (BYTE)(bb*255);
          Pixel += LEFT;     
      }  
  }   
 
  //ROTATION
  //For all Lines of the destination image
  for (YY = -CY; YY < dh - CY; YY++) { 
    //Get the rotation translation (gives the SourceImage coordinate for each DestImage x,y)
    tx = (-CX - px) * PCos - (YY - py) * PSin + px;
    ty = (-CX - px) * PSin + (YY - py) * PCos + py;
    DestPixel = (YY + CY)*DDown;
    for (XX = -CX; XX < dw - CX; XX++) {
        
      //Get nearest to the left pixel
      ix = (int)tx;
      iy = (int)ty;
          
      if (ix >= 0 && ix + 1 < w && iy >= 0 && iy + 1 < h) {
           //Get the digits after the decimal point
           dx = fabs(tx - ix);
           dy = fabs(ty - iy);             

           //Holds PixelXY index in the array
           Pixel = ix * LEFT + iy * DOWN;
           Bixel = ix + iy * w;
           
           if (TranspColor >= 0) {
             //Get Alpha if the color is not transparent, 0 if it is
             TopLV = TransparancyMap[Bixel] * Alpha;
             TopRV = TransparancyMap[Bixel+1] * Alpha;
             BotLV = TransparancyMap[Bixel+w] * Alpha;
             BotRV = TransparancyMap[Bixel+w+1] * Alpha;  
           } else TopLV = TopRV = BotLV = BotRV = Alpha;
           //Calculate the destination color getting color information from four neigbouring source pixels
           
           //Calculate percendage of pixel used
           TopL = (1 - dx) * (1 - dy);
           TopR = dx * (1 - dy);
           BotL = (1 - dx) * dy;
           BotR = dx * dy;

           //Blue
           BackgroundCol = BackgroundImg[DestPixel];
           RotatedImg[DestPixel] = (BYTE)(  
             (OriginalImg[Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
           + (OriginalImg[Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
           + (OriginalImg[Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
           + (OriginalImg[Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);
           //Green
           BackgroundCol = BackgroundImg[DestPixel+1];           
           RotatedImg[1+DestPixel] = (BYTE)(
             (OriginalImg[1+Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
           + (OriginalImg[1+Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
           + (OriginalImg[1+Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
           + (OriginalImg[1+Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);
           //Red
           BackgroundCol = BackgroundImg[DestPixel+2];           
           RotatedImg[2+DestPixel] = (BYTE)(
             (OriginalImg[2+Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
           + (OriginalImg[2+Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
           + (OriginalImg[2+Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
           + (OriginalImg[2+Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);          
      }      
      tx += PCos;
      ty += PSin;
      DestPixel += LEFT;
    }
  }
  

  //Draw the array
  if (!StretchDIBits(DestDC, (int)(x - dw / 2.0), (int)(y - dh / 2.0), dw, dh, 0, 0, dw, dh, RotatedImg, &RotBmp, DIB_RGB_COLORS, SRCCOPY))
     return FAILED_TO_DRAWIMAGE;

  //Clean up
  free(RotatedImg);
  free(OriginalImg);
  free(BackgroundImg);
  free(TransparancyMap);
  
  DeleteObject(iBitmap);
  DeleteObject(ImgHandle);
  //ReleaseDC(Dc acquired by GetDC)
  DeleteDC(PicDC);
  DeleteDC(BackDC);
  return 0;
}

double CRotate::norm(double a)
{
	if (a > 1.0) 
		return a - 1.0;
    else if (a < 0.0) 
		return a + 1.0;
    else  
      return a;
}

double CRotate::enclose(double a)
{
	if (a > 1.0) 
		return 1.0;
    else if (a < 0.0) 
		return 0;
    else  
      return a;
}

void CRotate::SaveDCToBMP(HDC hDC,int nStartX,int nStartY,int nWidth,int nHeight,LPCTSTR szFileName)
{
	//定义图形色深 
	int iPixel = 32;
	//位图信息头 
	LPBITMAPINFO lpbmih = new BITMAPINFO; 
	lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	lpbmih->bmiHeader.biWidth = nWidth; 
	lpbmih->bmiHeader.biHeight = nHeight; 
	lpbmih->bmiHeader.biPlanes = 1; 
	lpbmih->bmiHeader.biBitCount = iPixel; 
	lpbmih->bmiHeader.biCompression = BI_RGB; 
	lpbmih->bmiHeader.biSizeImage = 0; 
	lpbmih->bmiHeader.biXPelsPerMeter = 0; 
	lpbmih->bmiHeader.biYPelsPerMeter = 0; 
	lpbmih->bmiHeader.biClrUsed = 0; 
	lpbmih->bmiHeader.biClrImportant = 0;

	//创建位图数据 
	HDC hdcMem; 
	HBITMAP hBitMap = NULL; 
	CBitmap *pBitMap = NULL; 
	CDC *pMemDC = NULL; BYTE *pBits;
	hdcMem = CreateCompatibleDC(hDC); 
	hBitMap = CreateDIBSection(hdcMem,lpbmih,DIB_PAL_COLORS,(void **)&pBits,NULL,0); 
	pBitMap = new CBitmap; pBitMap->Attach(hBitMap); 
	pMemDC = new CDC; pMemDC->Attach(hdcMem); 
	pMemDC->SelectObject(pBitMap);  
	pMemDC->BitBlt(0,0,nWidth,nHeight,CDC::FromHandle(hDC),nStartX,nStartY,SRCCOPY);

	BITMAPFILEHEADER bmfh;
	//位图文件头 
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER)); 
	*((char *)&bmfh.bfType) = 'B'; 
	*(((char *)&bmfh.bfType) + 1) = 'M'; 
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
	bmfh.bfSize = bmfh.bfOffBits + (nWidth * nHeight) * iPixel / 8;
	int iBMPBytes = nWidth * nHeight * iPixel / 8; 
	CFile file; if(file.Open(szFileName,CFile::modeWrite | CFile::modeCreate)) 
	{  
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));  
		file.Write(&(lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER));  
		file.Write(pBits,iBMPBytes);  
		file.Close(); 
	}  
	DeleteObject(hBitMap); 
	DeleteObject(hDC); 
	pMemDC->DeleteDC(); 
	delete pMemDC; 
	pMemDC = NULL; 
	delete pBitMap; 
	pBitMap = NULL; 
	delete lpbmih; 
	lpbmih = NULL;
}
