// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// _Rb_tree::_M_lower_bound (retail 0x00692690, 180 bytes) and _M_upper_bound
// (0x00692780, 180 bytes) over the 12-byte key Rva00692570Less (0x00692570)
// compares: unsigned primary at +0, AsciiString at +4. Both are STLport's
// header walks; 0x00692690 keeps a node when !(node < key), 0x00692780 when
// key < node. Unlike the out-of-line functor, the trees inline the whole
// comparison, AsciiString's included: retail reads the null-buffer fallback
// from StringBase<char>::str()'s TheNullChr (0x0107388B), so the compare is
// spelled through getLength()/str(), and that spelling is also what gives the
// retail register assignment (a "" literal moves the node into EBP).

#define _STLP_NO_EXCEPTIONS 1
#include <set>
#include "ascii_string.h"

struct Rva00692570Key
{
	unsigned primary;
	AsciiString secondary;
	unsigned trailing;
};

static inline int CompareSecondary00692570(const AsciiString &self, const AsciiString &other)
{
	int thatLen = other.StringBase<char>::getLength();
	const char *thatData = other.str();
	int thisLen = self.StringBase<char>::getLength();
	const char *thisData = self.str();
	int c = memcmp(thisData, thatData, thisLen < thatLen ? thisLen : thatLen);
	return c ? c : thisLen - thatLen;
}

inline bool operator<(const Rva00692570Key &left, const Rva00692570Key &right)
{
	if (left.primary < right.primary)
		return true;
	if (left.primary > right.primary)
		return false;
	return CompareSecondary00692570(left.secondary, right.secondary) < 0;
}

// Not in retail: instantiates both bound walks in this object.
bool Rva00692570KeyBoundsAnchor(const _STL::set<Rva00692570Key> &tree, const Rva00692570Key &key)
{
	return tree.lower_bound(key) != tree.upper_bound(key);
}
