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
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	const char *str() const
	{
		return m_string.m_data ? &m_string.m_data->data[0] : "";
	}

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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
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

// Retail RVA 0x000D38F0 is the float-mapped AsciiString table's resize
// specialization.  The resize algorithm only walks the key half of each node,
// but the mapped type remains part of the canonical hashtable spelling.
typedef _STL::pair<const AsciiString, float> AsciiStringFloatPair;
typedef _STL::hashtable<AsciiStringFloatPair, AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<AsciiStringFloatPair>, _STL::equal_to<AsciiString>,
    _STL::allocator<AsciiStringFloatPair> > AsciiStringFloatResizeTable;

// Explicitly instantiate this one resize member; no operator[] body is emitted
// from this resize-only TU.  Retail's complete interval is [0xD38F0,0xD3A92),
// including the final ret 4 at 0xD3A8F.
template void AsciiStringFloatResizeTable::resize(unsigned int);
