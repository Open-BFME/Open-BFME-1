// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Natural STLport resize of the ThingFactory template map at RVA 0x00135ED0.
//
// The reference ThingFactory.h typedef is exactly
//   std::hash_map<AsciiString, ThingTemplate*, rts::hash<AsciiString>,
//                 rts::equal_to<AsciiString> > ThingTemplateHashMap;
// The local view exposes the proven four-byte StringBase handle and inline
// data access while retaining the genuine StringBase copy/release methods.
// The current WWLib header forwards str() out of line; this retail resize
// embeds the data access and signed-byte hash loop. The mapped pointer and
// hash/equality types follow the real ThingFactory typedef.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// Retail StringBase-backed ABI view used by the already verified 418-byte
// AsciiString hashtable resize family.
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
struct hash
{
	unsigned int operator()(T value) const;
};

// This is the canonical STLTypedefs.h rts::hash<AsciiString> identity.  The
// direct STLport helper is the implementation of its std::hash<const char *>
// call and keeps the established signed-char hash loop inline.
template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};

template <class T>
struct equal_to;

template <>
struct equal_to<AsciiString>
{
	Bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left == right;
	}
};
}

class ThingTemplate;

// Underlying STLport table from ThingFactory.h's map typedef. The
// mapped pointer is four bytes, yielding the observed 0x0C hashtable node.
typedef _STL::pair<const AsciiString, ThingTemplate *> ThingTemplateHashPair;
typedef _STL::hashtable<ThingTemplateHashPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<ThingTemplateHashPair>, rts::equal_to<AsciiString>,
	_STL::allocator<ThingTemplateHashPair> > ThingTemplateResizeTable;

// Retail RVA 0x00135ED0; complete body interval is [0x00135ED0, 0x00136072).
template void ThingTemplateResizeTable::resize(unsigned int);
