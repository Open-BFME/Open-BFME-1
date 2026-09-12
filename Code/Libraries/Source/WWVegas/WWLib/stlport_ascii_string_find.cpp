// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: STLport __find<AsciiString *, AsciiString>, retail 0x001DBC10,
// 547 bytes.  ModelConditionInfo::addPublicBone calls this specialization
// through ILT 0x0004A534 at 0x00772C55. Elements are four-byte string
// handles; the loop processes four handles (16 bytes) per unrolled group.
//
// This is the out-of-line random-access find body from vendor/stlport.  The
// local AsciiString view is the retail StringBase<char> layout: an object is
// one pointer; its header has a dword refcount and word length/capacity,
// with character data at header+8.
// Keeping compare visible here is material: MSVC inlines the first unrolled
// comparisons and leaves the remainder calls to the already-matched compare
// body, exactly as retail does.

#include <algorithm>
#include <stl/_iterator_base.h>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	int compare(const AsciiString &that) const
	{
		const int len = that.m_data.m_data ? that.m_data.m_data->length : 0;
		const char *data = that.m_data.m_data ?
			&that.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ?
			&m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

private:
	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace _STL
{
	typedef AsciiString *(*AsciiStringFindFn)(
		AsciiString *, AsciiString *, const AsciiString &,
		const random_access_iterator_tag &);

	template AsciiString *__find<AsciiString *, AsciiString>(
		AsciiString *, AsciiString *, const AsciiString &,
		const random_access_iterator_tag &);

	AsciiStringFindFn const bfmeAsciiStringFindAnchor =
		&__find<AsciiString *, AsciiString>;
}
