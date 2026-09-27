// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: map<NameKeyType, Real>'s tree copy, _M_copy at 0x005671E0,
// 171 bytes. A copy walks the source tree and never compares, so NameKeyType
// needs no more than its size here -- and the sibling _Rb_tree::operator= for
// the same instantiation (0x005672C0, RTS/Player.cpp) is the matched caller
// that fixes the identity.
//
// The node is 0x18 bytes: sixteen of _Rb_tree_node_base header and eight of
// value (the four-byte key plus the four-byte float). The value is built by an
// out-of-line _Construct call rather than inline stores, which is what this
// build does for every element type that is not a pointer.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef float Real;
typedef bool Bool;

// enum base type 4: W4NameKeyType in the mangled name is an int-sized enum.
enum NameKeyType { NAMEKEY_INVALID = 0 };

namespace _STL
{
// Not inlined in this build: the pair is built through a call. The address is
// ICF-shared with the other copyable four-byte-key pairs, e.g. the
// pair<const Gen_t_0007cd50_k4, Gen_t_0007cd50_p12cd> _Construct at 0x0007CD50.
template <>
void _Construct(pair<const NameKeyType, Real> *p, const pair<const NameKeyType, Real> &val);
}

typedef _STL::map<NameKeyType, Real> BfmeNameKeyFloatMap;

void BfmeNameKeyTypeFloatMapAnchor(BfmeNameKeyFloatMap &out, const BfmeNameKeyFloatMap &in)
{
	out = in;
}
