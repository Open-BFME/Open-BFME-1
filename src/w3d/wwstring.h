// Minimal StringClass, matching the layout and inline bodies of the Generals Zero
// Hour reference (Libraries/Source/WWVegas/WWLib/wwstring.h) that RawFileClass needs.
// StringClass has no vtable and a single member (m_Buffer), so this reproduces the
// object layout exactly; only the members RawFileClass touches are declared. The
// non-inline methods (Get_String / Uninitialised_Grow / Free_String) are prototypes
// -- their real bodies live in the game's wwstring.obj, reached by masked REL32 call.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __WWSTRING_H
#define __WWSTRING_H

#include <string.h>
#include <tchar.h>

#ifndef WWASSERT
#define WWASSERT(exp)
#endif

class StringClass
{
public:

	StringClass (const TCHAR *string, bool hint_temporary = false);
	~StringClass (void);

	inline const StringClass &operator= (const TCHAR *string);

	const TCHAR & operator[] (int index) const;
	TCHAR & operator[] (int index);
	inline operator const TCHAR * (void) const;

	inline int	Get_Length (void) const;

private:

	typedef struct _HEADER
	{
		int	allocated_length;
		int	length;
	} HEADER;

	void			Get_String (int length, bool is_temp);
	void			Uninitialised_Grow (int length);
	void			Free_String (void);

	inline void	Store_Length (int length);
	inline HEADER * Get_Header (void) const;

	TCHAR *		m_Buffer;

	static TCHAR	m_NullChar;
	static TCHAR *	m_EmptyString;
};

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator= (const TCHAR *string)
{
	if (string != 0) {

		int len = _tcslen (string);
		Uninitialised_Grow (len+1);
		Store_Length (len);

		::memcpy (m_Buffer, string, (len + 1) * sizeof (TCHAR));
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (const TCHAR *string, bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	int len=string ? _tcsclen(string) : 0;
	if (hint_temporary || len>0) {
		Get_String (len+1, hint_temporary);
	}

	(*this) = string;
	return ;
}

///////////////////////////////////////////////////////////////////
//	~StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::~StringClass (void)
{
	Free_String ();
	return ;
}

///////////////////////////////////////////////////////////////////
//	operator const TCHAR *
///////////////////////////////////////////////////////////////////
inline
StringClass::operator const TCHAR * (void) const
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Get_Length
///////////////////////////////////////////////////////////////////
inline int
StringClass::Get_Length (void) const
{
	int length = 0;

	if (m_Buffer != m_EmptyString) {

		//
		//	Read the length from the header
		//
		HEADER *header	= Get_Header ();
		length			= header->length;

		//
		//	Hmmm, a zero length was stored in the header,
		// we better manually get the string length.
		//
		if (length == 0) {
			length = _tcslen (m_Buffer);
			((StringClass *)this)->Store_Length (length);
		}
	}

	return length;
}

///////////////////////////////////////////////////////////////////
// Get_Header
///////////////////////////////////////////////////////////////////
inline StringClass::HEADER *
StringClass::Get_Header (void) const
{
	return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof (StringClass::_HEADER));
}

///////////////////////////////////////////////////////////////////
// Store_Length
///////////////////////////////////////////////////////////////////
inline void
StringClass::Store_Length (int length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header		= Get_Header ();
		header->length		= length;
	} else {
		WWASSERT (length == 0);
	}

	return ;
}

#endif //__WWSTRING_H
