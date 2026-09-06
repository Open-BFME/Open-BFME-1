// ?lookup@Rva00614EA0Owner@@QAE?AW4Rva00614D10Mapped@@PBD@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ivendor/stlport /ICode/Libraries/Source/WWVegas/WWLib
// Address-derived lookup owner.  Retail constructs an AsciiString, queries
// the four-byte AsciiString hash table at owner+0x224, and returns the mapped
// word.  The table's iterator/find body remains the pinned retail family.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
// The retail caller consumes the hashtable node returned by _M_find rather
// than materializing STLport's two-pointer const_iterator.  This access is
// confined to this TU and uses the vendor implementation's real layout.
#define private public
#include <hash_map>
#undef private

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}

	int compare(const AsciiString &other) const
	{
		const int otherLength = other.m_data
			? other.m_data->length : 0;
		const char *otherText = other.m_data
			? &other.m_data->data[0] : "";
		const int length = m_data ? m_data->length : 0;
		const char *text = m_data ? &m_data->data[0] : "";
		const int result = memcmp(text, otherText,
			length < otherLength ? length : otherLength);
		return result != 0 ? result : length - otherLength;
	}

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

enum Rva00614D10Mapped { Rva00614D10MappedZero = 0, Rva00614D10MappedMin = (-2147483647 - 1), Rva00614D10MappedMax = 2147483647 };

typedef _STL::hash_map<AsciiString, Rva00614D10Mapped,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00614D10Mapped> > >
	Rva00614D10Map;

class Rva00614EA0Owner
{
public:
	Rva00614D10Mapped lookup(const char *name);

private:
	char m_prefix[0x224];
	Rva00614D10Map m_map;
};

Rva00614D10Mapped Rva00614EA0Owner::lookup(const char *name)
{
	if (name == 0)
	{
		return Rva00614D10MappedZero;
	}

	AsciiString key(name);
	Rva00614D10Map::_Ht *table = &m_map._M_ht;
	Rva00614D10Map::_Ht::_Node *found = table->_M_find(key);
	if (found != 0)
	{
		return found->_M_val.second;
	}

	return Rva00614D10MappedZero;
}
