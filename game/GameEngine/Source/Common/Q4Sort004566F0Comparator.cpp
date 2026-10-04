// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// The retail comparator has no additional EH cleanup state for the no-case comparison.
template <>
__declspec(nothrow) int StringBase<unsigned short>::compareNoCase(
	const StringBase<unsigned short> &other) const;

inline UnicodeString::~UnicodeString()
{
    ((StringBase<wchar_t> *)this)->releaseBuffer();
}

class MapMetaData
{
public:
	UnicodeString getFileName() const;
};


struct Q4Sort004566F0
{
	bool operator()(int a, int b) const;
};

bool Q4Sort004566F0::operator()(int a, int b) const
{
	return ((const MapMetaData *)a)->getFileName().compareNoCase(
		((const MapMetaData *)b)->getFileName()) < 0;
}
