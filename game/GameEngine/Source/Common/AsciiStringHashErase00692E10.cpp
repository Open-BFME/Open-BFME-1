// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// Open-BFME matches the STLport hashtable erase(const AsciiString&) body at
// retail 0x00692E10.
// The paired iterator erase body at 0x00692D50 identifies the table as the
// AsciiString to address-derived mapped-pointer table. The pair destructor at
// ILT 0x00046D9E and the bucket helper at ILT 0x0004A741 match this instance.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class Rva00692D50Mapped;

// The upstream layout comes from inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// game/GameEngine/Include/Common/AsciiString.h.
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

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
struct hash
{
	unsigned int operator()(T value) const; // ILT 0x0000EC91
};
}

typedef _STL::pair<const AsciiString, Rva00692D50Mapped *> Rva00692E10Pair;
typedef _STL::hashtable<Rva00692E10Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva00692E10Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00692E10Pair> > Rva00692E10HashTable;

template unsigned int Rva00692E10HashTable::erase(const AsciiString &key);
