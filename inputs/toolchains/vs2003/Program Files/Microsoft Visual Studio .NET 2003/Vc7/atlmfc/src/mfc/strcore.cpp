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
#include "fixalloc.h"
#include <afxtempl.h>

#ifdef AFX_CORE1_SEG
#pragma code_seg(AFX_CORE1_SEG)
#endif

// MFC-enabled compilation. Use MFC memory management and exceptions;
// also, use MFC module state.

LPWSTR AFXAPI AfxA2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars)
{
	return AtlA2WHelper(lpw, lpa, nChars,CP_ACP);
}

LPSTR AFXAPI AfxW2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars)
{
	return AtlW2AHelper(lpa, lpw, nChars, CP_ACP);
}

///////////////////////////////////////////////////////////////////////////////
// CComBSTR support for template collections

template<> UINT AFXAPI HashKey<CComBSTR> (CComBSTR key)
{
	UINT nHash = 0;
	int iLength = key.Length();
	BSTR str = key.m_str;

	for( int i = 0; i < iLength; i++ )
	{
		nHash = (nHash<<5) + nHash + *str;
		str++;
	}
	return nHash;
}

template<>
void AFXAPI SerializeElements< CComBSTR >(CArchive& ar, CComBSTR* pElements, INT_PTR nCount)
{
	SerializeElementsInsertExtract(ar, pElements, nCount);
}

///////////////////////////////////////////////////////////////////////////////
// CString support for template collections

#if _MSC_VER >= 1100
template<> UINT AFXAPI HashKey<LPCWSTR> (LPCWSTR key)
#else
UINT AFXAPI HashKey(LPCWSTR key)
#endif
{
	UINT nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

#if _MSC_VER >= 1100
template<> UINT AFXAPI HashKey<LPCSTR> (LPCSTR key)
#else
UINT AFXAPI HashKey(LPCSTR key)
#endif
{
	UINT nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

template<>
void AFXAPI SerializeElements< CStringA >(CArchive& ar, CStringA* pElements, INT_PTR nCount)
{
	SerializeElementsInsertExtract(ar, pElements, nCount);
}

template<>
void AFXAPI SerializeElements< CStringW >(CArchive& ar, CStringW* pElements, INT_PTR nCount)
{
	SerializeElementsInsertExtract(ar, pElements, nCount);
}

#pragma warning(disable: 4074)
#pragma init_seg(compiler)

class CAfxStringMgr :
	public IAtlStringMgr
{
public:
	CAfxStringMgr()
	{
		m_nil.SetManager( this );
	}

// IAtlStringMgr
public:
	virtual CStringData* Allocate( int nChars, int nCharSize );
	virtual void Free( CStringData* pData );
	virtual CStringData* Reallocate( CStringData* pData, int nChars, int nCharSize );
	virtual CStringData* GetNilString();
	virtual IAtlStringMgr* Clone();

protected:
	CNilStringData m_nil;
};

CAfxStringMgr afxStringManager;

IAtlStringMgr* AFXAPI AfxGetStringManager()
{
	return &afxStringManager;
}

CStringData* CAfxStringMgr::Allocate( int nChars, int nCharSize )
{
	size_t nTotalSize;
	CStringData* pData;
	size_t nDataBytes;

	ASSERT(nCharSize > 0);
	
	if(nChars < 0)
	{
		ASSERT(FALSE);
		return NULL;
	}
	
	nDataBytes = (nChars+1)*nCharSize;
	nTotalSize = sizeof( CStringData )+nDataBytes;
	pData = (CStringData*)malloc( nTotalSize );
	if (pData == NULL)
		return NULL;
	pData->pStringMgr = this;
	pData->nRefs = 1;
	pData->nAllocLength = nChars;
	pData->nDataLength = 0;

	return pData;
}

void CAfxStringMgr::Free( CStringData* pData )
{
	free(pData);
}

CStringData* CAfxStringMgr::Reallocate( CStringData* pData, int nChars, int nCharSize )
{
	CStringData* pNewData;
	size_t nTotalSize;
	size_t nDataBytes;
	
	ASSERT(nCharSize > 0);
	
	if(nChars < 0)
	{
		ASSERT(FALSE);
		return NULL;
	}
	
	nDataBytes = (nChars+1)*nCharSize;
	nTotalSize = sizeof( CStringData )+nDataBytes;
	pNewData = (CStringData*)realloc( pData, nTotalSize );
	if( pNewData == NULL )
	{
		return NULL;
	}
	pNewData->nAllocLength = nChars;

	return pNewData;
}


CStringData* CAfxStringMgr::GetNilString()
{
	m_nil.AddRef();
	return &m_nil;
}

IAtlStringMgr* CAfxStringMgr::Clone()
{
	return this;
}

/////////////////////////////////////////////////////////////////////////////
