// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

struct Rva00197430Pair
{
	AsciiString first;
	AsciiString second;
};

typedef int Rva00197430Bool;

// ?rva00197430PairLess@@YAHABURva00197430Pair@@0@Z
Rva00197430Bool rva00197430PairLess(
	const Rva00197430Pair &left, const Rva00197430Pair &right)
{
	return left.first.StringBase<char>::compare( right.first ) < 0
		|| ( !( right.first.StringBase<char>::compare( left.first ) < 0 )
			&& left.second.StringBase<char>::compare( right.second ) < 0 );
}
