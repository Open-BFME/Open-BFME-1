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
#include <afxisapi.h>

CHttpServerContext& CHttpServerContext::operator<<(const CLongBinary& blob)
{
	ISAPIASSERT(m_pStream != NULL);
	if (m_pStream != NULL) *m_pStream << blob;
		return *this;
}

CHttpServerContext& CHttpServerContext::operator<<(const CByteArray& array)
{
	ISAPIASSERT(m_pStream != NULL);
	if (m_pStream != NULL) *m_pStream << array;
		return *this;
}

CHtmlStream& CHtmlStream::operator<<(const CByteArray& array)
{
   UINT_PTR nBytesLeft = array.GetSize();
   const BYTE* pb = array.GetData();

   if( pb != NULL )
   {
	  while( nBytesLeft > 0 )
	  {
		 UINT nBytesToWrite;

		 nBytesToWrite = (UINT)min( nBytesLeft, INT_MAX );
		 Write(pb, nBytesToWrite);
		 nBytesLeft -= nBytesToWrite;
		 pb += nBytesToWrite;
	  }
   }

	return *this;
}

CHtmlStream& CHtmlStream::operator<<(const CLongBinary& blob)
{
	if (blob.m_dwDataLength > 0 && blob.m_hData != NULL)
	{
		LPBYTE pbData = LPBYTE( GlobalLock(blob.m_hData) );
	  if (pbData != NULL )
	  {
		 UINT_PTR nBytesLeft;

		 nBytesLeft = blob.m_dwDataLength;
		 while( nBytesLeft > 0 )
		 {
			UINT nBytesToWrite;

			nBytesToWrite = (UINT)min( nBytesLeft, INT_MAX );
			Write(pbData, nBytesToWrite);
			nBytesLeft -= nBytesToWrite;
			pbData += nBytesToWrite;
		 }
		 GlobalUnlock( blob.m_hData );
	  }
	}

	return *this;
}
