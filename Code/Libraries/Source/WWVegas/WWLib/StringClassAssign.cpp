// cl: /DNDEBUG /MD /EHsc
// Open-BFME: StringClass::operator=(const StringClass &), retail 0x0013B600, 73 bytes.
//
// wwstring.h's inline, emitted out of line here. Get_Length and
// Uninitialised_Grow are the two calls (the first through the ILT at
// 0x00017DA0, the second straight to 0x009DBA70); Store_Length is inlined
// down to its `m_Buffer != m_EmptyString` guard and the store at
// m_Buffer-4, which is where HEADER::length lives.
//
// The memcpy is the intrinsic's variable-count expansion -- rep movsd for the
// dwords, rep movsb for the remainder -- with the count in characters times
// sizeof(TCHAR), and TCHAR is char in this build, so the count is len+1 bytes.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

typedef char TCHAR;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	const StringClass &operator= (const StringClass &string);

	int Get_Length (void) const;				// ILT 0x00017DA0

private:
	typedef struct _HEADER
	{
		int	allocated_length;
		int	length;
	} HEADER;

	void Uninitialised_Grow (int length);			// retail 0x009DBA70

	inline void Store_Length (int length)
	{
		if (m_Buffer != m_EmptyString) {
			HEADER *header		= Get_Header ();
			header->length		= length;
		}
	}

	inline HEADER *Get_Header (void) const
	{
		return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof (StringClass::_HEADER));
	}

	TCHAR *		m_Buffer;

	static TCHAR *	m_EmptyString;
};

// ??4StringClass@@QAEABV0@ABV0@@Z
const StringClass &
StringClass::operator= (const StringClass &string)
{	
	int len = string.Get_Length();
	Uninitialised_Grow(len+1);
	Store_Length(len);

	::memcpy (m_Buffer, string.m_Buffer, (len+1) * sizeof (TCHAR));		
	return (*this);

}
