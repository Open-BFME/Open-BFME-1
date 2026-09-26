// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <malloc.h>

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif


/////////////////////////////////////////////////////////////////////////////
// Cached system metrics, etc

AFX_DATADEF AUX_DATA afxData;

// Initialization code
AUX_DATA::AUX_DATA()
{
	// Cache various target platform version information
	DWORD dwVersion = ::GetVersion();
	bWin95 = (dwVersion & 0x80000000) != 0;

	// Cached system metrics (updated in CWnd::OnWinIniChange)
	UpdateSysMetrics();

	// Cached system values (updated in CWnd::OnSysColorChange)
	hbrBtnFace = NULL;
	UpdateSysColors();

	// Standard cursors
	hcurWait = ::LoadCursor(NULL, IDC_WAIT);
	hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
	ASSERT(hcurWait != NULL);
	ASSERT(hcurArrow != NULL);
	hcurHelp = NULL;    // loaded on demand

	// cxBorder2 and cyBorder are 2x borders for Win4
	cxBorder2 = CX_BORDER*2;
	cyBorder2 = CY_BORDER*2;

	// allocated on demand
	hbmMenuDot = NULL;
	hcurHelp = NULL;
}

#ifdef AFX_TERM_SEG
#pragma code_seg(AFX_TERM_SEG)
#endif

// Termination code
AUX_DATA::~AUX_DATA()
{
	// clean up objects we don't actually create
	AfxDeleteObject((HGDIOBJ*)&hbmMenuDot);
}

#ifdef AFX_CORE1_SEG
#pragma code_seg(AFX_CORE1_SEG)
#endif

void AUX_DATA::UpdateSysColors()
{
	clrBtnFace = ::GetSysColor(COLOR_BTNFACE);
	clrBtnShadow = ::GetSysColor(COLOR_BTNSHADOW);
	clrBtnHilite = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	clrBtnText = ::GetSysColor(COLOR_BTNTEXT);
	clrWindowFrame = ::GetSysColor(COLOR_WINDOWFRAME);

	hbrBtnFace = ::GetSysColorBrush(COLOR_BTNFACE);
	ASSERT(hbrBtnFace != NULL);
	hbrWindowFrame = ::GetSysColorBrush(COLOR_WINDOWFRAME);
	ASSERT(hbrWindowFrame != NULL);
}

void AUX_DATA::UpdateSysMetrics()
{
	// System metrics
	cxIcon = GetSystemMetrics(SM_CXICON);
	cyIcon = GetSystemMetrics(SM_CYICON);

	// System metrics which depend on subsystem version
	afxData.cxVScroll = GetSystemMetrics(SM_CXVSCROLL) + CX_BORDER;
	afxData.cyHScroll = GetSystemMetrics(SM_CYHSCROLL) + CY_BORDER;

	// Device metrics for screen
	HDC hDCScreen = GetDC(NULL);
	ASSERT(hDCScreen != NULL);
	cxPixelsPerInch = GetDeviceCaps(hDCScreen, LOGPIXELSX);
	cyPixelsPerInch = GetDeviceCaps(hDCScreen, LOGPIXELSY);
	ReleaseDC(NULL, hDCScreen);
}

/////////////////////////////////////////////////////////////////////////////
