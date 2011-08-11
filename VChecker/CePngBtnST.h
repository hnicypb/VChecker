//
//	Class:		CCePngButtonST
//	Compiler:	vs2005
//	Tested on:	Windows CE 5.0
//	Version:	1.0
//	Created:	2008-7-25
//	Updated:	2008-7-26
//	Author:		starefu or fuxing
//	Note:		To display Image(png) orBitmap(bmp,jpg,etc) or Icon on the Button 
//				which is on a bkgnd bitmap.			
//	Disclaimer
//	----------
//	THIS SOFTWARE IS MODIFIED FROM CCeButtonST CLASS BY AUTHOR.
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE 1$ (ONE U.S. DOLLAR) TO THE AUTHOR:
//	------------
//	by starefu or fuxing	Shenzhen of China
//
#ifndef _CEPNGBTNST_H_
#define _CEPNGBTNST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Imaging.h>

// Return values
#ifndef	BTNST_OK
#define	BTNST_OK						0
#endif
#ifndef	BTNST_INVALIDRESOURCE
#define	BTNST_INVALIDRESOURCE			1
#endif
#ifndef	BTNST_FAILEDMASK
#define	BTNST_FAILEDMASK				2
#endif
#ifndef	BTNST_INVALIDINDEX
#define	BTNST_INVALIDINDEX				3
#endif
#ifndef	BTNST_INVALIDALIGN
#define	BTNST_INVALIDALIGN				4
#endif

class CCePngButtonST : public CButton
{
public:
	CCePngButtonST();
	virtual ~CCePngButtonST();

    enum	{	ST_ALIGN_HORIZ	= 0,			// Icon/bitmap on the left, text on the right
				ST_ALIGN_VERT,					// Icon/bitmap on the top, text on the bottom
				ST_ALIGN_HORIZ_RIGHT,			// Icon/bitmap on the right, text on the left
				ST_ALIGN_CENTER					// text on the top of icon/bitmap
			};

	enum	{	BTNST_COLOR_BK_IN	= 0,		// Background color when mouse is INside
				BTNST_COLOR_FG_IN,				// Text color when mouse is INside
				BTNST_COLOR_BK_OUT,				// Background color when mouse is OUTside
				BTNST_COLOR_FG_OUT,				// Text color when mouse is OUTside
				BTNST_COLOR_BK_FOCUS,			// Background color when the button is focused
				BTNST_COLOR_FG_FOCUS,			// Text color when the button is focused

				BTNST_MAX_COLORS
			};

	DWORD SetDefaultColors(BOOL bRepaint = TRUE);
	DWORD SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint = TRUE);
	DWORD GetColor(BYTE byColorIndex, COLORREF* crpColor);

	DWORD SetCheck(int nCheck, BOOL bRepaint = TRUE);
	int GetCheck();

	DWORD SetURL(LPCTSTR lpszURL = NULL);

	BOOL GetDefault();
	DWORD SetAlwaysTrack(BOOL bAlwaysTrack = TRUE);

	DWORD SetBtnCursor(int nCursorId = NULL, BOOL bRepaint = TRUE);

	DWORD SetFlat(BOOL bFlat = TRUE, BOOL bRepaint = TRUE);
	DWORD SetAlign(BYTE byAlign, BOOL bRepaint = TRUE);

	DWORD DrawBorder(BOOL bDrawBorder = TRUE, BOOL bRepaint = TRUE);
	DWORD DrawFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint = TRUE);

	DWORD SetIcon(int nIconIn, CSize sizeIn = CSize(32,32), int nIconOut = NULL, CSize sizeOut = CSize(32,32), int nIconDis = NULL, CSize sizeDis = CSize(32,32));
	DWORD SetIcon(HICON hIconIn, CSize sizeIn = CSize(32,32), HICON hIconOut = NULL, CSize sizeOut = CSize(32,32), HICON hIconDis = NULL, CSize sizeDis = CSize(32,32));
	//add by starefu or fuxing
	DWORD SetBitmap(int nBitmapIn, CSize sizeIn = CSize(32,32), int nBitmapOut = NULL, CSize sizeOut = CSize(32,32), int nBitmapDis = NULL, CSize sizeDis = CSize(32,32));
	DWORD SetBitmap(HBITMAP hBitmapIn, CSize sizeIn = CSize(32,32), HBITMAP hBitmapOut = NULL, CSize sizeOut = CSize(32,32), HBITMAP hBitmapDis = NULL, CSize sizeDis = CSize(32,32));

	DWORD SetImage(int nBkgndID, int nImageIn, CSize sizeIn = CSize(80,80), int nImageOut = NULL, CSize sizeOut = CSize(80,80), int nImageDis = NULL, CSize sizeDis = CSize(80,80));
	DWORD SetImage(IImage* pIImageIn, CSize sizeIn = CSize(80,80), IImage* pIImageOut = NULL, CSize sizeOut = CSize(80,80), IImage* pIImageDis = NULL, CSize sizeDis = CSize(80,80));
	//end add
	DWORD SetMenu(UINT nMenu, HWND hParentWnd, BOOL bRepaint = TRUE);

	static short GetVersionI()		{return 12;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.2");}

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeButtonST)
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CCeButtonST)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnClicked();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnGetDlgCode();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual DWORD OnDrawBorder(CDC* pDC, LPCRECT pRect);
	virtual DWORD OnDrawBackground(CDC* pDC, LPCRECT pRect);

	BOOL		m_bIsFlat;			// Is a flat button?
	BOOL		m_bMouseOnButton;	// Is mouse over the button?
	BOOL		m_bIsPressed;		// Is button pressed?
	BOOL		m_bIsFocused;		// Is button focused?
	BOOL		m_bIsDisabled;		// Is button disabled?
	BOOL		m_bIsDefault;		// Is default button?
	BOOL		m_bIsCheckBox;		// Is the button a checkbox?
	BYTE		m_byAlign;			// Align mode
	BOOL		m_bDrawBorder;		// Draw border?
	BOOL		m_bDrawFlatFocus;	// Draw focus rectangle for flat button?
	COLORREF	m_crColors[BTNST_MAX_COLORS];	// Colors to be used
	COLORREF	m_transpCREF;
	HMENU		m_hMenu;			// Handle to associated menu
	HWND		m_hParentWndMenu;	// Handle to window for menu selection
	BOOL		m_bMenuDisplayed;	// Is menu displayed ?

private:
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);
	static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

	void CancelHover();
	//modify by starefu or fuxing
	void FreeResources(BOOL bCheckForNULL = TRUE);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	void PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage);
	//end modify
	void DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled);
	//add by starefu or fuxing
	void DrawTheBitmap(HDC h_destDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled);
	void DrawTheImage(HDC h_destDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled);
	//end add
#pragma pack(1)
	typedef struct _STRUCT_ICONS
	{
		HICON		hIcon;			// Handle to icon
		DWORD		dwWidth;		// Width of icon
		DWORD		dwHeight;		// Height of icon
	} STRUCT_ICONS;
	//add by starefu or fuxing
	typedef struct _STRUCT_BITMAPS
	{
		HBITMAP		hBitmap;		// Handle to bitmap
		DWORD		dwWidth;		// Width of bitmap
		DWORD		dwHeight;		// Height of bitmap
	} STRUCT_BITMAPS;
	typedef struct _STRUCT_IIMAGES
	{
		IImage		*pIImage;		// Point to IImage
		DWORD		dwWidth;		// Width of bitmap
		DWORD		dwHeight;		// Height of bitmap
	} STRUCT_IIMAGES;
#pragma pack()
	BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR, IImage** pIImage);
	IImagingFactory *pIImgFactory;

	STRUCT_ICONS	m_csIcons[3];
	STRUCT_BITMAPS  m_csBitmaps[3];
	STRUCT_IIMAGES	m_csImages[3];
	int			nBkgndImageID;		//the bkgnd image ID where button on 
	// end add

	HCURSOR		m_hCursor;			// Handle to cursor
	HCURSOR		m_hOldCursor;		// Handle to old cursor

	BOOL		m_bAlwaysTrack;		// Always hilight button?
	int			m_nCheck;			// Current value for checkbox
	UINT		m_nTypeStyle;		// Button style
	UINT		m_nTimerId;			// Timer ID used for mouse-leave

	TCHAR		m_szURL[_MAX_PATH];	// URL to open when clicked

	DECLARE_MESSAGE_MAP()
};
#endif 
