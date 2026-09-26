// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLPATH_H__
#define __ATLPATH_H__

#pragma once

#ifdef _AFX
#include <afxstr.h>
#else
#include <atlstr.h>
#endif

#ifndef _ATL_NO_DEFAULT_LIBS
#pragma comment(lib, "shlwapi.lib")
#endif  // !_ATL_NO_DEFAULT_LIBS

namespace ATL
{

namespace ATLPath
{

inline char* AddBackslash( char* pszPath )
{
	return ::PathAddBackslashA( pszPath );
}

inline wchar_t* AddBackslash( wchar_t* pszPath )
{
	return ::PathAddBackslashW( pszPath );
}

inline BOOL AddExtension( char* pszPath, const char* pszExtension )
{
	return ::PathAddExtensionA( pszPath, pszExtension );
}

inline BOOL AddExtension( wchar_t* pszPath, const wchar_t* pszExtension )
{
	return ::PathAddExtensionW( pszPath, pszExtension );
}

inline BOOL Append( char* pszPath, const char* pszMore )
{
	return ::PathAppendA( pszPath, pszMore );
}

inline BOOL Append( wchar_t* pszPath, const wchar_t* pszMore )
{
	return ::PathAppendW( pszPath, pszMore );
}

inline char* BuildRoot( char* pszPath, int iDrive )
{
	return ::PathBuildRootA( pszPath, iDrive );
}

inline wchar_t* BuildRoot( wchar_t* pszPath, int iDrive )
{
	return ::PathBuildRootW( pszPath, iDrive );
}

inline BOOL Canonicalize( char* pszDest, const char* pszSrc )
{
	return ::PathCanonicalizeA( pszDest, pszSrc );
}

inline BOOL Canonicalize( wchar_t* pszDest, const wchar_t* pszSrc )
{
	return ::PathCanonicalizeW( pszDest, pszSrc );
}

inline char* Combine( char* pszDest, const char* pszDir,
	const char* pszFile )
{
	return ::PathCombineA( pszDest, pszDir, pszFile );
}

inline wchar_t* Combine( wchar_t* pszDest, const wchar_t* pszDir,
	const wchar_t* pszFile )
{
	return ::PathCombineW( pszDest, pszDir, pszFile );
}

inline int CommonPrefix( const char* pszFile1, const char* pszFile2,
	char* pszDest )
{
	return ::PathCommonPrefixA( pszFile1, pszFile2, pszDest );
}

inline int CommonPrefix( const wchar_t* pszFile1, const wchar_t* pszFile2,
	wchar_t* pszDest )
{
	return ::PathCommonPrefixW( pszFile1, pszFile2, pszDest );
}

inline BOOL FileExists( const char* pszPath )
{
	return ::PathFileExistsA( pszPath );
}

inline BOOL FileExists( const wchar_t* pszPath )
{
	return ::PathFileExistsW( pszPath );
}

inline char* FindExtension( const char* pszPath )
{
	return ::PathFindExtensionA( pszPath );
}

inline wchar_t* FindExtension( const wchar_t* pszPath )
{
	return ::PathFindExtensionW( pszPath );
}

inline char* FindFileName( const char* pszPath )
{
	return ::PathFindFileNameA( pszPath );
}

inline wchar_t* FindFileName( const wchar_t* pszPath )
{
	return ::PathFindFileNameW( pszPath );
}

inline int GetDriveNumber( const char* pszPath )
{
	return ::PathGetDriveNumberA( pszPath );
}

inline int GetDriveNumber( const wchar_t* pszPath )
{
	return ::PathGetDriveNumberW( pszPath );
}

inline BOOL IsDirectory( const char* pszPath )
{
	return ::PathIsDirectoryA( pszPath );
}

inline BOOL IsDirectory( const wchar_t* pszPath )
{
	return ::PathIsDirectoryW( pszPath );
}

inline BOOL IsFileSpec( const char* pszPath )
{
	return ::PathIsFileSpecA( pszPath );
}

inline BOOL IsFileSpec( const wchar_t* pszPath )
{
	return ::PathIsFileSpecW( pszPath );
}

inline BOOL IsPrefix( const char* pszPrefix, const char* pszPath )
{
	return ::PathIsPrefixA( pszPrefix, pszPath );
}

inline BOOL IsPrefix( const wchar_t* pszPrefix, const wchar_t* pszPath )
{
	return ::PathIsPrefixW( pszPrefix, pszPath );
}

inline BOOL IsRelative( const char* pszPath )
{
	return ::PathIsRelativeA( pszPath );
}

inline BOOL IsRelative( const wchar_t* pszPath )
{
	return ::PathIsRelativeW( pszPath );
}

inline BOOL IsRoot( const char* pszPath )
{
	return ::PathIsRootA( pszPath );
}

inline BOOL IsRoot( const wchar_t* pszPath )
{
	return ::PathIsRootW( pszPath );
}

inline BOOL IsSameRoot( const char* pszPath1, const char* pszPath2 )
{
	return ::PathIsSameRootA( pszPath1, pszPath2 );
}

inline BOOL IsSameRoot( const wchar_t* pszPath1, const wchar_t* pszPath2 )
{
	return ::PathIsSameRootW( pszPath1, pszPath2 );
}

inline BOOL IsUNC( const char* pszPath )
{
	return ::PathIsUNCA( pszPath );
}

inline BOOL IsUNC( const wchar_t* pszPath )
{
	return ::PathIsUNCW( pszPath );
}

inline BOOL IsUNCServer( const char* pszPath )
{
	return ::PathIsUNCServerA( pszPath );
}

inline BOOL IsUNCServer( const wchar_t* pszPath )
{
	return ::PathIsUNCServerW( pszPath );
}

inline BOOL IsUNCServerShare( const char* pszPath )
{
	return ::PathIsUNCServerShareA( pszPath );
}

inline BOOL IsUNCServerShare( const wchar_t* pszPath )
{
	return ::PathIsUNCServerShareW( pszPath );
}

inline BOOL MakePretty( char* pszPath )
{
	return ::PathMakePrettyA( pszPath );
}

inline BOOL MakePretty( wchar_t* pszPath )
{
	return ::PathMakePrettyW( pszPath );
}

inline BOOL MatchSpec( const char* pszPath, const char* pszSpec )
{
	return ::PathMatchSpecA( pszPath, pszSpec );
}

inline BOOL MatchSpec( const wchar_t* pszPath, const wchar_t* pszSpec )
{
	return ::PathMatchSpecW( pszPath, pszSpec );
}

inline void QuoteSpaces( char* pszPath )
{
	::PathQuoteSpacesA( pszPath );
}

inline void QuoteSpaces( wchar_t* pszPath )
{
	::PathQuoteSpacesW( pszPath );
}

inline BOOL RelativePathTo( char* pszPath, const char* pszFrom,
	DWORD dwAttrFrom, const char* pszTo, DWORD dwAttrTo )
{
	return ::PathRelativePathToA( pszPath, pszFrom, dwAttrFrom, pszTo, dwAttrTo );
}

inline BOOL RelativePathTo( wchar_t* pszPath, const wchar_t* pszFrom,
	DWORD dwAttrFrom, const wchar_t* pszTo, DWORD dwAttrTo )
{
	return ::PathRelativePathToW( pszPath, pszFrom, dwAttrFrom, pszTo, dwAttrTo );
}

inline void RemoveArgs( char* pszPath )
{
	::PathRemoveArgsA( pszPath );
}

inline void RemoveArgs( wchar_t* pszPath )
{
	::PathRemoveArgsW( pszPath );
}

inline char* RemoveBackslash( char* pszPath )
{
	return ::PathRemoveBackslashA( pszPath );
}

inline wchar_t* RemoveBackslash( wchar_t* pszPath )
{
	return ::PathRemoveBackslashW( pszPath );
}

inline void RemoveBlanks( char* pszPath )
{
	::PathRemoveBlanksA( pszPath );
}

inline void RemoveBlanks( wchar_t* pszPath )
{
	::PathRemoveBlanksW( pszPath );
}

inline void RemoveExtension( char* pszPath )
{
	::PathRemoveExtensionA( pszPath );
}

inline void RemoveExtension( wchar_t* pszPath )
{
	::PathRemoveExtensionW( pszPath );
}

inline BOOL RemoveFileSpec( char* pszPath )
{
	return ::PathRemoveFileSpecA( pszPath );
}

inline BOOL RemoveFileSpec( wchar_t* pszPath )
{
	return ::PathRemoveFileSpecW( pszPath );
}

inline BOOL RenameExtension( char* pszPath, const char* pszExt )
{
	return ::PathRenameExtensionA( pszPath, pszExt );
}

inline BOOL RenameExtension( wchar_t* pszPath, const wchar_t* pszExt )
{
	return ::PathRenameExtensionW( pszPath, pszExt );
}

inline char* SkipRoot( const char* pszPath )
{
	return ::PathSkipRootA( pszPath );
}

inline wchar_t* SkipRoot( const wchar_t* pszPath )
{
	return ::PathSkipRootW( pszPath );
}

inline void StripPath( char* pszPath )
{
	::PathStripPathA( pszPath );
}

inline void StripPath( wchar_t* pszPath )
{
	::PathStripPathW( pszPath );
}

inline BOOL StripToRoot( char* pszPath )
{
	return ::PathStripToRootA( pszPath );
}

inline BOOL StripToRoot( wchar_t* pszPath )
{
	return ::PathStripToRootW( pszPath );
}

inline void UnquoteSpaces( char* pszPath )
{
	::PathUnquoteSpacesA( pszPath );
}

inline void UnquoteSpaces( wchar_t* pszPath )
{
	::PathUnquoteSpacesW( pszPath );
}

inline BOOL CompactPath( HDC hDC, char* pszPath, UINT dx )
{
	return ::PathCompactPathA( hDC, pszPath, dx );
}

inline BOOL CompactPath( HDC hDC, wchar_t* pszPath, UINT dx )
{
	return ::PathCompactPathW( hDC, pszPath, dx );
}

inline BOOL CompactPathEx( char* pszDest, const char* pszSrc,
	UINT nMaxChars, DWORD dwFlags )
{
	return ::PathCompactPathExA( pszDest, pszSrc, nMaxChars, dwFlags );
}

inline BOOL CompactPathEx( wchar_t* pszDest, const wchar_t* pszSrc,
	UINT nMaxChars, DWORD dwFlags )
{
	return ::PathCompactPathExW( pszDest, pszSrc, nMaxChars, dwFlags );
}

};  // namespace ATLPath

template< typename StringType >
class CPathT
{
public:
	typedef typename StringType::XCHAR XCHAR;
	typedef typename StringType::PCXSTR PCXSTR;
	typedef typename StringType::PXSTR PXSTR;

public:
	CPathT() throw()
	{
	}
	CPathT( const CPathT< StringType >& path ) :
		m_strPath( path.m_strPath )
	{
	}
	CPathT( PCXSTR pszPath ) :
		m_strPath( pszPath )
	{
	}

	operator const StringType& () const throw()
	{
		return m_strPath;
	}
	operator StringType& () throw()
	{
		return m_strPath;
	}
	operator PCXSTR() const throw()
	{
		return m_strPath;
	}
	CPathT< StringType >& operator+=( PCXSTR pszMore )
	{
		Append( pszMore );

		return *this;
	}

	void AddBackslash()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength()+1 );
		ATLPath::AddBackslash( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	BOOL AddExtension( PCXSTR pszExtension )
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength()+StringType::StringLength( pszExtension ) );
		bResult = ATLPath::AddExtension( pszBuffer, pszExtension );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	BOOL Append( PCXSTR pszMore )
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength()+StringType::StringLength( pszMore )+1 );
		bResult = ATLPath::Append( pszBuffer, pszMore );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	void BuildRoot( int iDrive )
	{
		PXSTR pszBuffer;

		ATLASSERT( iDrive >= 0 );
		ATLASSERT( iDrive <= 25 );

		pszBuffer = m_strPath.GetBuffer( 3 );
		ATLPath::BuildRoot( pszBuffer, iDrive );
		m_strPath.ReleaseBuffer();
	}
	void Canonicalize()
	{
		PXSTR pszBuffer;
		StringType strResult;

		pszBuffer = strResult.GetBuffer( m_strPath.GetLength() );
		ATLPath::Canonicalize( pszBuffer, m_strPath );
		strResult.ReleaseBuffer();

		m_strPath = strResult;
	}
	void Combine( PCXSTR pszDir, PCXSTR pszFile )
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( MAX_PATH );
		ATLPath::Combine( pszBuffer, pszDir, pszFile );
		m_strPath.ReleaseBuffer();
	}
	CPathT< StringType > CommonPrefix( PCXSTR pszOther )
	{
		PXSTR pszBuffer;
		int nLength;
		CPathT< StringType > pathResult;

		pszBuffer = pathResult.m_strPath.GetBuffer( max( m_strPath.GetLength(), StringType::StringLength( pszOther ) ) );
		nLength = ATLPath::CommonPrefix( m_strPath, pszOther, pszBuffer );
		pathResult.m_strPath.ReleaseBuffer( nLength );

		return pathResult;
	}
	BOOL CompactPath( HDC hDC, UINT nWidth )
	{
		PXSTR pszBuffer;
		BOOL bResult;

		// PathCompactPath can actually _increase_ the length of the path
		pszBuffer = m_strPath.GetBuffer( MAX_PATH );
		bResult = ATLPath::CompactPath( hDC, pszBuffer, nWidth );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	BOOL CompactPathEx( UINT nMaxChars, DWORD dwFlags = 0 )
	{
		StringType strResult;
		BOOL bResult;
		PXSTR pszBuffer;

		pszBuffer = strResult.GetBuffer( nMaxChars );
		bResult = ATLPath::CompactPathEx( pszBuffer, m_strPath, nMaxChars,
			dwFlags );
		strResult.ReleaseBuffer();

		m_strPath = strResult;

		return bResult;
	}
	BOOL FileExists() const
	{
		return ATLPath::FileExists( m_strPath );
	}
	int FindExtension() const
	{
		PCXSTR pszBuffer;
		PCXSTR pszExtension;

		pszBuffer = m_strPath;
		pszExtension = ATLPath::FindExtension( pszBuffer );
		if( *pszExtension == 0 )
			return -1;
		else
			return int( pszExtension-pszBuffer );
	}
	int FindFileName() const
	{
		PCXSTR pszBuffer;
		PCXSTR pszFileName;

		pszBuffer = m_strPath;
		pszFileName = ATLPath::FindFileName( pszBuffer );
		if( *pszFileName == 0 )
			return -1;
		else
			return int( pszFileName-pszBuffer );
	}
	int GetDriveNumber() const
	{
		return ATLPath::GetDriveNumber( m_strPath );
	}
	StringType GetExtension() const
	{
		int iExtension;
		StringType strExtension;

		iExtension = FindExtension();
		if( iExtension != -1 )
			strExtension = m_strPath.Mid( iExtension );

		return strExtension;
	}
	BOOL IsDirectory() const
	{
		return ATLPath::IsDirectory( m_strPath );
	}

	BOOL IsFileSpec() const
	{
		return ATLPath::IsFileSpec( m_strPath );
	}
	BOOL IsPrefix( PCXSTR pszPrefix ) const
	{
		return ATLPath::IsPrefix( pszPrefix, m_strPath );
	}
	BOOL IsRelative() const
	{
		return ATLPath::IsRelative( m_strPath );
	}
	BOOL IsRoot() const
	{
		return ATLPath::IsRoot( m_strPath );
	}
	BOOL IsSameRoot( PCXSTR pszOther ) const
	{
		return ATLPath::IsSameRoot( m_strPath, pszOther );
	}
	BOOL IsUNC() const
	{
		return ATLPath::IsUNC( m_strPath );
	}
	BOOL IsUNCServer() const
	{
		return ATLPath::IsUNCServer( m_strPath );
	}
	BOOL IsUNCServerShare() const
	{
		return ATLPath::IsUNCServerShare( m_strPath );
	}
	BOOL MakePretty()
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		bResult = ATLPath::MakePretty( pszBuffer );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	BOOL MatchSpec( PCXSTR pszSpec ) const
	{
		return ATLPath::MatchSpec( m_strPath, pszSpec );
	}
	void QuoteSpaces()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength()+2 );
		ATLPath::QuoteSpaces( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	BOOL RelativePathTo( PCXSTR pszFrom, DWORD dwAttrFrom, 
		PCXSTR pszTo, DWORD dwAttrTo )
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( MAX_PATH );
		bResult = ATLPath::RelativePathTo( pszBuffer, pszFrom, dwAttrFrom,
			pszTo, dwAttrTo );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	void RemoveArgs()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::RemoveArgs( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	void RemoveBackslash()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::RemoveBackslash( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	void RemoveBlanks()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::RemoveBlanks( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	void RemoveExtension()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::RemoveExtension( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	BOOL RemoveFileSpec()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		BOOL bResult = ATLPath::RemoveFileSpec( pszBuffer );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	BOOL RenameExtension( PCXSTR pszExtension )
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( MAX_PATH );
		bResult = ATLPath::RenameExtension( pszBuffer, pszExtension );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	int SkipRoot() const
	{
		PCXSTR pszBuffer;
		PXSTR pszResult;

		pszBuffer = m_strPath;
		pszResult = ATLPath::SkipRoot( pszBuffer );

		return int( pszResult-pszBuffer );
	}
	void StripPath()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::StripPath( pszBuffer );
		m_strPath.ReleaseBuffer();
	}
	BOOL StripToRoot()
	{
		PXSTR pszBuffer;
		BOOL bResult;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		bResult = ATLPath::StripToRoot( pszBuffer );
		m_strPath.ReleaseBuffer();

		return bResult;
	}
	void UnquoteSpaces()
	{
		PXSTR pszBuffer;

		pszBuffer = m_strPath.GetBuffer( m_strPath.GetLength() );
		ATLPath::UnquoteSpaces( pszBuffer );
		m_strPath.ReleaseBuffer();
	}

public:
	StringType m_strPath;
};

typedef CPathT< CString > CPath;
typedef CPathT< CStringA > CPathA;
typedef CPathT< CStringW > CPathW;

};  // namespace ATL

#endif  //__ATLPATH_H__
