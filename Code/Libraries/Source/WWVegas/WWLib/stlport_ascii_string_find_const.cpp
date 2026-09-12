// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: STLport __find<const AsciiString *, AsciiString>, retail
// 0x001DBEC0, 547 bytes.  ObjectTypes::isInSet(const AsciiString&) at
// 0x001DC2D0 calls std::find on its vector<AsciiString> member, and the
// named ILT at 0x0004B29A reaches this const-pointer specialization.  The
// addObjectType caller at 0x001DC520 supplies an independent same-family
// use.  Each AsciiString is a 4-byte handle.  Retail's `sar ebp,4` divides
// the byte distance by sixteen, and its unrolled group covers four handles
// (16 bytes total); the element itself is not 16 bytes.  StringBase<char>
// stores a 4-byte Header* whose header words are int ref_count, followed by
// unsigned-short length and capacity, then char data.  The complete +0x222
// ret establishes the full boundary.
//
// This is the out-of-line random-access find body from vendor/stlport.  The
// local AsciiString view keeps StringBase<char>'s retail layout visible so
// MSVC emits the four-way unrolled comparisons and the compare tail calls.

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
	typedef const AsciiString *(*AsciiStringConstFindFn)(
		const AsciiString *, const AsciiString *, const AsciiString &,
		const random_access_iterator_tag &);

	template const AsciiString *__find<const AsciiString *, AsciiString>(
		const AsciiString *, const AsciiString *, const AsciiString &,
		const random_access_iterator_tag &);

	AsciiStringConstFindFn const bfmeAsciiStringConstFindAnchor =
		&__find<const AsciiString *, AsciiString>;
}
