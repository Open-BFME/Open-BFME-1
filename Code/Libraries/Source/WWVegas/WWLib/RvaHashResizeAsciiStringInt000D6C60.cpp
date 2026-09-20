// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	const char *str() const
	{
		return m_data.m_data ? &m_data.m_data->data[0] : "";
	}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;
};

template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

// Same value/extract-key shape as the landed _M_insert anchor at retail
// 0x000D6C60 (Code/Libraries/Source/WWVegas/WWLib/RvaHashInsertAsciiString.cpp):
// an 8-byte value (4-byte AsciiString key + 4-byte mapped int) reached
// through its own extract-key functor.
struct Rva000D6C60Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000D6C60ExtractKey
{
	const AsciiString &operator()(const Rva000D6C60Value &entry) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva000D6C60Value, AsciiString, rts::hash<AsciiString>,
	Rva000D6C60ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6C60Value> > AsciiStringIntHash000D6C60;

// retail 0x000D3BE0: the resize the 0x000D6C60 _M_insert calls when the
// table needs to grow. Same explicit-instantiation technique as
// Code/Libraries/Source/WWVegas/WWLib/AsciiStringFloatHashResize.cpp.
template void AsciiStringIntHash000D6C60::resize(unsigned int);
