// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Open-BFME: STLport hashtable erase(const AsciiString&) at retail
// 0x006A78C0. The caller at 0x006AC0F0 resets this table through its
// address-derived subobject. The pinned bucket helper at 0x006A1060 names
// the four-byte mapped value as BuildableStatus.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ?
			&str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

enum BuildableStatus
{
	BSTATUS_YES = 0,
	BSTATUS_IGNORE_PREREQUISITES,
	BSTATUS_NO,
	BSTATUS_ONLY_BY_AI,
	BSTATUS_NUM_TYPES
};

namespace rts
{
	template <class T> struct hash;
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};
}

typedef _STL::pair<const AsciiString, BuildableStatus> Rva006A78C0Pair;
typedef _STL::hashtable<Rva006A78C0Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva006A78C0Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva006A78C0Pair> > Rva006A78C0HashTable;

#pragma comment(linker, "/alternatename:??1?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@QAE@XZ=?j_00036291@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_bkt_num_key@?$hashtable@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@2@@_STL@@ABEIABVAsciiString@@I@Z=?j_0004004d@@YAXXZ")

template unsigned int Rva006A78C0HashTable::erase(const AsciiString &key);
