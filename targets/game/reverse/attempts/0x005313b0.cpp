// ??$__find@PAVUnicodeString@@V1@@_STL@@YAPAVUnicodeString@@PAV1@0ABV1@ABUrandom_access_iterator_tag@0@@Z
// partial score=0.0 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ??$__find@PAVUnicodeString@@V1@@_STL@@YAPAVUnicodeString@@PAV1@0ABV1@ABUrandom_access_iterator_tag@0@@Z
// partial score=0.05 date=2026-09-28
// STLport __find<UnicodeString *, UnicodeString> (random-access, 4x unrolled),
// retail 0x005313B0, 627 bytes; the find() wrapper 0x00531F10 (tag byte at
// esp+3) calls it through ILT 0x00007220.  Twin of the matched AsciiString
// instantiation stlport_ascii_string_find.cpp (0x001DBC10).  Pointer constness
// of the iterator is not witnessed (the __uninitialized_copy pin is synthetic).
// Retail inlines UnicodeString::compare (word loop, a-b on mismatch, else
// length difference) at 4 of the 7 sites (trip sites 1-2, switch cases 2 and
// 1) and calls ILT 0x000226EC at the rest.  This compare is rejected by the
// VC7.1 inline budget: the same body WITHOUT the four null-check ternaries
// inlines at exactly retail's 4 sites (445 B), so retail's null handling must
// cost less in the IR; if/else, accessor, forceinline-accessor, goto, while,
// helper and wcsncmp spellings all failed.

#include <algorithm>
#include <stl/_iterator_base.h>

#include "string_base.h"

extern const char g_bfmeEmptyUnicode[];

class UnicodeString
{
public:
	int compare(const UnicodeString &that) const
	{
		const int len = that.m_data.m_data ? that.m_data.m_data->length : 0;
		const unsigned short *data = that.m_data.m_data ?
			&that.m_data.m_data->data[0] : (const unsigned short *)g_bfmeEmptyUnicode;
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const unsigned short *myData = m_data.m_data ?
			&m_data.m_data->data[0] : (const unsigned short *)g_bfmeEmptyUnicode;
		int result = 0;
		for (int count = myLen < len ? myLen : len; count > 0; --count, ++myData, ++data)
		{
			if (*myData != *data)
			{
				result = *myData - *data;
				break;
			}
		}
		if (result != 0)
			return result;
		return myLen - len;
	}

private:
	StringBase<unsigned short> m_data;
};

inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compare(right) == 0;
}

namespace _STL
{
	typedef UnicodeString *(*UnicodeStringFindFn)(
		UnicodeString *, UnicodeString *, const UnicodeString &,
		const random_access_iterator_tag &);

	template UnicodeString *__find<UnicodeString *, UnicodeString>(
		UnicodeString *, UnicodeString *, const UnicodeString &,
		const random_access_iterator_tag &);

	UnicodeStringFindFn const bfmeUnicodeStringFindAnchor =
		&__find<UnicodeString *, UnicodeString>;
}
