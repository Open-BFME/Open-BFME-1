// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLSTR_H__
#define __ATLSTR_H__

#pragma once

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#include <atlbase.h>

#include <winnls.h>
#include <limits.h>

#include <cstringt.h>

namespace ATL
{

class CAtlStringMgr :
	public IAtlStringMgr
{
public:
	CAtlStringMgr( IAtlMemMgr* pMemMgr = NULL ) throw() :
		m_pMemMgr( pMemMgr )
	{
		m_nil.SetManager( this );
	}
	virtual ~CAtlStringMgr() throw()
	{
	}

	void SetMemoryManager( IAtlMemMgr* pMemMgr ) throw()
	{
		ATLASSERT( m_pMemMgr == NULL );
		m_pMemMgr = pMemMgr;
	}

// IAtlStringMgr
public:
	virtual CStringData* Allocate( int nChars, int nCharSize ) throw()
	{
		size_t nTotalSize;
		CStringData* pData;
		size_t nDataBytes;

		nChars = AtlAlignUp( nChars + 1, 8 );  // Prevent excessive reallocation.  The heap will usually round up anyway.

		nDataBytes = nChars*nCharSize;
		nTotalSize = sizeof( CStringData )+nDataBytes;
		pData = static_cast< CStringData* >( m_pMemMgr->Allocate( nTotalSize ) );
		if( pData == NULL )
		{
			return( NULL );
		}
		pData->pStringMgr = this;
		pData->nRefs = 1;
		pData->nAllocLength = nChars - 1;
		pData->nDataLength = 0;

		return( pData );
	}
	virtual void Free( CStringData* pData ) throw()
	{
		ATLASSERT( pData->pStringMgr == this );
		m_pMemMgr->Free( pData );
	}
	virtual CStringData* Reallocate( CStringData* pData, int nChars, int nCharSize ) throw()
	{
		CStringData* pNewData;
		ULONG nTotalSize;
		ULONG nDataBytes;

		ATLASSERT( pData->pStringMgr == this );
		nChars = AtlAlignUp( nChars+1, 8 );  // Prevent excessive reallocation.  The heap will usually round up anyway.

		nDataBytes = nChars*nCharSize;
		nTotalSize = sizeof( CStringData )+nDataBytes;
		pNewData = static_cast< CStringData* >( m_pMemMgr->Reallocate( pData, nTotalSize ) );
		if( pNewData == NULL )
		{
			return NULL;
		}
		pNewData->nAllocLength = nChars - 1;

		return pNewData;
	}
	virtual CStringData* GetNilString() throw()
	{
		m_nil.AddRef();
		return &m_nil;
	}
	virtual IAtlStringMgr* Clone() throw()
	{
		return this;
	}

protected:
	IAtlMemMgr* m_pMemMgr;
	CNilStringData m_nil;
};

extern CAtlStringMgr g_strmgr;

template< typename _CharType = char >
class ChTraitsOS :
	public ChTraitsBase< _CharType >
{
public:
	static int tclen(LPCSTR p) throw()
	{
		ATLASSERT(p != NULL);
		LPCSTR pnext = CharNext(p);
		return ((pnext-p)>1) ? 2 : 1;
	}
	static LPCSTR strchr(LPCSTR p, char ch) throw()
	{
		ATLASSERT(p != NULL);
		//strchr for '\0' should succeed
		do
		{
			if (*p == ch)
			{
				return p;
			}
			p = CharNext(p);
		} while( *p != 0 );

		return NULL;
	}
	static LPCSTR strchr_db(LPCSTR p, char ch1, char ch2) throw()
	{
		ATLASSERT(p != NULL);
		while (*p != 0)
		{
			if (*p == ch1 && *(p+1) == ch2)
			{
				return p;
			}
			p = CharNext(p);
		}
		return NULL;
	}
	static LPCSTR strrchr(LPCSTR p, char ch) throw()
	{
		ATLASSERT(p != NULL);
		const _CharType* pch = NULL;
		while (*p != 0)
		{
			if (*p == ch)
				pch = p;
			p = CharNext(p);
		}
		return const_cast< _CharType* >( pch );
	}
	static _CharType* _strrev(_CharType* psz) throw()
	{
		// Optimize NULL, zero-length, and single-char case.
		if ((psz == NULL) || (psz[0] == '\0') || (psz[1] == '\0'))
			return psz;

		_CharType* p = psz;

		while (p[1] != 0) 
		{
			_CharType* pNext = CharNext(p);
			if(pNext > p + 1)
			{
				char p1 = *p;
				*p = *(p + 1);
				*(p + 1) = p1;
			}
			p = pNext;
		}

		_CharType* q = psz;

		while (q < p)
		{
			_CharType t = *q;
			*q = *p;
			*p = t;
			q++;
			p--;
		}
		return psz;
	}
	static LPCSTR strstr(LPCSTR pStr, LPCSTR pCharSet) throw()
	{
		ATLASSERT(pStr != NULL);
		int nLen = lstrlenA(pCharSet);
		if (nLen == 0)
			return pStr;

		const _CharType* pMatch;
		const _CharType* pStart = pStr;
		while ((pMatch = strchr(pStart, *pCharSet)) != NULL)
		{
			if (memcmp(pMatch, pCharSet, nLen*sizeof(_CharType)) == 0)
				return pMatch;
			pStart = CharNextA(pMatch);
		}

		return NULL;
	}
	static int strspn(const _CharType* pStr, const _CharType* pCharSet) throw()
	{
		ATLASSERT(pStr != NULL);
		int nRet = 0;
		_CharType* p = const_cast<_CharType*>(pStr);
		while (*p != 0)
		{
			_CharType* pNext = CharNext(p);
			if(pNext > p + 1)
			{
				if(strchr_db(pCharSet, *p, *(p+1)) == NULL)
					break;
				nRet += 2;
			}
			else
			{
				if(strchr(pCharSet, *p) == NULL)
					break;
				nRet++;
			}
			p = pNext;
		}
		return nRet;
	}
	static int strcspn(const _CharType* pStr, const _CharType* pCharSet) throw()
	{
		ATLASSERT(pStr != NULL);
		int nRet = 0;
		_CharType* p = const_cast<_CharType*>(pStr);
		while (*p != 0)
		{
			_CharType* pNext = CharNext(p);
			if(pNext > p + 1)
			{
				if(strchr_db(pCharSet, *p, *(p+1)) != NULL)
					break;
				nRet += 2;
			}
			else
			{
				if(strchr(pCharSet, *p) != NULL)
					break;
				nRet++;
			}
			p = pNext;
		}
		return nRet;
	}
	static LPCSTR strpbrk(LPCSTR p, LPCSTR lpszCharSet) throw()
	{
		ATLASSERT(p != NULL);
		while (*p != 0)
		{
			if (strchr(lpszCharSet, *p) != NULL)
			{
				return p;
			}
			p = CharNext(p);
		}
		return NULL;
	}

	static _CharType* CharNext(const _CharType* p) throw()
	{
		ATLASSERT(p != NULL);
		if (*p == '\0')  // ::CharNextA won't increment if we're at a \0 already
			return const_cast<_CharType*>(p+1);
		else
			return ::CharNextA(p);
	}

	static int IsDigit(_CharType ch) throw()
	{
		WORD type;
		GetStringTypeExA(GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
		return (type & C1_DIGIT) == C1_DIGIT;
	}

	static int IsSpace(_CharType ch) throw()
	{
		WORD type;
		GetStringTypeExA(GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
		return (type & C1_SPACE) == C1_SPACE;
	}

	static int StringCompare(const _CharType* pstrOne,
		const _CharType* pstrOther) throw()
	{
		return lstrcmpA((LPCSTR) pstrOne, (LPCSTR) pstrOther);
	}

	static int StringCompareIgnore(const _CharType* pstrOne,
		const _CharType* pstrOther) throw()
	{
		return lstrcmpiA((LPCSTR) pstrOne, (LPCSTR) pstrOther);
	}

	static int StringCollate(const _CharType* pstrOne,
		const _CharType* pstrOther) throw()
	{
		int nRet = CompareStringA(GetThreadLocale(), 0, (LPCSTR)pstrOne, -1, 
			(LPCSTR)pstrOther, -1);
		ATLASSERT(nRet != 0);
		return nRet-2;  // Convert to strcmp convention.  This really is documented.
	}

	static int StringCollateIgnore(const _CharType* pstrOne,
		const _CharType* pstrOther) throw()
	{
		int nRet = CompareStringA(GetThreadLocale(), NORM_IGNORECASE, (LPCSTR)pstrOne, -1, 
			(LPCSTR)pstrOther, -1);
		ATLASSERT(nRet != 0);
		return nRet-2;  // Convert to strcmp convention.  This really is documented.
	}

	static LPCSTR StringFindString(LPCSTR pstrBlock,
		LPCSTR pstrMatch) throw()
	{
		return strstr(pstrBlock, pstrMatch);
	}

	static LPSTR StringFindString(LPSTR pszBlock, LPCSTR pszMatch) throw()
	{
		return( const_cast< LPSTR >( StringFindString( const_cast< LPCSTR >( pszBlock ), pszMatch ) ) );
	}

	static LPCSTR StringFindChar(LPCSTR pszBlock,
		char chMatch) throw()
	{
		return strchr(pszBlock, chMatch);
	}

	static LPCSTR StringFindCharRev(LPCSTR psz, char ch) throw()
	{
		return strrchr(psz, ch);
	}

	static LPCSTR StringScanSet(LPCSTR pszBlock,
		LPCSTR pszMatch) throw()
	{
		return strpbrk(pszBlock, pszMatch);
	}

	static int StringSpanIncluding(const _CharType* pstrBlock,
		const _CharType* pstrSet) throw()
	{
		return strspn(pstrBlock, pstrSet);
	}

	static int StringSpanExcluding(const _CharType* pstrBlock,
		const _CharType* pstrSet) throw()
	{
		return strcspn(pstrBlock, pstrSet);
	}

	static _CharType* StringUppercase(_CharType* psz) throw()
	{
		return CharUpperA( psz );
	}

	static _CharType* StringLowercase(_CharType* psz) throw()
	{
		return CharLowerA( psz );
	}

	static _CharType* StringReverse(_CharType* psz) throw()
	{
		return _strrev( psz );
	}

	static int GetFormattedLength(const _CharType* pszFormat, va_list args) throw()
	{
		_CharType szBuffer[1028];

		// wvsprintf always truncates the output to 1024 character plus
		// the '\0'.
		int nLength = wvsprintfA(szBuffer, pszFormat, args);
		ATLASSERT(nLength >= 0);
		ATLASSERT(nLength <= 1024);

		return nLength;
	}

	static int Format(_CharType* pszBuffer, const _CharType* pszFormat,
		va_list args) throw()
	{
		return wvsprintfA(pszBuffer, pszFormat, args);
	}

	static int GetBaseTypeLength(const char* pszSrc) throw()
	{
		// Returns required buffer length in XCHARs
		return lstrlenA(pszSrc);
	}

	static int GetBaseTypeLength(const char* pszSrc, int nLength) throw()
	{
		(void)pszSrc;
		// Returns required buffer length in XCHARs
		return nLength;
	}

	static int GetBaseTypeLength(const wchar_t* pszSrc) throw()
	{
		// Returns required buffer length in XCHARs
		return ::WideCharToMultiByte(_AtlGetConversionACP(), 0, pszSrc, -1, NULL, 0, NULL, NULL)-1;
	}

	static int GetBaseTypeLength(const wchar_t* pszSrc, int nLength) throw()
	{
		// Returns required buffer length in XCHARs
		return ::WideCharToMultiByte(_AtlGetConversionACP(), 0, pszSrc, nLength, NULL, 0, NULL, NULL);
	}

	static void ConvertToBaseType(_CharType* pszDest, int nDestLength,
		const char* pszSrc, int nSrcLength = -1) throw()
	{
		(void)nSrcLength;
		// nLen is in chars
		memcpy(pszDest, pszSrc, nDestLength*sizeof(_CharType));
	}

	static void ConvertToBaseType(_CharType* pszDest, int nDestLength,
		const wchar_t* pszSrc, int nSrcLength = -1) throw()
	{
		// nLen is in XCHARs
		::WideCharToMultiByte(_AtlGetConversionACP(), 0, pszSrc, nSrcLength, pszDest, nDestLength, NULL, NULL);
	}

	static void ConvertToOem(_CharType* pstrString) throw()
	{
		::AnsiToOem(pstrString, pstrString);
	}

	static void ConvertToAnsi(_CharType* pstrString) throw()
	{
		::OemToAnsi(pstrString, pstrString);
	}

	static void FloodCharacters(_CharType ch, int nLength, _CharType* pstr) throw()
	{
		// nLength is in XCHARs
		memset(pstr, ch, nLength);
	}

	static BSTR AllocSysString(const _CharType* pchData, int nDataLength) throw()
	{
		int nLen = MultiByteToWideChar(_AtlGetConversionACP(), 0, pchData, nDataLength,
			NULL, NULL);
		BSTR bstr = ::SysAllocStringLen(NULL, nLen);
		if (bstr != NULL)
		{
			MultiByteToWideChar(_AtlGetConversionACP(), 0, pchData, nDataLength,
				bstr, nLen);
		}

		return bstr;
	}

	static BOOL ReAllocSysString(const _CharType* pchData, BSTR* pbstr,
		int nDataLength) throw()
	{
		int nLen = MultiByteToWideChar(_AtlGetConversionACP(), 0, pchData,
			nDataLength, NULL, NULL);
		BOOL bSuccess =::SysReAllocStringLen(pbstr, NULL, nLen);
		if (bSuccess)
		{
			MultiByteToWideChar(_AtlGetConversionACP(), 0, pchData, nDataLength,
				*pbstr, nLen);
		}

		return bSuccess;
	}

	static DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource,
		DWORD dwMessageID, DWORD dwLanguageID, char* pstrBuffer,
		DWORD nSize, va_list* pArguments) throw()
	{
		return ::FormatMessageA(dwFlags, lpSource, dwMessageID, dwLanguageID,
				pstrBuffer, nSize, pArguments);
	}

	static int SafeStringLen(const char* psz) throw()
	{
		// returns length in bytes
		return (psz != NULL) ? lstrlenA(psz) : 0;
	}

	static int SafeStringLen(const wchar_t* psz) throw()
	{
		// returns length in wchar_ts
		return (psz != NULL) ? lstrlenW(psz) : 0;
	}

	static int GetCharLen(const wchar_t*) throw()
	{
		// returns char length
		return 1;
	}
	static int GetCharLen(const char* psz) throw()
	{
		const char* p = ::CharNextA(psz);
		return (p - psz);
	}

	static DWORD GetEnvironmentVariable(const _CharType* pstrVar,
		_CharType* pstrBuffer, DWORD dwSize) throw()
	{
		return ::GetEnvironmentVariableA(pstrVar, pstrBuffer, dwSize);
	}
};

// specialization for wchar_t
template<>
class ChTraitsOS< wchar_t > :
	public ChTraitsBase< wchar_t >
{
protected:
#if defined(_UNICODE) && !defined(_CSTRING_ALWAYS_THUNK)
	static int CompareStringW(LCID lcid, DWORD dwFlags, 
		LPCWSTR pszString1, int nLength1, LPCWSTR pszString2, int nLength2)
	{
		return ::CompareStringW(lcid, dwFlags, pszString1, nLength1, 
			pszString2, nLength2);
	}
	static BOOL GetStringTypeExW(LCID lcid, DWORD dwInfoType, LPCWSTR pszSrc,
		int nLength, LPWORD pwCharType)
	{
		return ::GetStringTypeExW(lcid, dwInfoType, pszSrc, nLength, pwCharType);
	}
	static int lstrcmpiW(LPCWSTR psz1, LPCWSTR psz2)
	{
		return ::lstrcmpiW(psz1, psz2);
	}
	static LPWSTR CharLowerW(LPWSTR psz)
	{
		return ::CharLowerW(psz);
	}
	static LPWSTR CharUpperW(LPWSTR psz)
	{
		return ::CharUpperW(psz);
	}
	static DWORD _GetEnvironmentVariableW(LPCWSTR pszName, LPWSTR pszBuffer, DWORD nSize)
	{
		return ::GetEnvironmentVariableW(pszName, pszBuffer, nSize);
	}
#else  // !_UNICODE
	static int WINAPI CompareStringW(LCID lcid, DWORD dwFlags, 
		LPCWSTR pszString1, int nLength1, LPCWSTR pszString2, int nLength2)
	{
		return _strthunks.pfnCompareStringW(lcid, dwFlags, pszString1, nLength1, pszString2, nLength2);
	}
	static BOOL WINAPI GetStringTypeExW(LCID lcid, DWORD dwInfoType, LPCWSTR pszSrc,
		int nLength, LPWORD pwCharType)
	{
		return _strthunks.pfnGetStringTypeExW(lcid, dwInfoType, pszSrc, nLength, pwCharType);
	}
	static int WINAPI lstrcmpiW(LPCWSTR psz1, LPCWSTR psz2)
	{
		return _strthunks.pfnlstrcmpiW(psz1, psz2);
	}
	static LPWSTR WINAPI CharLowerW(LPWSTR psz)
	{
		ATLASSERT(HIWORD(psz) != 0);  // No single chars
		return _strthunks.pfnCharLowerW(psz);
	}
	static LPWSTR WINAPI CharUpperW(LPWSTR psz)
	{
		ATLASSERT(HIWORD(psz) != 0);  // No single chars
		return _strthunks.pfnCharUpperW(psz);
	}
	static DWORD _GetEnvironmentVariableW(LPCWSTR pszName, LPWSTR pszBuffer, DWORD nSize)
	{
		return _strthunks.pfnGetEnvironmentVariableW(pszName, pszBuffer, nSize);
	}
#endif  // !_UNICODE

public:
	static int tclen(const wchar_t*) throw()
	{
		return 1;
	}
	static LPCWSTR strchr(LPCWSTR p, wchar_t ch) throw()
	{
		//strchr for '\0' should succeed
		while (*p != 0)
		{
			if (*p == ch)
			{
				return p;
			}
			p++;
		}
		return (*p == ch) ? p : NULL;
	}
	static LPCWSTR strrchr(LPCWSTR p, wchar_t ch) throw()
	{
		const wchar_t* pch = p+lstrlenW(p);
		while ((pch != p) && (*pch != ch))
		{
			pch--;
		}
		if (*pch == ch)
		{
			return pch;
		}
		else
		{
			return NULL;
		}
	}
	static wchar_t* _strrev(wchar_t* psz) throw()
	{
		// Optimize NULL, zero-length, and single-char case.
		if ((psz == NULL) || (psz[0] == L'\0') || (psz[1] == L'\0'))
			return psz;

		wchar_t* p = psz+(lstrlenW( psz )-1);
		wchar_t* q = psz;
		while(q < p)
		{
			wchar_t t = *q;
			*q = *p;
			*p = t;
			q++;
			p--;
		}
		return psz;
	}
	static LPCWSTR strstr(LPCWSTR pStr, LPCWSTR pCharSet) throw()
	{
		int nLen = lstrlenW(pCharSet);
		if (nLen == 0)
			return pStr;

		const wchar_t* pMatch;
		const wchar_t* pStart = pStr;
		while ((pMatch = strchr(pStart, *pCharSet)) != NULL)
		{
			if (memcmp(pMatch, pCharSet, nLen*sizeof(wchar_t)) == 0)
				return pMatch;
			pStart++;
		}

		return NULL;
	}
	static int strspn(const wchar_t* psz, const wchar_t* pszCharSet) throw()
	{
		int nRet = 0;
		const wchar_t* p = psz;
		while (*p != 0)
		{
			if(strchr(pszCharSet, *p) == NULL)
				break;
			nRet++;
			p++;
		}
		return nRet;
	}
	static int strcspn(const wchar_t* psz, const wchar_t* pszCharSet) throw()
	{
		int nRet = 0;
		const wchar_t* p = psz;
		while (*p != 0)
		{
			if(strchr(pszCharSet, *p) != NULL)
				break;
			nRet++;
			p++;
		}
		return nRet;
	}
	static LPCWSTR strpbrk(LPCWSTR psz, LPCWSTR pszCharSet) throw()
	{
		const wchar_t* p = psz;
		while (*p != 0)
		{
			if (strchr(pszCharSet, *p) != NULL)
				return p;
			p++;
		}
		return NULL;
	}

	static wchar_t* CharNext(const wchar_t* p) throw()
	{
		return const_cast< wchar_t* >( p+1 );
	}

	static int IsDigit(wchar_t ch) throw()
	{
		WORD type;
		GetStringTypeExW(0, CT_CTYPE1, &ch, 1, &type);
		return (type & C1_DIGIT) == C1_DIGIT;
	}

	static int IsSpace(wchar_t ch) throw()
	{
		WORD type;
		GetStringTypeExW(0, CT_CTYPE1, &ch, 1, &type);
		return (type & C1_SPACE) == C1_SPACE;
	}


	static int StringCompare(const wchar_t* pstrOne,
		const wchar_t* pstrOther) throw()
	{
		return wcscmp(pstrOne, pstrOther);
	}

	static int StringCompareIgnore(const wchar_t* pstrOne,
		const wchar_t* pstrOther) throw()
	{
		return lstrcmpiW(pstrOne, pstrOther);
	}

	static int StringCollate(const wchar_t* pstrOne,
		const wchar_t* pstrOther) throw()
	{ 
		int nRet;

		nRet = CompareStringW(GetThreadLocale(), 0, pstrOne, -1, pstrOther, -1);
		ATLASSERT(nRet != 0);
		return nRet-2;  // Convert to strcmp convention.  This really is documented.
	}

	static int StringCollateIgnore(const wchar_t* pstrOne,
		const wchar_t* pstrOther) throw()
	{
		int nRet = CompareStringW(GetThreadLocale(), NORM_IGNORECASE, 
			pstrOne, -1, pstrOther, -1);
		ATLASSERT(nRet != 0);
		return nRet-2;  // Convert to strcmp convention.  This really is documented.
	}

	static LPCWSTR StringFindString(LPCWSTR pstrBlock,
		LPCWSTR pstrMatch) throw()
	{
		return strstr(pstrBlock, pstrMatch);
	}

	static LPWSTR StringFindString( LPWSTR pszBlock, LPCWSTR pszMatch ) throw()
	{
		return( const_cast< LPWSTR >( StringFindString( const_cast< LPCWSTR >( pszBlock ), pszMatch ) ) );
	}

	static LPCWSTR StringFindChar(LPCWSTR pstrBlock,
		wchar_t pstrMatch) throw()
	{
		return strchr(pstrBlock, pstrMatch);
	}

	static LPCWSTR StringFindCharRev(LPCWSTR pstr, wchar_t ch) throw()
	{
		return strrchr(pstr, ch);
	}

	static LPCWSTR StringScanSet(LPCWSTR pszBlock,
		LPCWSTR pszMatch) throw()
	{
		return strpbrk(pszBlock, pszMatch);
	}

	static int StringSpanIncluding(const wchar_t* pszBlock,
		const wchar_t* pszSet) throw()
	{
		return strspn(pszBlock, pszSet);
	}

	static int StringSpanExcluding(const wchar_t* pszBlock,
		const wchar_t* pszSet) throw()
	{
		return strcspn(pszBlock, pszSet);
	}

	static wchar_t* StringUppercase(wchar_t* psz) throw()
	{
		CharUpperW(psz);
		return psz;
	}

	static wchar_t* StringLowercase(wchar_t* psz) throw()
	{
		CharLowerW(psz);
		return psz;
	}

	static wchar_t* StringReverse(wchar_t* psz) throw()
	{
		return _strrev(psz);
	}

#ifdef _UNICODE
	static int GetFormattedLength(const wchar_t* pszFormat, va_list args) throw()
	{
		wchar_t szBuffer[1028];

		// wvsprintf always truncates the output to 1024 character plus
		// the '\0'.
		int nLength = wvsprintfW(szBuffer, pszFormat, args);
		ATLASSERT(nLength >= 0);
		ATLASSERT(nLength <= 1024);

		return nLength;
	}

	static int Format(wchar_t* pszBuffer, const wchar_t* pszFormat,
		va_list args) throw()
	{
		return wvsprintfW(pszBuffer, pszFormat, args);
	}
#endif

	static int GetBaseTypeLength(const char* pszSrc) throw()
	{
		// Returns required buffer size in wchar_ts
		return ::MultiByteToWideChar(_AtlGetConversionACP(), 0, pszSrc, -1, NULL, 0)-1;
	}

	static int GetBaseTypeLength(const char* pszSrc, int nLength) throw()
	{
		// Returns required buffer size in wchar_ts
		return ::MultiByteToWideChar(_AtlGetConversionACP(), 0, pszSrc, nLength, NULL, 0);
	}

	static int GetBaseTypeLength(const wchar_t* pszSrc) throw()
	{
		// Returns required buffer size in wchar_ts
		return lstrlenW(pszSrc);
	}

	static int GetBaseTypeLength(const wchar_t* pszSrc, int nLength) throw()
	{
		(void)pszSrc;
		// Returns required buffer size in wchar_ts
		return nLength;
	}

	static void ConvertToBaseType(wchar_t* pszDest, int nDestLength,
		const char* pszSrc, int nSrcLength = -1) throw()
	{
		// nLen is in wchar_ts
		::MultiByteToWideChar(_AtlGetConversionACP(), 0, pszSrc, nSrcLength, pszDest, nDestLength);
	}

	static void ConvertToBaseType(wchar_t* pszDest, int nDestLength,
		const wchar_t* pszSrc, int nSrcLength = -1) throw()
	{
		(void)nSrcLength;
		// nLen is in wchar_ts
		memcpy(pszDest, pszSrc, nDestLength*sizeof(wchar_t));
	}

	// this conversion on Unicode strings makes no sense
	/*
	static void ConvertToOem(wchar_t*)
	{
		ATLASSERT(FALSE);
	}
	*/

	// this conversion on Unicode strings makes no sense
	/*
	static void ConvertToAnsi(wchar_t*)
	{
		ATLASSERT(FALSE);
	}
	*/

	static void FloodCharacters(wchar_t ch, int nLength, wchar_t* pstr) throw()
	{
		// nLength is in XCHARs
		for (int i = 0; i < nLength; i++)
			pstr[i] = ch;
	}

	static BSTR AllocSysString(const wchar_t* pchData, int nDataLength) throw()
	{
		BSTR bstr = ::SysAllocStringLen(pchData, nDataLength);
		return bstr;
	}

	static BOOL ReAllocSysString(const wchar_t* pchData, BSTR* pbstr,
		int nDataLength) throw()
	{
		return ::SysReAllocStringLen(pbstr, pchData, nDataLength);
	}

#ifdef _UNICODE
	static DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource,
		DWORD dwMessageID, DWORD dwLanguageID, wchar_t* pstrBuffer,
		DWORD nSize, va_list* pArguments) throw()
	{
		return ::FormatMessageW(dwFlags, lpSource, dwMessageID, dwLanguageID,
				pstrBuffer, nSize, pArguments);
	}
#endif
	static int SafeStringLen(const char* psz) throw()
	{
		// returns length in bytes
		return (psz != NULL) ? lstrlenA(psz) : 0;
	}

	static int SafeStringLen(const wchar_t* psz) throw()
	{
		// returns length in wchar_ts
		return (psz != NULL) ? lstrlenW(psz) : 0;
	}

	static int GetCharLen(const wchar_t*) throw()
	{
		// returns char length
		return 1;
	}
	static int GetCharLen(const char* psz) throw()
	{
		LPCSTR p = ::CharNextA( psz );
		return int( p-psz );
	}

	static DWORD GetEnvironmentVariable(const wchar_t* pstrVar,
		wchar_t* pstrBuffer, DWORD dwSize) throw()
	{
		return ::GetEnvironmentVariableW(pstrVar, pstrBuffer, dwSize);
	}
};

template< typename _BaseType = char, class StringIterator = ChTraitsOS< _BaseType > >
class StrTraitATL : public StringIterator
{
public:
	static HINSTANCE FindStringResourceInstance(UINT nID) throw()
	{
		return( AtlFindStringResourceInstance( nID ) );
	}

	static IAtlStringMgr* GetDefaultManager() throw()
	{
		return( &g_strmgr );
	}
};

#if !defined(_ATL_CSTRING_NO_CRT) && defined(_ATL_MIN_CRT)
#define _ATL_CSTRING_NO_CRT
#endif

#ifndef _ATL_CSTRING_NO_CRT
typedef CStringT< wchar_t, StrTraitATL< wchar_t, ChTraitsCRT< wchar_t > > > CAtlStringW;
typedef CStringT< char, StrTraitATL< char, ChTraitsCRT< char > > > CAtlStringA;
typedef CStringT< TCHAR, StrTraitATL< TCHAR, ChTraitsCRT< TCHAR > > > CAtlString;
#else  // _ATL_CSTRING_NO_CRT
typedef CStringT< wchar_t, StrTraitATL< wchar_t > > CAtlStringW;
typedef CStringT< char, StrTraitATL< char > > CAtlStringA;
typedef CStringT< TCHAR, StrTraitATL< TCHAR > > CAtlString;
#endif  // _ATL_CSTRING_NO_CRT

#ifndef _AFX
typedef CAtlStringW CStringW;
typedef CAtlStringA CStringA;
typedef CAtlString CString;
#endif

template< typename T >
class CElementTraits;

template<>
class CElementTraits< ATL::CAtlStringA > :
	public CStringElementTraits< ATL::CAtlStringA >
{
};

template<>
class CElementTraits< ATL::CAtlStringW > :
	public CStringElementTraits< ATL::CAtlStringW >
{
};

}; //namespace ATL

#endif // __ATLSTR_H__

/////////////////////////////////////////////////////////////////////////////
