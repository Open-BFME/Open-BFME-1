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

#ifdef AFX_AUX_SEG
#pragma code_seg(AFX_AUX_SEG)
#endif


#ifdef _DEBUG
CDumpContext& AFXAPI operator <<(CDumpContext& dc, CTime time)
{
	__time64_t tmp = time.GetTime();
	char* psz = _ctime64(&tmp);
	if ((psz == NULL) || (time.GetTime() == 0))
		return dc << "CTime(invalid #" << time.GetTime() << ")";

	// format it
	psz[24] = '\0';         // nuke newline
	return dc << "CTime(\"" << psz << "\")";
}
#endif

CArchive& CTime::Serialize64(CArchive& ar)
{
	if (ar.IsStoring())
		return ar << (__int64) m_time;
	else
		return ar >> (__int64) m_time;
}

CArchive& AFXAPI operator <<(CArchive& ar, CTime time)
{
	// this version serializes only 32 bits
	__time64_t ttime = time.GetTime();
	ASSERT( ttime <= UINT_MAX);
	if( ttime > UINT_MAX )
		AfxThrowInvalidArgException();
	time_t timeConverted = (time_t)ttime;
	return ar << (DWORD) timeConverted;
}

CArchive& AFXAPI operator >>(CArchive& ar, CTime& rtime)
{
	// this version serializes only 32 bits
	time_t timeOld;
	CArchive& retRef = ar >> (DWORD&) timeOld;
	rtime = __time64_t(timeOld);
	return retRef;
}

/////////////////////////////////////////////////////////////////////////////
// CTimeSpan - relative time

#ifdef _DEBUG
CDumpContext& AFXAPI operator <<(CDumpContext& dc, CTimeSpan timeSpan)
{
	return dc << "CTimeSpan(" << timeSpan.GetDays() << " days, " <<
		 timeSpan.GetHours() << " hours, " <<
		 timeSpan.GetMinutes() << " minutes and " <<
		 timeSpan.GetSeconds() << " seconds)";
}
#endif

CArchive& CTimeSpan::Serialize64(CArchive& ar)
{
	if (ar.IsStoring())
		return ar << (__int64) m_timeSpan;
	else
		return ar >> (__int64) m_timeSpan;
}

CArchive& AFXAPI operator <<(CArchive& ar, CTimeSpan timeSpan)
{
	// this version serializes only 32 bits
	__time64_t timespan = timeSpan.GetTimeSpan();
	ASSERT( timespan <= UINT_MAX);
	if( timespan > UINT_MAX)
		AfxThrowInvalidArgException();
	time_t timeConverted = (time_t)timespan;
	return ar << (DWORD) timeConverted;
}

CArchive& AFXAPI operator >>(CArchive& ar, CTimeSpan& rtimeSpan)
{
	// this version serializes only 32 bits
	time_t timeOld;
	CArchive& retRef = ar >> (DWORD&) timeOld;
	rtimeSpan = __time64_t(timeOld);
	return retRef;
}
