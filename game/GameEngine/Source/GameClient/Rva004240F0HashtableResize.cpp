// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x004240F0 is a 418-byte STLport hashtable resize body. The
// StringBase<char> copy and release calls at 0x00887B60 and 0x00887940,
// together with the inline signed-byte hash loop, prove the AsciiString key.
// Resize never reads the mapped payload, so this TU uses an address-derived
// payload view while retaining the unresolved body's address in the type name.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "ascii_string.h"

typedef unsigned short Word;

struct Rva004240F0StringHeader
{
	int m_refCount;
	Word m_length;
	Word m_capacity;
	char m_data[1];
};

struct Rva004240F0StringView
{
	Rva004240F0StringHeader *m_data;
};

namespace rts
{
template <class T>
	struct hash;

template <>
	struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const
		{
			Rva004240F0StringHeader *data =
				reinterpret_cast<Rva004240F0StringView *>(&value)->m_data;
			const char *p = data ? &data->m_data[0] : "";
			unsigned int result = 0;
			while (*p != '\0')
			{
				result = result * 5 + *p;
				++p;
			}
			return result;
		}
	};

template <class T>
	struct equal_to;

template <>
	struct equal_to<AsciiString>
	{
		bool operator()(const AsciiString &left, const AsciiString &right) const
		{
			return left == right;
		}
	};
}

struct Rva004240F0Value
{
	unsigned int m_payload;
};

typedef _STL::pair<const AsciiString, Rva004240F0Value *> Rva004240F0Pair;
typedef _STL::hashtable<Rva004240F0Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva004240F0Pair>, rts::equal_to<AsciiString>,
	_STL::allocator<Rva004240F0Pair> > Rva004240F0Table;

template void Rva004240F0Table::resize(unsigned int);
