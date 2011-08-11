#include "stdafx.h"
#include "CePngBtnST.h"
#include <Windows.h>
#include <initguid.h>
#include <imgguids.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Mask for control's type
#ifndef WM_MOUSELEAVE
#define WM_MOUSELEAVE                   0x02A3
#endif

#ifndef	DestroyCursor
#define	DestroyCursor	DestroyIcon
#endif
#define BS_TYPEMASK 0x0000000FL
HBRUSH GetBkBrush( HWND hWnd, UINT nID, HBITMAP hBmBk );
CCePngButtonST::CCePngButtonST()
{
	m_bIsPressed		= FALSE;
	m_bIsFocused		= FALSE;
	m_bIsDisabled		= FALSE;
	m_bMouseOnButton	= FALSE;

	FreeResources(FALSE);

	// Default type is "flat" button
	m_bIsFlat = TRUE; 
	// Button will be tracked also if when the window is inactive (like Internet Explorer)
	m_bAlwaysTrack = TRUE;

	// By default draw border in "flat" button 
	m_bDrawBorder = TRUE; 

	// By default icon is aligned horizontally
	m_byAlign = ST_ALIGN_HORIZ; 
  
	// By default, for "flat" button, don't draw the focus rect
	m_bDrawFlatFocus = FALSE;

	// By default the button is not the default button
	m_bIsDefault = FALSE;
	// Invalid value, since type still unknown
	m_nTypeStyle = BS_TYPEMASK;

	// By default the button is not a checkbox
	m_bIsCheckBox = FALSE;
	m_nCheck = 0;

	// Set default colors
	SetDefaultColors(FALSE);

	// No URL defined
	SetURL(NULL);

	// No cursor defined
	m_hCursor = NULL;
	m_hOldCursor = NULL;

	// No timer defined
	m_nTimerId = 0;

	// No associated menu
	m_hMenu = NULL;
	m_hParentWndMenu = NULL;
	m_bMenuDisplayed = FALSE;

	// transp CRef
	m_transpCREF = RGB(255,255,255);

	//IImagingFactory *pIImgFactory;
	pIImgFactory = NULL;	
}

CCePngButtonST::~CCePngButtonST()
{
	FreeResources();

	// Restore old cursor (if any)
	if (m_hOldCursor)	::SetCursor(m_hOldCursor);
	// Destroy the cursor (if any)
	if (m_hCursor)	::DestroyCursor(m_hCursor);
	// Destroy the menu (if any)
	if (m_hMenu)	::DestroyMenu(m_hMenu);

	//free(pIImgFactory);
}

BEGIN_MESSAGE_MAP(CCePngButtonST, CButton)
	//{{AFX_MSG_MAP(CCeButtonST)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_ENABLE()
	ON_WM_GETDLGCODE()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_ACTIVATE()
	ON_WM_CANCELMODE()
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	//ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

void CCePngButtonST::FreeResources(BOOL bCheckForNULL)
{
	if (bCheckForNULL)
	{
		// Destroy icons
		// Note: the following lines MUST be here! even if
		// BoundChecker says they are unnecessary!
		if (m_csIcons[0].hIcon)	::DestroyIcon(m_csIcons[0].hIcon);
		if (m_csIcons[1].hIcon)	::DestroyIcon(m_csIcons[1].hIcon);
		if (m_csIcons[2].hIcon)	::DestroyIcon(m_csIcons[2].hIcon);
	} // if

	memset(&m_csIcons, 0, sizeof(m_csIcons));
	memset(&m_csBitmaps, 0, sizeof(m_csBitmaps));
	memset(&m_csImages, 0, sizeof(m_csImages));
} // End of FreeResources

void CCePngButtonST::PreSubclassWindow() 
{
	UINT nBS;

	nBS = GetButtonStyle();

	// Set initial control type
	m_nTypeStyle = nBS & BS_TYPEMASK;

	// Check if this is a checkbox
	if (nBS & BS_CHECKBOX) m_bIsCheckBox = TRUE;

	// Set initial default state flag
	if (m_nTypeStyle == BS_DEFPUSHBUTTON)
	{
		// Set default state for a default button
		m_bIsDefault = TRUE;

		// Adjust style for default button
		m_nTypeStyle = BS_PUSHBUTTON;
	} // If

	// You should not set the Owner Draw before this call
	// (don't use the resource editor "Owner Draw" or
	// ModifyStyle(0, BS_OWNERDRAW) before calling PreSubclassWindow() )
	ASSERT(m_nTypeStyle != BS_OWNERDRAW);

	// Switch to owner-draw
	ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
} // End of PreSubclassWindow

void CCePngButtonST::OnDestroy() 
{
	// Kill timer
	if (m_nTimerId)	KillTimer(m_nTimerId);
	m_nTimerId = 0;

	CButton::OnDestroy();
} // End of OnDestroy

UINT CCePngButtonST::OnGetDlgCode() 
{
	UINT nCode = CButton::OnGetDlgCode();

	// tell the system if we want default state handling
	// (losing default state always allowed)
	nCode |= (m_bIsDefault ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);

	return nCode;
} // End of OnGetDlgCode

LRESULT CCePngButtonST::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	} // if
	return CButton::DefWindowProc(message, wParam, lParam);
} // End of DefWindowProc

HBRUSH CCePngButtonST::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
} // End of CtlColor

LRESULT CCePngButtonST::OnSetStyle(WPARAM wParam, LPARAM lParam)
{
	UINT nNewType = (wParam & BS_TYPEMASK);

	// Update default state flag
	if (nNewType == BS_DEFPUSHBUTTON)
	{
		m_bIsDefault = TRUE;
	} // if
	else if (nNewType == BS_PUSHBUTTON)
	{
		// Losing default state always allowed
		m_bIsDefault = FALSE;
	} // if

	// Can't change control type after owner-draw is set.
	// Let the system process changes to other style bits
	// and redrawing, while keeping owner-draw style
	return DefWindowProc(BM_SETSTYLE,
		(wParam & ~BS_TYPEMASK) | BS_OWNERDRAW, lParam);
} // End of OnSetStyle

void CCePngButtonST::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	if (bEnable == FALSE)	
	{
		CWnd*	pWnd = GetParent()->GetNextDlgTabItem(this);
		if (pWnd)
			pWnd->SetFocus();
		else
			GetParent()->SetFocus();

		CancelHover();
	} // if
} // End of OnEnable
  
void CCePngButtonST::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	CancelHover();
} // End of OnKillFocus

void CCePngButtonST::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CButton::OnActivate(nState, pWndOther, bMinimized);
	if (nState == WA_INACTIVE)	CancelHover();
} // End of OnActivate

void CCePngButtonST::OnCancelMode() 
{
	CButton::OnCancelMode();
	CancelHover();
} // End of OnCancelMode

void CCePngButtonST::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetState(TRUE);
#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300)
	SHRecognizeGesture(point);
#endif // _WIN32_WCE_PSPC
	Default();
	
	//CButton::OnLButtonDown(nFlags, point);
} // End of OnLButtonDown

void CCePngButtonST::CancelHover()
{
	// Only for flat buttons
	if (m_bIsFlat)
	{
		// Kill timer (if active)
		if (m_nTimerId)	KillTimer(m_nTimerId);
		m_nTimerId = 0;

		if (m_bMouseOnButton)
		{
			// Restore old cursor (if any)
			if (m_hOldCursor)
			{
				::SetCursor(m_hOldCursor);
				m_hOldCursor = NULL;
			} // if

			m_bMouseOnButton = FALSE;
			Invalidate();
		} // if
	} // if
} // End of CancelHover

void CCePngButtonST::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;

	CButton::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	// If the mouse enter the button with the left button pressed then do nothing
	if (nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) return;

	// If our button is not flat then do nothing
	if (m_bIsFlat == FALSE) return;

	if (m_bAlwaysTrack == FALSE)	wndActive = GetActiveWindow();

	if (wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd && wndActive)
	{
		if (!m_bMouseOnButton)
		{
			m_bMouseOnButton = TRUE;

			Invalidate();

			ASSERT(m_nTimerId == 0);
			m_nTimerId = SetTimer(1, 50, TimerProc);
		} // if
	} //else CancelHover();
} // End of OnMouseMove

// Handler for WM_MOUSELEAVE
LRESULT CCePngButtonST::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} // End of OnMouseLeave

BOOL CCePngButtonST::OnClicked() 
{
	if (m_bIsCheckBox)
	{
		m_nCheck = !m_nCheck;
		Invalidate();
	} // if
	else
	{
		// Handle the menu (if any)
		if (m_hMenu)
		{
			HMENU	hSubMenu = NULL;
			CRect	rWnd;

			hSubMenu = ::GetSubMenu(m_hMenu, 0);

			GetWindowRect(rWnd);

			m_bMenuDisplayed = TRUE;
			Invalidate();

			::TrackPopupMenuEx(	hSubMenu, 
#ifdef UNDER_CE
								TPM_LEFTALIGN,
#else
								TPM_LEFTALIGN | TPM_LEFTBUTTON,
#endif
								rWnd.left, rWnd.bottom, m_hParentWndMenu, NULL);

			m_bMenuDisplayed = FALSE;
			Invalidate();
		} // if
		else
		{
			// Handle the URL (if any)
			if (_tcslen(m_szURL) > 0)
			{
				SHELLEXECUTEINFO	csSEI;

				memset(&csSEI, 0, sizeof(csSEI));
				csSEI.cbSize = sizeof(SHELLEXECUTEINFO);
				csSEI.fMask = SEE_MASK_FLAG_NO_UI;
				csSEI.lpVerb = _T("open");
				csSEI.lpFile = m_szURL;
				csSEI.nShow = SW_SHOWMAXIMIZED;
				::ShellExecuteEx(&csSEI);
			} // if
		} // else
	} // else

	return FALSE;
} // End of OnClicked
  
void CCePngButtonST::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);

	// Checkbox?
	if (m_bIsCheckBox)
	{
		m_bIsPressed  =  (lpDIS->itemState & ODS_SELECTED) || (m_nCheck != 0);
	} // if
	else	// Normal button OR other button style ...
	{
		m_bIsPressed = (lpDIS->itemState & ODS_SELECTED);

		// If there is a menu and it's displayed, draw the button as pressed
		if (m_hMenu && m_bMenuDisplayed)	m_bIsPressed = TRUE;
	} // else

	m_bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
	m_bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

	CRect itemRect = lpDIS->rcItem;

	pDC->SetBkMode(TRANSPARENT);

	if (m_bIsFlat == FALSE)
	{
		if (m_bIsFocused || m_bIsDefault)
		{
			CBrush br(RGB(0,0,0));  
			pDC->FrameRect(&itemRect, &br);
			itemRect.DeflateRect(1, 1);
		} // if
	} // if

	// Prepare draw... paint button background
	OnDrawBackground(pDC, &itemRect);

	// Paint button border
	//if (!m_bIsFlat || (m_bIsFlat && m_bDrawBorder))
	//	OnDrawBorder(pDC, &itemRect);

	// Read the button's title
	TCHAR	szTitle[256];
	GetWindowText(szTitle, sizeof(szTitle)/sizeof(TCHAR));

	CRect captionRect = lpDIS->rcItem;

	/* Draw the icon
	if (m_csIcons[0].hIcon)
	{
		DrawTheIcon(pDC, _tcslen(szTitle), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} 
	// Draw the bitmap
	if (m_csBitmaps[0].hBitmap)
	{
		DrawTheBitmap(lpDIS->hDC, _tcslen(szTitle), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} 
	*/
	// Draw the image
	if (m_csImages[0].pIImage)
	{
		DrawTheImage(lpDIS->hDC, _tcslen(szTitle), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} 
	// Write the button title (if any)
	if (_tcslen(szTitle))
	{
		// Draw the button's title
		// If button is pressed then "press" title also
		if (m_bIsPressed && m_bIsCheckBox == FALSE && m_byAlign != ST_ALIGN_CENTER )//add && m_byAlign != ST_ALIGN_CENTER for press static button not move
			captionRect.OffsetRect(1, 1);
    
		// ONLY FOR DEBUG 
		//CBrush brBtnShadow(RGB(255, 0, 0));
		//pDC->FrameRect(&captionRect, &brBtnShadow);

		// Center text
		CRect centerRect = captionRect;
		pDC->DrawText(szTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
		captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
		/* RFU
		captionRect.OffsetRect(0, (centerRect.Height() - captionRect.Height())/2);
		captionRect.OffsetRect((centerRect.Width() - captionRect.Width())-4, (centerRect.Height() - captionRect.Height())/2);
		*/

		pDC->SetBkMode(TRANSPARENT);
		/*
		pDC->DrawState(captionRect.TopLeft(), captionRect.Size(), szTitle, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
						TRUE, 0, (CBrush*)NULL);
		*/
		if (m_bIsDisabled)
		{
			
			captionRect.OffsetRect(1, 1);
			pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
			pDC->DrawText(szTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
			captionRect.OffsetRect(-1, -1);
			pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
			//pDC->SetTextColor(RGB(0,0,0));//modify and add : use this disable button for static text.
			pDC->DrawText(szTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
		} // if
		else
		{
			if (m_bMouseOnButton || m_bIsPressed) 
			{
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_IN]);
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_IN]);
			} // if
			else 
			{
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_OUT]);
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_OUT]);
			} // else
			pDC->DrawText(szTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
		} // if
	} // if

	if (m_bIsFlat == FALSE || (m_bIsFlat && m_bDrawFlatFocus))
	{
		// Draw the focus rect
		if (m_bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC->DrawFocusRect(&focusRect);
		} // if
	} // if
} // End of DrawItem

//
// Parameters:
//		[IN]	bHasTitle
//				TRUE if the button has a text
//		[IN]	rpItem
//				A pointer to a RECT structure indicating the allowed paint area
//		[IN/OUT]rpTitle
//				A pointer to a CRect object indicating the paint area reserved for the
//				text. This structure will be modified if necessary.
//		[IN]	bIsPressed
//				TRUE if the button is currently pressed
//		[IN]	dwWidth
//				Width of the image (icon or bitmap)
//		[IN]	dwHeight
//				Height of the image (icon or bitmap)
//		[OUT]	rpImage
//				A pointer to a CRect object that will receive the area available to the image
//
void CCePngButtonST::PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage)
{
	CRect rBtn;

	rpImage->CopyRect(rpItem);

	switch (m_byAlign)
	{
		case ST_ALIGN_HORIZ:
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpImage->left += 3;  
				rpTitle->left += dwWidth + 3;
			}
			// Center image vertically
			rpImage->top += ((rpImage->Height() - dwHeight)/2);
			break;

		case ST_ALIGN_HORIZ_RIGHT:
			GetClientRect(&rBtn);
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpTitle->right = rpTitle->Width() - dwWidth - 3;
				rpTitle->left = 3;
				rpImage->left = rBtn.right - dwWidth - 3;
				// Center image vertically
				rpImage->top += ((rpImage->Height() - dwHeight)/2);
			}
			break;
		
		case ST_ALIGN_VERT:
			// Center image horizontally
			rpImage->left += ((rpImage->Width() - dwWidth)/2);
			if (bHasTitle == FALSE)
			{
				// Center image vertically
				rpImage->top += ((rpImage->Height() - dwHeight)/2);           
			}
			else
			{
				rpImage->top = 0;//modify from 3
				rpTitle->top += dwHeight-14;//modify form dwHeight
			}
			break;
		case ST_ALIGN_CENTER:
			// Center image horizontally
			rpImage->left += ((rpImage->Width() - dwWidth)/2);
			if (bHasTitle == FALSE)
			{
				// Center image vertically
				rpImage->top += ((rpImage->Height() - dwHeight)/2);           
			}
			else
			{
				rpImage->top = 0;//modify from 3
				rpTitle->top += 0;//modify form dwHeight
			}
			break;
	}
	//add by fuxing 2008-7-26
	rpImage->right = rpImage->left + dwWidth;
	rpImage->bottom = rpImage->top + dwHeight;
    
	// If button is pressed then press image also
	if (bIsPressed && m_bIsCheckBox == FALSE && m_byAlign != ST_ALIGN_CENTER)//add && m_byAlign != ST_ALIGN_CENTER for press static button not move
		rpImage->OffsetRect(1, 1);
		//rpImage->DeflateRect(1,1);
} // End of PrepareImageRect

void CCePngButtonST::DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;

	// Select the icon to use
	if (bIsDisabled)
		byIndex = (m_csIcons[2].hIcon == NULL ? 0 : 2);
	else
	{
		if ((m_bIsCheckBox && bIsPressed) || (!m_bIsCheckBox && (bIsPressed || m_bMouseOnButton)))
			byIndex = 0;
		else
			byIndex = (m_csIcons[1].hIcon == NULL ? 0 : 1);
	} // else

	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpTitle, bIsPressed, m_csIcons[byIndex].dwWidth, m_csIcons[byIndex].dwHeight, &rImage);

	// Ole'!
	pDC->DrawIcon(rImage.TopLeft(), m_csIcons[byIndex].hIcon);
} // End of DrawTheIcon

void CCePngButtonST::DrawTheBitmap(HDC h_destDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;
	CRect		rImage;
	BITMAP		bmp;
	HBITMAP		hBmp;
	HDC			hDC;
	// Select the icon to use
	// Select the icon to use
	if (bIsDisabled)
		byIndex = (m_csBitmaps[2].hBitmap == NULL ? 0 : 2);
	else
	{
		if ((m_bIsCheckBox && bIsPressed) || (!m_bIsCheckBox && (bIsPressed || m_bMouseOnButton)))
			byIndex = 0;
		else
			byIndex = (m_csBitmaps[1].hBitmap == NULL ? 0 : 1);
	} // else

	//GetClientRect(&cltRect);
	//hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(byIndex));
	hBmp = m_csBitmaps[byIndex].hBitmap;
	::GetObject(hBmp, sizeof(bmp), &bmp);
	hDC = ::CreateCompatibleDC(NULL);
	SelectObject(hDC, hBmp);

	PrepareImageRect(bHasTitle, rpItem, rpTitle, bIsPressed, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, &rImage);
	::TransparentImage(h_destDC, rImage.left, rImage.top, rImage.Width(), rImage.Height(), hDC, 0, 0, rImage.Width(), rImage.Height(), m_transpCREF);
	//BLENDFUNCTION   bf;   
	//bf.AlphaFormat=0;   
	//bf.BlendFlags=0;   
	//bf.BlendOp=AC_SRC_OVER;   
	//bf.SourceConstantAlpha=255;//Í¸Ã÷¶È0~255   
	//::AlphaBlend(h_destDC, rImage.left, rImage.top, rImage.Width(), rImage.Height(), hDC, 0, 0, rImage.Width(), rImage.Height(), bf);
	::DeleteObject(hBmp);
	::DeleteDC(hDC);
} // End of DrawTheBitmap

void CCePngButtonST::DrawTheImage(HDC h_destDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;
	CRect		rImage;
	// Select the image to use
	if (bIsDisabled)
		byIndex = (m_csImages[2].pIImage == NULL ? 1 : 2);
	else
	{
		if ((m_bIsCheckBox && bIsPressed) || (!m_bIsCheckBox && (bIsPressed)))//|| m_bMouseOnButton
			byIndex = 0;
		else
			byIndex = (m_csImages[1].pIImage == NULL ? 0 : 1);
	}
	PrepareImageRect(bHasTitle, rpItem, rpTitle, bIsPressed, m_csImages[byIndex].dwWidth, m_csImages[byIndex].dwHeight, &rImage);
	
	m_csImages[byIndex].pIImage->Draw(h_destDC, rImage, NULL);

}	// End of DrawTheImage

BOOL CCePngButtonST::ImageFromIDResource(UINT nID, LPCTSTR sTR, IImage** pIImage)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pStream;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pStream);
	// load from stream
	pIImgFactory->CreateImageFromStream(pStream, pIImage);

	// free/release stuff
	GlobalUnlock(m_hMem);
	pStream->Release();
	FreeResource(lpRsrc);
	if(!pIImage)
		return FALSE;

	return TRUE;
}

// This function assigns icons to the button.
// Any previous icon will be removed.
//
// Parameters:
//		[IN]	nIconIn
//				ID number of the icon resource to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	sizeIn
//				Size of the icon.
//		[IN]	nIconOut
//				ID number of the icon resource to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	sizeOut
//				Size of the icon.
//		[IN]	nIconDis
//				ID number of the icon resource to show when the button is disabled.
//				Can be NULL.
//		[IN]	sizeDis
//				Size of the icon.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetIcon(int nIconIn, CSize sizeIn, int nIconOut, CSize sizeOut, int nIconDis, CSize sizeDis)
{
	HICON		hIconIn			= NULL;
	HICON		hIconOut		= NULL;
	HICON		hIconDis		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconIn), RT_GROUP_ICON);

	// Set icon when the mouse is IN the button
	hIconIn = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconIn), IMAGE_ICON, 0, 0, 0);
  	// Set icon when the mouse is OUT the button
	if (nIconOut)
		hIconOut = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconOut), IMAGE_ICON, 0, 0, 0);
  	// Set icon when the mouse is DISABLED
	if (nIconDis)
		hIconDis = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconDis), IMAGE_ICON, 0, 0, 0);

	return SetIcon(hIconIn, sizeIn, hIconOut, sizeOut, hIconDis, sizeDis);
} // End of SetIcon

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	hIconIn
//				Handle fo the icon to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	sizeIn
//				Size of the icon.
//		[IN]	hIconOut
//				Handle to the icon to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	sizeOut
//				Size of the icon.
//		[IN]	hIconDis
//				ID number of the icon resource to show when the button is disabled.
//				Can be NULL.
//		[IN]	sizeDis
//				Size of the icon.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetIcon(HICON hIconIn, CSize sizeIn, HICON hIconOut, CSize sizeOut, HICON hIconDis, CSize sizeDis)
{
	// Free any loaded resource
	FreeResources();

	if (hIconIn)
	{
		// Icon when mouse over button?
		m_csIcons[0].hIcon = hIconIn;
		// Get icon dimension
		m_csIcons[0].dwWidth	= (DWORD)sizeIn.cx;
		m_csIcons[0].dwHeight	= (DWORD)sizeIn.cy;
		
		// Icon when mouse outside button?
		if (hIconOut)
		{
			m_csIcons[1].hIcon = hIconOut;
			// Get icon dimension
			m_csIcons[1].dwWidth	= (DWORD)sizeOut.cx;
			m_csIcons[1].dwHeight	= (DWORD)sizeOut.cy;
		} // if

		// Icon when button disabled?
		if (hIconDis)
		{
			m_csIcons[2].hIcon = hIconDis;
			// Get icon dimension
			m_csIcons[2].dwWidth	= (DWORD)sizeDis.cx;
			m_csIcons[2].dwHeight	= (DWORD)sizeDis.cy;
		} // if
	} // if

	Invalidate();

	return BTNST_OK;
} // End of SetIcon

// This function assigns bitmaps to the button.
// Any previous bitmap will be removed.
//
// Parameters:
//		[IN]	nBitmapIn
//				ID number of the icon resource to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	sizeIn
//				Size of the icon.
//		[IN]	nBitmapOut
//				ID number of the icon resource to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	sizeOut
//				Size of the icon.
//		[IN]	nBitmapDis
//				ID number of the icon resource to show when the button is disabled.
//				Can be NULL.
//		[IN]	sizeDis
//				Size of the icon.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetBitmap(int nBitmapIn, CSize sizeIn, int nBitmapOut, CSize sizeOut, int nBitmapDis, CSize sizeDis)
{
	HBITMAP		hBitmapIn		= NULL;
	HBITMAP		hBitmapOut		= NULL;
	HBITMAP		hBitmapDis		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmapIn), RT_BITMAP);

	// Set icon when the mouse is IN the button
	hBitmapIn = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapIn), IMAGE_BITMAP, 0, 0, 0);
  	// Set icon when the mouse is OUT the button
	if (nBitmapOut)
		hBitmapOut = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapOut), IMAGE_BITMAP, 0, 0, 0);
  	// Set icon when the mouse is DISABLED
	if (nBitmapDis)
		hBitmapDis = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapDis), IMAGE_BITMAP, 0, 0, 0);

	return SetBitmap(hBitmapIn, sizeIn, hBitmapOut, sizeOut, hBitmapDis, sizeDis);
} // End of SetIcon

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	hBitmapIn
//				Handle fo the icon to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	sizeIn
//				Size of the bitmap.
//		[IN]	hBitmapOut
//				Handle to the icon to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	sizeOut
//				Size of the bitmap.
//		[IN]	hBitmapDis
//				ID number of the icon resource to show when the button is disabled.
//				Can be NULL.
//		[IN]	sizeDis
//				Size of the bitmap.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetBitmap(HBITMAP hBitmapIn, CSize sizeIn, HBITMAP hBitmapOut, CSize sizeOut, HBITMAP hBitmapDis, CSize sizeDis)
{
	// Free any loaded resource
	FreeResources();

	if (hBitmapIn)
	{
		// Icon when mouse over button?
		m_csBitmaps[0].hBitmap = hBitmapIn;
		// Get icon dimension
		m_csBitmaps[0].dwWidth	= (DWORD)sizeIn.cx;
		m_csBitmaps[0].dwHeight	= (DWORD)sizeIn.cy;
		
		// Icon when mouse outside button?
		if (hBitmapOut)
		{
			m_csBitmaps[1].hBitmap = hBitmapOut;
			// Get icon dimension
			m_csBitmaps[1].dwWidth	= (DWORD)sizeOut.cx;
			m_csBitmaps[1].dwHeight	= (DWORD)sizeOut.cy;
		} // if

		// Icon when button disabled?
		if (hBitmapDis)
		{
			m_csBitmaps[2].hBitmap = hBitmapDis;
			// Get icon dimension
			m_csBitmaps[2].dwWidth	= (DWORD)sizeDis.cx;
			m_csBitmaps[2].dwHeight	= (DWORD)sizeDis.cy;
		} // if
	} // if

	Invalidate();

	return BTNST_OK;
} // End of SetBitmap

DWORD CCePngButtonST::SetImage(int nBkgndID, int nImageIn, CSize sizeIn, int nImageOut, CSize sizeOut, int nImageDis, CSize sizeDis)
{
	IImage*	pImageIn	= NULL;
	IImage*	pImageOut	= NULL;
	IImage*	pImageDis	= NULL;

	nBkgndImageID = nBkgndID;
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	//initialize com 
	if(!SUCCEEDED(CoCreateInstance(CLSID_ImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_IImagingFactory,(void **)&pIImgFactory)))
	{
		return BTNST_FAILEDMASK;
	}
	// Set image when the mouse is IN the button
	ImageFromIDResource(nImageIn, L"PNG", &pImageIn);
  	// Set image when the mouse is OUT the button
	if (nImageOut)
		ImageFromIDResource(nImageOut, L"PNG", &pImageOut);
  	// Set image when the mouse is DISABLED
	if (nImageDis)
		ImageFromIDResource(nImageDis, L"PNG", &pImageDis);
	return SetImage(pImageIn, sizeIn, pImageOut, sizeOut, pImageDis, sizeDis);
} // End of SetImage

DWORD CCePngButtonST::SetImage(IImage* pIImageIn, CSize sizeIn, IImage* pIImageOut, CSize sizeOut, IImage* pIImageDis, CSize sizeDis)
{
	// Free any loaded resource
	FreeResources();

	if (pIImageIn)
	{
		// Image when mouse over button?
		m_csImages[0].pIImage = pIImageIn;
		// Get image dimension
		m_csImages[0].dwWidth	= (DWORD)sizeIn.cx;
		m_csImages[0].dwHeight	= (DWORD)sizeIn.cy;
		
		// Image when mouse outside button?
		if (pIImageOut)
		{
			m_csImages[1].pIImage = pIImageOut;
			// Get image dimension
			m_csImages[1].dwWidth	= (DWORD)sizeOut.cx;
			m_csImages[1].dwHeight	= (DWORD)sizeOut.cy;
		} // if

		// Image when button disabled?
		if (pIImageDis)
		{
			m_csImages[2].pIImage = pIImageDis;
			// Get icon dimension
			m_csImages[2].dwWidth	= (DWORD)sizeDis.cx;
			m_csImages[2].dwHeight	= (DWORD)sizeDis.cy;
		} // if
	} // if

	Invalidate();

	return BTNST_OK;
} // End of SetImage

// This functions sets the button to have a standard or flat style.
//
// Parameters:
//		[IN]	bFlat
//				If TRUE the button will have a flat style, else
//				will have a standard style.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetFlat(BOOL bFlat, BOOL bRepaint)
{
	m_bIsFlat = bFlat;
	if (bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetFlat

// This function sets the alignment type between icon/bitmap and text.
//
// Parameters:
//		[IN]	byAlign
//				Alignment type. Can be one of the following values:
//				ST_ALIGN_HORIZ			Icon/bitmap on the left, text on the right
//				ST_ALIGN_VERT			Icon/bitmap on the top, text on the bottom
//				ST_ALIGN_HORIZ_RIGHT	Icon/bitmap on the right, text on the left
//				By default, CButtonST buttons have ST_ALIGN_HORIZ alignment.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDALIGN
//			Alignment type not supported.
//
DWORD CCePngButtonST::SetAlign(BYTE byAlign, BOOL bRepaint)
{
	switch (byAlign)
	{    
		case ST_ALIGN_HORIZ:
		case ST_ALIGN_HORIZ_RIGHT:
		case ST_ALIGN_VERT:
		case ST_ALIGN_CENTER:
			m_byAlign = byAlign;
			if (bRepaint)	Invalidate();
			return BTNST_OK;
			break;
	} // switch

	return BTNST_INVALIDALIGN;
} // End of SetAlign

// This function sets the state of the checkbox.
// If the button is not a checkbox, this function has no meaning.
//
// Parameters:
//		[IN]	nCheck
//				1 to check the checkbox.
//				0 to un-check the checkbox.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetCheck(int nCheck, BOOL bRepaint)
{
	if (m_bIsCheckBox)
	{
		if (nCheck == 0) m_nCheck = 0;
		else m_nCheck = 1;

		if (bRepaint) Invalidate();
	} // if

	return BTNST_OK;
} // End of SetCheck

// This function returns the current state of the checkbox.
// If the button is not a checkbox, this function has no meaning.
//
// Return value:
//		The current state of the checkbox.
//			1 if checked.
//			0 if not checked or the button is not a checkbox.
//
int CCePngButtonST::GetCheck()
{
	return m_nCheck;
} // End of GetCheck

// This function sets all colors to a default value.
//
// Parameters:
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetDefaultColors(BOOL bRepaint)
{
	m_crColors[BTNST_COLOR_BK_IN]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_IN]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_OUT]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_OUT]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_FOCUS]	= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_FOCUS]	= ::GetSysColor(COLOR_BTNTEXT);

	if (bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetDefaultColors

// This function sets the color to use for a particular state.
//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to set. Can be one of the following values:
//				BTNST_COLOR_BK_IN		Background color when mouse is over the button
//				BTNST_COLOR_FG_IN		Text color when mouse is over the button
//				BTNST_COLOR_BK_OUT		Background color when mouse is outside the button
//				BTNST_COLOR_FG_OUT		Text color when mouse is outside the button
//				BTNST_COLOR_BK_FOCUS	Background color when the button is focused
//				BTNST_COLOR_FG_FOCUS	Text color when the button is focused
//		[IN]	crColor
//				New color.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//
DWORD CCePngButtonST::SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint)
{
	if (byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// Set new color
	m_crColors[byColorIndex] = crColor;

	if (bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetColor

// This functions returns the color used for a particular state.
//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to get. Can be one of the following values:
//				BTNST_COLOR_BK_IN		Background color when mouse is over the button
//				BTNST_COLOR_FG_IN		Text color when mouse is over the button
//				BTNST_COLOR_BK_OUT		Background color when mouse is outside the button
//				BTNST_COLOR_FG_OUT		Text color when mouse is outside the button
//				BTNST_COLOR_BK_FOCUS	Background color when the button is focused
//				BTNST_COLOR_FG_FOCUS	Text color when the button is focused
//		[OUT]	crpColor
//				A pointer to a COLORREF that will receive the color.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//
DWORD CCePngButtonST::GetColor(BYTE byColorIndex, COLORREF* crpColor)
{
	if (byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// Get color
	*crpColor = m_crColors[byColorIndex];

	return BTNST_OK;
} // End of GetColor

// This function sets the hilight logic for the button.
// Applies only to flat buttons.
//
// Parameters:
//		[IN]	bAlwaysTrack
//				If TRUE the button will be hilighted even if the window that owns it, is
//				not the active window.
//				If FALSE the button will be hilighted only if the window that owns it,
//				is the active window.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetAlwaysTrack(BOOL bAlwaysTrack)
{
	m_bAlwaysTrack = bAlwaysTrack;
	return BTNST_OK;
} // End of SetAlwaysTrack

// This function sets the cursor to be used when the mouse is over the button.
//
// Parameters:
//		[IN]	nCursorId
//				ID number of the cursor resource.
//				Pass NULL to remove a previously loaded cursor.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
DWORD CCePngButtonST::SetBtnCursor(int nCursorId, BOOL bRepaint)
{
	HINSTANCE	hInstResource = NULL;
	// Restore old cursor (if any)
	if (m_hOldCursor)	::SetCursor(m_hOldCursor);
	// Destroy the cursor (if any)
	if (m_hCursor)	::DestroyCursor(m_hCursor);
	m_hCursor = NULL;
	m_hOldCursor = NULL;

	// Load cursor
	if (nCursorId)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR);
		// Load cursor resource
		m_hCursor = (HCURSOR)::LoadImage(hInstResource, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		// Repaint the button
		if (bRepaint) Invalidate();
		// If something wrong
		if (m_hCursor == NULL) return BTNST_INVALIDRESOURCE;
	} // if

	return BTNST_OK;
} // End of SetBtnCursor

// This function sets if the button border must be drawn.
// Applies only to flat buttons.
//
// Parameters:
//		[IN]	bDrawBorder
//				If TRUE the border will be drawn.
//		[IN]	bRepaint
//				If TRUE the button will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::DrawBorder(BOOL bDrawBorder, BOOL bRepaint)
{
	m_bDrawBorder = bDrawBorder;
	// Repaint the button
	if (bRepaint) Invalidate();

	return BTNST_OK;
} // End of DrawBorder

// This function sets if the focus rectangle must be drawn for flat buttons.
//
// Parameters:
//		[IN]	bDrawFlatFocus
//				If TRUE the focus rectangle will be drawn also for flat buttons.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::DrawFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	// Repaint the button
	if (bRepaint) Invalidate();

	return BTNST_OK;
} // End of DrawFlatFocus

// This function returns if the button is the default button.
//
// Return value:
//		TRUE
//			The button is the default button.
//		FALSE
//			The button is not the default button.
//
BOOL CCePngButtonST::GetDefault()
{
	return m_bIsDefault;
} // End of GetDefault

// This function sets the URL that will be opened when the button is clicked.
//
// Parameters:
//		[IN]	lpszURL
//				Pointer to a null-terminated string that contains the URL.
//				Pass NULL to remove any previously specified URL.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::SetURL(LPCTSTR lpszURL)
{
	// Remove any existing URL
	memset(m_szURL, 0, sizeof(m_szURL));

	if (lpszURL)
	{
		// Store the URL
		_tcsncpy(m_szURL, lpszURL, _MAX_PATH);
	} // if

	return BTNST_OK;
} // End of SetURL

BOOL CCePngButtonST::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR	hOldCursor;

	// If a cursor was specified then use it!
	if (m_hCursor != NULL)
	{
		hOldCursor = ::SetCursor(m_hCursor);
		// Store old cursor
		if (!m_hOldCursor)	m_hOldCursor = hOldCursor;
		return TRUE;
	} // if

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor

// This function associates a menu to the button.
// The menu will be displayed clicking the button.
//
// Parameters:
//		[IN]	nMenu
//				ID number of the menu resource.
//				Pass NULL to remove any menu from the button.
//		[IN]	hParentWnd
//				Handle to the window that owns the menu.
//				This window receives all messages from the menu.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
DWORD CCePngButtonST::SetMenu(UINT nMenu, HWND hParentWnd, BOOL bRepaint)
{
	HINSTANCE	hInstResource	= NULL;

	// Destroy any previous menu
	if (m_hMenu)
	{
		::DestroyMenu(m_hMenu);
		m_hMenu = NULL;
		m_hParentWndMenu = NULL;
		m_bMenuDisplayed = FALSE;
	} // if

	// Load menu
	if (nMenu)
	{
		// Find correct resource handle
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nMenu), RT_MENU);
		// Load menu resource
		m_hMenu = ::LoadMenu(hInstResource, MAKEINTRESOURCE(nMenu));
		m_hParentWndMenu = hParentWnd;
		// If something wrong
		if (m_hMenu == NULL) return BTNST_INVALIDRESOURCE;
	} // if

	// Repaint the button
	if (bRepaint) Invalidate();

	return BTNST_OK;
} // End of SetMenu

// This function is called every time the button background needs to be painted.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::OnDrawBackground(CDC* pDC, LPCRECT pRect)
{
	/*
	COLORREF	crColor;

	if (m_bMouseOnButton || m_bIsPressed)
		crColor = m_crColors[BTNST_COLOR_BK_IN];
	else
	{
		if (m_bIsFocused)
			crColor = m_crColors[BTNST_COLOR_BK_FOCUS];
		else
			crColor = m_crColors[BTNST_COLOR_BK_OUT];
	} // else

	CBrush		brBackground(crColor);

	pDC->FillRect(pRect, &brBackground);
	*/
	//modify by starefu 2008-7-25
	HINSTANCE hBgInstResource = NULL;
    hBgInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBkgndImageID), RT_BITMAP);
	HBITMAP m_hBmBkgnd = ::LoadBitmap(hBgInstResource, MAKEINTRESOURCE(nBkgndImageID));
	UINT nCtlID = ::GetDlgCtrlID(this->m_hWnd);
	HBRUSH m_hBrushCtl = GetBkBrush( this->GetParent()->m_hWnd, nCtlID, m_hBmBkgnd );

	pDC->FillRect(pRect,CBrush::FromHandle(m_hBrushCtl));

	return BTNST_OK;
} // End of OnDrawBackground

// This function is called every time the button border needs to be painted.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CCePngButtonST::OnDrawBorder(CDC* pDC, LPCRECT pRect)
{
	if (m_bIsPressed)
		pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
	else
		if (m_bIsFlat == FALSE || (m_bIsFlat && m_bMouseOnButton))
			pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));

	return BTNST_OK;
} // End of OnDrawBorder

void CALLBACK CCePngButtonST::TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	POINT	csPos;
	RECT	csRect;

	::GetCursorPos(&csPos);
    ::ScreenToClient(hwnd, &csPos);

	::GetClientRect(hwnd, &csRect);

	if (!::PtInRect(&csRect, csPos))
	{
		::PostMessage(hwnd, WM_MOUSELEAVE, 0, 0);
		//m_bMouseOnButton = FALSE;
		//Invalidate();
	} // if
} // End of TimerProc

#undef BS_TYPEMASK
#undef WM_MOUSELEAVE

/*
void CCePngButtonST::OnCaptureChanged(CWnd *pWnd) 
{
	if (m_bMouseOnButton)
	{
		ReleaseCapture();
		Invalidate();
	} // if

	CButton::OnCaptureChanged(pWnd);
} // End of OnCaptureChanged
*/

//add by starefu or fuxing to transparent the button bkgnd 2008-7-26
#define _X(x) (x.left) 
#define _Y(x) (x.top) 
#define _W(x) (x.right - x.left) 
#define _H(x) (x.bottom - x.top) 

//************************************************************************************** 
// 
// GetBkBrush( HWND hWnd, UINT nID, HBITMAP hBmBk ) 
//  
// Creates Background brush for the control specified by nID 
// according to its position in the parent dialog window. 
// 
// hWnd [in]: Handle to the parent window 
//  nID [in]: Control ID 
//  hBmBk [in]: Bitmap handle of the parent dialog's background image 
// 
// 
//************************************************************************************** 

HBRUSH GetBkBrush( HWND hWnd, UINT nID, HBITMAP hBmBk ) 
{ 
	HWND hWndCtrl; 

	hWndCtrl = ::GetDlgItem( hWnd, nID ); 

	HBRUSH hBrushCtrl = NULL; 

	if( NULL != hWndCtrl ) 
	{ 
		RECT rcCtrl; 

		::GetWindowRect( hWndCtrl, &rcCtrl ); 
		::ScreenToClient(hWnd, (LPPOINT)&rcCtrl); 
		::ScreenToClient(hWnd, ((LPPOINT)&rcCtrl)+1); 

		HDC hDC = ::GetDC(hWnd); 

		HDC hMemDCBk = CreateCompatibleDC( hDC ); 
		HDC hMemDCCtrl = CreateCompatibleDC( hDC ); 

		HBITMAP hBmCtrl = CreateCompatibleBitmap( hDC, _W(rcCtrl), _H(rcCtrl) ); 

		HBITMAP hBmOldBk; 
		HBITMAP hBmOldCtrl; 

		hBmOldBk = (HBITMAP) ::SelectObject( hMemDCBk, hBmBk ); 
		hBmOldCtrl = (HBITMAP) ::SelectObject( hMemDCCtrl, hBmCtrl ); 

		::BitBlt( hMemDCCtrl, 0, 0, _W(rcCtrl), _H(rcCtrl), hMemDCBk, _X(rcCtrl), _Y(rcCtrl), SRCCOPY ); 

		::SelectObject(hMemDCCtrl, hBmOldCtrl ); 
		::SelectObject(hMemDCBk, hBmOldBk ); 

		hBrushCtrl = ::CreatePatternBrush( hBmCtrl ); 

		DeleteObject( hBmCtrl ); 

		::DeleteDC( hMemDCBk ); 
		::DeleteDC( hMemDCCtrl ); 
		::ReleaseDC( hWnd, hDC ); 
	} 

	return hBrushCtrl; 
} 
