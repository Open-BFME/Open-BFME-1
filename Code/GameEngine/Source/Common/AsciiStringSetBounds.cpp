// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _Rb_tree<AsciiString>::_M_lower_bound (145B at 0x00633900) and
// _M_upper_bound (145B at 0x000804D0), the two halves of set<AsciiString>'s
// bound search. Both names were parked on 5-byte incremental-link thunks.
//
// The tree is STLport's, so the walk itself is the header's; what makes these
// bodies 145 bytes is that the comparison inlines all the way down. AsciiString
// is one pointer to the shared buffer header -- refcount, then the length as a
// halfword at +4, then the characters at +8 -- and a null pointer stands in as
// the empty string at 0x0107388B, which is the same literal string_base.cpp's
// compare uses. The compare runs memcmp over the shorter side and falls back to
// the length difference, exactly as StringBase<char>::compare does.
//
// Node layout confirms STLport's: colour and three pointers, then the value at
// +0x10, with the left child at +8 and the right at +0x0C.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compare(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : "";
		int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result == 0) {
			result = myLen - len;
		}
		return result;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

inline bool operator<(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) < 0;
}

// Reaching both bounds is what makes the compiler emit them.
Bool BfmeAsciiStringSetBoundsAnchor(const _STL::set<AsciiString> &tree, const AsciiString &key)
{
	return tree.lower_bound(key) != tree.upper_bound(key);
}
