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

#ifdef AFX_CORE1_SEG
#pragma code_seg(AFX_CORE1_SEG)
#endif


#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Map from HMENU to CMenu *

CHandleMap* PASCAL afxMapHMENU(BOOL bCreate)
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	if (pState->m_pmapHMENU == NULL && bCreate)
	{
		BOOL bEnable = AfxEnableMemoryTracking(FALSE);
#ifndef _AFX_PORTABLE
		_PNH pnhOldHandler = AfxSetNewHandler(&AfxCriticalNewHandler);
#endif
		pState->m_pmapHMENU = new CHandleMap(RUNTIME_CLASS(CMenu),
			ConstructDestruct<CMenu>::Construct, ConstructDestruct<CMenu>::Destruct, 
			offsetof(CMenu, m_hMenu)),

#ifndef _AFX_PORTABLE
		AfxSetNewHandler(pnhOldHandler);
#endif
		AfxEnableMemoryTracking(bEnable);
	}
	return pState->m_pmapHMENU;
}

CMenu* PASCAL CMenu::FromHandle(HMENU hMenu)
{
	CHandleMap* pMap = afxMapHMENU(TRUE); // create map if not exist
	ASSERT(pMap != NULL);
	CMenu* pMenu = (CMenu*)pMap->FromHandle(hMenu);
	ASSERT(pMenu == NULL || pMenu->m_hMenu == hMenu);
	return pMenu;
}

CMenu* PASCAL CMenu::FromHandlePermanent(HMENU hMenu)
{
	CHandleMap* pMap = afxMapHMENU();
	CMenu* pMenu = NULL;
	if (pMap != NULL)
	{
		// only look in the permanent map - does no allocations
		pMenu = (CMenu*)pMap->LookupPermanent(hMenu);
		ASSERT(pMenu == NULL || pMenu->m_hMenu == hMenu);
	}
	return pMenu;
}

/////////////////////////////////////////////////////////////////////////////
// CMenu

#ifdef _DEBUG
void CMenu::AssertValid() const
{
	CObject::AssertValid();
	ASSERT(m_hMenu == NULL || ::IsMenu(m_hMenu));
}

void CMenu::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << "m_hMenu = " << m_hMenu;
	dc << "\n";
}
#endif

BOOL CMenu::Attach(HMENU hMenu)
{
	ASSERT(m_hMenu == NULL);        // only attach once, detach on destroy
	if (hMenu == NULL)
		return FALSE;
	CHandleMap* pMap = afxMapHMENU(TRUE); // create map if not exist
	ASSERT(pMap != NULL);
	pMap->SetPermanent(m_hMenu = hMenu, this);
	return TRUE;
}

HMENU CMenu::Detach()
{
	HMENU hMenu;
	if ((hMenu = m_hMenu) != NULL)
	{
		CHandleMap* pMap = afxMapHMENU(); // don't create if not exist
		if (pMap != NULL)
			pMap->RemoveHandle(m_hMenu);
	}
	m_hMenu = NULL;
	return hMenu;
}

BOOL CMenu::DestroyMenu()
{
	if (m_hMenu == NULL)
		return FALSE;
	return ::DestroyMenu(Detach());
}

int CMenu::GetMenuString(UINT nIDItem, CString& rString, UINT nFlags) const
{
	ASSERT(::IsMenu(m_hMenu)); 

	// offer no buffer first
	int nStringLen = ::GetMenuString(m_hMenu, nIDItem, NULL, 0, nFlags);

	// use exact buffer length
	if (nStringLen > 0)
	{
		LPTSTR pstrString = rString.GetBufferSetLength(nStringLen+1);
		::GetMenuString(m_hMenu, nIDItem, pstrString, nStringLen+1, nFlags);
		rString.ReleaseBuffer();
	}
	else
		rString.Empty();

	return nStringLen;
}

/////////////////////////////////////////////////////////////////////////////
// Self-drawing menu items
void CMenu::DrawItem(LPDRAWITEMSTRUCT /*pdis*/)
{
	// default does nothing
}

void CMenu::MeasureItem(LPMEASUREITEMSTRUCT /*pmis*/)
{
	// default does nothing
}

CChevronOwnerDrawMenu::CChevronOwnerDrawMenu()
{
	NONCLIENTMETRICS NonClientMetrics;
	NonClientMetrics.cbSize = sizeof(NONCLIENTMETRICS);

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS), &NonClientMetrics, 0);

	m_MenuFont.CreateFontIndirect(&NonClientMetrics.lfMenuFont);
}

void CChevronOwnerDrawMenu::DrawItem(LPDRAWITEMSTRUCT pdis)
{
	ASSERT(pdis->CtlType == ODT_MENU);

	CBitmap *pBmp;

	pBmp = (CBitmap *) pdis->itemData;
	ASSERT(pBmp);
	ASSERT_KINDOF(CBitmap, pBmp);
	if(pBmp && pBmp->IsKindOf(RUNTIME_CLASS(CBitmap)))
	{
		MENUITEMINFO info;

		ZeroMemory(&info, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_STRING;
		if(GetMenuItemInfo(pdis->itemID, &info))
		{
			CString strText;
			LPTSTR pszText;

			pszText = strText.GetBuffer(info.cch);
			info.dwTypeData = pszText;
			info.cch++; // space for zero terminator
			BOOL bCheck = GetMenuItemInfo(pdis->itemID, &info);
			strText.ReleaseBuffer();

			if(bCheck)
			{
				BITMAP bitmap;
				CDC *pDC;
				CSize Size;
				CRect rc, rcItem(pdis->rcItem);

				pBmp->GetObject(sizeof(BITMAP), &bitmap);

				COLORREF crMenu = ::GetSysColor(COLOR_MENU);

				// Find the rect that will center the bitmap in the menu item
				rc.top = rcItem.Height() / 2 - bitmap.bmHeight / 2 + rcItem.top - 1;
				rc.left = 0;
				rc.right = bitmap.bmWidth + 1;
				rc.bottom = bitmap.bmHeight + 1;
				rc.bottom += rc.top;
				rc.right += rc.left;

				pDC = CDC::FromHandle(pdis->hDC);
				int nSave = pDC->SaveDC();

				pDC->SelectObject(&m_MenuFont);
				Size = pDC->GetTextExtent(strText);

				// Selected (possibly grayed)
				if(pdis->itemState & ODS_SELECTED)
				{
					// MenuColor
					CRect rcFill(pdis->rcItem);
					rcFill.left = rc.right + 2;
					pDC->FillSolidRect(rcFill, ::GetSysColor(COLOR_HIGHLIGHT));

					// if not grayed and not checked, raise the button
					if(!(pdis->itemState & (ODS_GRAYED | ODS_CHECKED)))
						pDC->Draw3dRect(rc.left, rc.top, rc.Width() + 1, rc.Height() + 1,
							::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));

					// Text
					pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
					pDC->SetTextColor(
						(pdis->itemState & ODS_GRAYED) ? crMenu : ::GetSysColor(COLOR_HIGHLIGHTTEXT));

					pDC->ExtTextOut(rc.right + 3, rc.top + rc.Height() / 2 - Size.cy / 2,
						ETO_OPAQUE, NULL, strText, NULL);
				}
				else
				{
					pDC->FillSolidRect(&pdis->rcItem, crMenu);
					pDC->SetBkColor(crMenu);

					// Grayed (disabled)
					if(pdis->itemState & ODS_GRAYED)
					{
						pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));

						pDC->SetBkMode(TRANSPARENT);

						pDC->ExtTextOut(rc.right + 4, rc.top + rc.Height() / 2 - Size.cy / 2 + 1, ETO_OPAQUE, NULL, strText, NULL);
						pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
						pDC->ExtTextOut(rc.right + 3, rc.top + rc.Height() / 2 - Size.cy / 2, 0, NULL, strText, NULL);
					}
					// Everything else
					else
					{
						// if checked draw as pushed
						if(pdis->itemState & ODS_CHECKED)
							pDC->Draw3dRect(rc.left, rc.top, rc.Width() + 1, rc.Height() + 1,
								::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));

						pDC->SetBkColor(crMenu);
						pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
						pDC->ExtTextOut(rc.right + 3, rc.top + rc.Height() / 2 - Size.cy / 2, ETO_OPAQUE, NULL, strText, NULL);
					}
				}

				// The bitmap...
				CBitmap bmp;
				int x = 0, y = 0;
				if(pdis->itemState & ODS_GRAYED)
				{
					::AfxGetGrayBitmap(*pBmp, &bmp, crMenu);
					pBmp = &bmp;
				}
				else
					if(pdis->itemState & ODS_CHECKED)
					{
						::AfxGetDitheredBitmap(*pBmp, &bmp, crMenu, RGB(255, 255, 255));
						pBmp = &bmp;
					}

				CDC dcMem;
				dcMem.CreateCompatibleDC(NULL);
				dcMem.SelectObject(pBmp);

				rc.InflateRect(-1, -1);

				pDC->BitBlt(rc.left, rc.top, rc.right, rc.bottom, &dcMem, x, y, SRCCOPY);

				pDC->RestoreDC(nSave);
			}
		}
	}
}

void CChevronOwnerDrawMenu::MeasureItem(LPMEASUREITEMSTRUCT pmis)
{
	CBitmap *pBmp = (CBitmap *) pmis->itemData;
	ASSERT_KINDOF(CBitmap, pBmp);

	if(pBmp)
	{
		BITMAP bitmap;
		CString strText;
		LPTSTR pszText;
		MENUITEMINFO info;

		pBmp->GetBitmap(&bitmap);
		pmis->itemHeight = max(::GetSystemMetrics(SM_CYMENU), bitmap.bmHeight + 2);

		ZeroMemory(&info, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_STRING;
		if(GetMenuItemInfo(pmis->itemID, &info))
		{
			pszText = strText.GetBuffer(info.cch);
			info.dwTypeData = pszText;
			info.cch++;
			BOOL bCheck = GetMenuItemInfo(pmis->itemID, &info);
			strText.ReleaseBuffer();

			if(bCheck)
			{
				CWindowDC dc(NULL);

				CFont *pFont = dc.SelectObject(&m_MenuFont);
				CSize size = dc.GetTextExtent(strText);
				dc.SelectObject(pFont);

				// 1 pixel for gap, 2 for bitmap, 2 for menu item = 5
				// (disregard checkmark gap)
				pmis->itemWidth = bitmap.bmWidth + size.cx + 5;
			}
		}
	}
}

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

IMPLEMENT_DYNCREATE(CMenu, CObject)

/////////////////////////////////////////////////////////////////////////////
