// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <string.h>
#include <vector>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template <>
inline int StringBase<char>::compare(const StringBase<char> &other) const
{
    int nb = other.m_data ? other.m_data->length : 0;
    const char *b = other.m_data ? other.m_data->data : "";
    return compare(b, nb);
}

template <>
inline int StringBase<char>::compare(const char *b, int nb) const
{
    int na = m_data ? m_data->length : 0;
    const char *a = m_data ? m_data->data : "";
    int cmp = memcmp(a, b, na < nb ? na : nb);
    return cmp ? cmp : na - nb;
}

// BfmeSharedString is the address-scoped view of the narrow-string result the
// field+0x10 getters share (see NetworkStringGetterIdentities.cpp).  The sole
// string-destructor definition retail folds here is ??1BfmeSharedString at
// 0x00887940 (a C++ alias of ?releaseBuffer@?$StringBase@D@@AAEXXZ in
// game/Libraries/Source/string/StringBase.cpp); this TU stays declaration-only
// for the lifetime and never defines the body, mirroring BfmeConv2016.cpp.
class BfmeSharedString : private AsciiString
{
public:
    int compare(const BfmeSharedString &other) const
    {
        return StringBase<char>::compare(other);
    }
};

class Rva00361960
{
public:
	BfmeSharedString copyString();

private:
	char m_beforeString[0x10];
	BfmeSharedString m_string;
	char m_afterString[0x58 - 0x10 - sizeof(BfmeSharedString)];
};

class Rva003634F0LivingWorldEntryStore
{
public:
	int findByField10(const BfmeSharedString &key);

private:
	char m_beforeEntries[0x18];
	std::vector<Rva00361960> m_entries;
};

int Rva003634F0LivingWorldEntryStore::findByField10(
	const BfmeSharedString &key)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		BfmeSharedString current = m_entries[i].copyString();
		if (current.compare(key) == 0)
			return i;
	}
	return -1;
}
