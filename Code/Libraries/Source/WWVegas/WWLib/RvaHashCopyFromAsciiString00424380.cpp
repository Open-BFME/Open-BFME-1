// cl: /ICode/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hashtable<V, AsciiString>::_M_copy_from at 0x00424380, byte-twin (tools/twin_scan.py) of 0x000D6800 in RvaHashCopyFromAsciiString.cpp; only the _Construct callee differs.
// Same value layout as the _M_insert neighbour at 0x000D6770: 12-byte node
// (next plus AsciiString key plus 4-byte mapped). Pins named initialize_buckets
// were wrong; the body clears buckets, reserve+insert of nulls, then clones
// each chain through _M_new_node / _Construct.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#define private public
#include <hash_map>
#undef private

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

struct Rva00424380Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00424380ExtractKey
{
	const AsciiString &operator()(const Rva00424380Value &x) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00424380Value, AsciiString, rts::hash<AsciiString>,
	Rva00424380ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00424380Value> > Rva00424380Table;

template void Rva00424380Table::_M_copy_from(const Rva00424380Table &other);
