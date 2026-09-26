// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;
};

// STLTypedefs' AsciiString specialization hashes the character sequence through
// STLport's inline __stl_hash_string.  The x86 retail/compiler char mode is
// signed, giving the observed movsx contribution for each byte.  Keep the
// return explicitly unsigned: resize uses the unsigned div path.
template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

struct Rva00614D10Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00614D10ExtractKey
{
	const AsciiString &operator()(const Rva00614D10Value &entry) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00614D10Value, AsciiString, rts::hash<AsciiString>,
	Rva00614D10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00614D10Value> > Rva00614D10Table;

// Retail RVA 0x006138D0 is the resize body called by the named _M_insert at
// 0x00614D10 through ILT 0x0000A998.  The existing Rva00614D10 value and
// extract-key declarations establish this concrete AsciiString/int table.
template void Rva00614D10Table::resize(unsigned int);
