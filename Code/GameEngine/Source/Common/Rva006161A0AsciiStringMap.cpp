// ?Rva006161A0@Rva006161A0Owner@@QAEXVAsciiString@@H@Z
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

	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }

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

class Rva006161A0Owner
{
public:
    void Rva006161A0(AsciiString key, int value);
private:
    char m_pad[0x224];
    Rva00614D10Map m_map;
};
void Rva006161A0Owner::Rva006161A0(AsciiString key, int value)
{
    if (key.isEmpty() || value == 0) return;
    if (m_map._M_ht._M_find(key) == 0)
        m_map[key] = static_cast<Rva00614D10Mapped>(value);
}
