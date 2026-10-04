// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// S4 sort compares the numbered BFME display name after it compares the
// entry count.  The count branch and the two UnicodeString temporaries match
// the comparator shared by the retail S4 insertion and heap callers.

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// Retail does not establish an additional EH state for this comparison.
template <>
__declspec(nothrow) int StringBase<unsigned short>::compareNoCase(
    const StringBase<unsigned short> &other) const;

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

// Keep the comparison on the canonical wide buffer, without emitting a second
// public UnicodeString comparison provider from this comparator TU.
static inline int compareDisplayNames(
    const UnicodeString &left, const UnicodeString &right)
{
    return ((const StringBase<unsigned short> *)&left)->compareNoCase(
        *(const StringBase<unsigned short> *)&right);
}

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(void);

	char m_pad[0x20];
	int m_count;
};

struct S4Cmp00452A50
{
	void *m_state;
	bool operator()(int a, int b) const;
};

bool S4Cmp00452A50::operator()(int a, int b) const
{
	if (((const MapMetaData *)a)->m_count == ((const MapMetaData *)b)->m_count)
		return compareDisplayNames(((MapMetaData *)a)->bfme_getDisplayName(),
			((MapMetaData *)b)->bfme_getDisplayName()) < 0;

	return ((const MapMetaData *)a)->m_count < ((const MapMetaData *)b)->m_count;
}
