// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: STLport __find<UnicodeString *, UnicodeString>, retail 0x005313B0,
// 627 bytes.  The find() wrapper at 0x00531F10 (random-access tag byte at
// esp+3) and the body at 0x005337E0 call it through ILT 0x00007220.  Elements
// are four-byte wide-string handles; the loop processes four handles (16
// bytes) per unrolled group.  Twin of the AsciiString instantiation in
// stlport_ascii_string_find.cpp (0x001DBC10).
//
// The element is UnicodeString: its out-of-line comparisons call
// StringBase<unsigned short>::compare (ILT 0x000226EC, body 0x0005FFA0), and
// StringBase's constructors and destructor are private to its AsciiString and
// UnicodeString friends, so no container can hold a bare StringBase<G>.
// Iterator constness is not witnessed by the bytes.
//
// Retail inlines compare at 4 of the 7 sites (trip sites 1-2, switch cases 2
// and 1) and calls ILT 0x000226EC at the rest.  The inline expansion contains
// the 0x0005DC70 run compare, so that helper is visible here.  Material for
// VC7.1's inline budget: the helper is a non-static inline (a static one is
// never inlined) taking the one-byte flags argument 0x0005FFA0 pushes, its
// loop is a pre-tested while, and its cursor locals are defined p-then-q
// (that order loads *q before *p in the mismatch delta).

#include <algorithm>
#include <stl/_iterator_base.h>

#include "string_base.h"

struct Rva0005DC70Flags
{
	bool noCase;
};

inline int Rva0005DC70CompareWideLengths(const unsigned short *s1, int len1,
	const unsigned short *s2, int len2, Rva0005DC70Flags flags)
{
	int minLen = len1;
	if (minLen >= len2)
		minLen = len2;

	const unsigned short *p = s1;
	const unsigned short *q = s2;
	while (minLen > 0)
	{
		if (*p != *q)
		{
			int diff = *p - *q;
			if (diff)
				return diff;
			break;
		}
		++p;
		++q;
		--minLen;
	}
	return len1 - len2;
}

class UnicodeString
{
public:
	int compare(const UnicodeString &that) const
	{
		int len = that.m_data.m_data ? that.m_data.m_data->length : 0;
		const unsigned short *data = that.m_data.str();
		return compare(data, len);
	}

	int compare(const unsigned short *str, int len) const
	{
		Rva0005DC70Flags flags;
		flags.noCase = false;
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const unsigned short *data = m_data.str();
		return Rva0005DC70CompareWideLengths(data, myLen, str, len, flags);
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

	// Retail 0x00531F10, 30 bytes, through ILT 0x00032D67: the find() front
	// end passing the random-access tag at esp+3.
	template UnicodeString *find<UnicodeString *, UnicodeString>(
		UnicodeString *, UnicodeString *, const UnicodeString &);
}
